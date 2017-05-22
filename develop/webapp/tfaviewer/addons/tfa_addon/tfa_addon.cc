// hello.cc
// https://nodejs.org/api/addons.html
// arguments https://github.com/nodejs/node-addon-examples/blob/master/2_function_arguments/node_0.12/addon.cc

/*
npm install -g node-gyp
npm install --save nan
*/

// =============================================================================
// INCLUDES
// =============================================================================

#include <node.h>
#include <nan.h>
#include <uv.h>

#include <string>
#include <fstream>
#include <streambuf>

 #include <math.h>       /* ceil */

#include "zutil.h"
#include "zindex.h"

using namespace v8;
using namespace std;

namespace demo {

// =============================================================================
// NAMESPACES
// =============================================================================

using v8::HandleScope;
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Persistent;
using Nan::New; 
using Nan::Set;

#define MAX_SEQUENCES_TRANSMISSION 1000 // Maximum number of sequences to be sent in order to prevent Heap Allocation Failure
                                        // For example:
                                        //      If 10 sequences are required, then 10 sequences are returned
                                        //      If MAX sequences are required, then MAX sequences are returned
                                        //      If 2*MAX sequences are required, then MAX sequences are returned. Jumping 1 sequence.
                                        //      If 3*MAX sequences are required, then MAX sequences are returned. Jumping 2 sequences.
                                        //      If 2,5*MAX sequences are required, then <=MAX sequences are returned. Jumping a float number of sequences from 1 to 2.


// =============================================================================
// CONSTANTS
// =============================================================================

#define EMPTY_RETURN String::NewFromUtf8(isolate, "{\"data\":[],\"items\":0}")

// =============================================================================
// PERSISTENT DATA
// =============================================================================

struct SGZIndex tfa_idx_;
Nan::Persistent<v8::String> index_file_name_;


// =============================================================================
// PRIVATE FUNCTIONS
// =============================================================================

struct SGZIndex *GetIndex(void) {
    //v8::Local<struct SGZIndex> local_tfa_idx = Nan::New(tfa_idx_);
    //struct SGZIndex *tfa_idx = static_cast<struct SGZIndex *>(*local_tfa_idx);
    return &tfa_idx_;
}

void OpenIndexFile(char *str_new_index_file_name) {
    // Get value from the persistent string:
    v8::Local<v8::String> index_file_name = Nan::New(index_file_name_);

    // Get the persistent Index
    struct SGZIndex *tfa_idx = GetIndex();

    if (strcmp(*String::Utf8Value(index_file_name), str_new_index_file_name) != 0) {
        // If names are different, close the previous index file and open the new one:
        unload_all_index_positions(tfa_idx);
        load_index_from_file(str_new_index_file_name, tfa_idx);
        index_file_name_.Reset(Nan::New(str_new_index_file_name).ToLocalChecked());
    } else {
        // Do nothing
    } 
}

// This function returns "step" number of sequences if step <= MAX_SEQUENCES_TRANSMISSION else it returns MAX_SEQUENCES_TRANSMISSION of sequences
v8::Local<v8::String> GetSequencesFromCurrentPosition(Isolate *isolate, FILE *tfa_handle, SGZip *tfa_gz, SGZIndex *tfa_idx, long int row_num, long int step) {
    long int items = tfa_idx->items;
    bool first_time = true;
    char ch = ' ';
    long int max_seq_bases = 0;
    long int current_seq_bases = 0;
    std::string ch_static = " ";

    v8::Local<v8::String> ret(String::NewFromUtf8(isolate, "{\"data\":["));

    // ********************************************
    // LOOP SEQUENCES JUMPING FROM ONE TO THE OTHER
    // ********************************************

    float jump_distance = 1.0f;

    // Limit for preventing Heap Allocation Failures.
    // For example:
    //   1) MAX_SEQUENCES_TRANSMISSION is 4 and
    //      step = 3
    //      then, distance is 1
    //      It returns one sequence every 1. Total = 3 (step) sequences returned: [0][1][2]
    //   2) MAX_SEQUENCES_TRANSMISSION is 4 and
    //      step = 4
    //      then, distance is 1
    //      It returns one sequence every 1. Total = 4 (step) sequences returned: [0][1][2][3]
    //   3) MAX_SEQUENCES_TRANSMISSION is 4 and
    //      step = 6
    //      then, distance is 2      ceil(step / MAX) = ceil (6 / 4) = ceil(1,5) = 2
    //      It returns one sequence every 2. Total = 3 (<step) sequences returned: [0][2][4]

    if (step <= MAX_SEQUENCES_TRANSMISSION) {
        jump_distance = 1;
    } else {
        jump_distance = step;
        jump_distance /= MAX_SEQUENCES_TRANSMISSION;
        jump_distance = ceil(jump_distance);
    }

    long int jump_to_row = 0;
    for (long int i = row_num; i < row_num + step; i += jump_distance) {

        jump_to_row = i;

        if (first_time == false) {
            ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ","));
        }
        ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, "{\"order\":"));
        ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, to_string(jump_to_row).c_str()));

        if (fzseek(tfa_handle, tfa_gz, tfa_idx, NULL, &jump_to_row, true) == GZ_OK) {

            // Get the sequence ID
            // -------------------

            ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ",\"id\":\""));

            ch = 'a';

            while((!fzeof(tfa_handle, tfa_gz)) && (ch != '\t')) {
                ch = fzgetc(tfa_handle, tfa_gz);

                if (ch != '\t') {
                    ch_static.at(0) = ch;
                    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ch_static.c_str()));
                }
            }

            // Get the sequence 
            // ----------------

            ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, "\",\"seq\":\""));

            current_seq_bases = 0;

            while((!fzeof(tfa_handle, tfa_gz)) && (ch != '\n')) {
                ch = fzgetc(tfa_handle, tfa_gz);

                if (ch != '\n') {
                    ch_static.at(0) = ch;
                    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ch_static.c_str()));
                    current_seq_bases++;
                }
            }

            ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, "\"}"));

            if (current_seq_bases > max_seq_bases) {
                max_seq_bases = current_seq_bases;
            }

            first_time = false;
        }
    }

    if (current_seq_bases > max_seq_bases) {
        max_seq_bases = current_seq_bases;
    }

    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, "],\"items\":"));
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, to_string(items).c_str()));
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ",\"max_seq_bases\":"));
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, to_string(max_seq_bases).c_str()));
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, "}"));

    return ret;
}

// =============================================================================
// PUBLIC FUNCTIONS
// =============================================================================

// If row_num and step are -1 then all the file content is required
void PublicGetSequencesByPos(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    v8::Local<v8::String> ret(String::NewFromUtf8(isolate, ""));

    // Get the persistent Index
    struct SGZIndex *tfa_idx = GetIndex();

    // Check Params
    // ------------
    if ((args.Length() == 3) &&
        (args[0]->IsNumber() == false) &&
        (args[1]->IsNumber() == true) &&
        (args[2]->IsNumber() == true)) {

        // Get Params
        // ----------
        v8::String::Utf8Value file_name(args[0]->ToString()); // *file_name is like c_str()
        long int row_num = args[1]->NumberValue();
        long int step = args[2]->NumberValue();

        // Open T-Fasta File
        // -----------------
        SGZip tfa_gz;
        FILE *tfa_handle = fzopen(*file_name, "r", &tfa_gz);

        if (tfa_handle != NULL) {

            // Load Index if it is not loaded yet
            // ----------------------------------

            OpenIndexFile(tfa_gz.index_file_name);

            if (tfa_idx->items > 0) {

                // If row_num and step are -1 then all the file content is required
                // ----------------------------------------------------------------
                if ((row_num == -1) && (step == -1)) {
                    row_num = 0;
                    step = tfa_idx->items;
                }

                // Reach Desired Sequence
                // ----------------------
                if (fzseek(tfa_handle, &tfa_gz, tfa_idx, NULL, &row_num, false) == GZ_OK) {
                    // Get Sequences
                    // -------------
                    ret = GetSequencesFromCurrentPosition(isolate, tfa_handle, &tfa_gz, tfa_idx, row_num, step);
                }
            } else {
                ret = EMPTY_RETURN;
            }

            // Close the Input File
            // --------------------
            fzclose(tfa_handle, &tfa_gz);
        }
    } else {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "syntax: file row_num step")));
        ret = EMPTY_RETURN;
    }

    // Return Data
    // -----------
    args.GetReturnValue().Set(ret);
}

void PublicCloseFiles(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    
    // Get the persistent Index
    struct SGZIndex *tfa_idx = GetIndex();

    unload_all_index_positions(tfa_idx);


    // Get value from the persistent string:
    v8::Local<v8::String> index_file_name = Nan::New(index_file_name_);

    // Reset the index file name:
    index_file_name_.Reset(Nan::New("").ToLocalChecked()); // Ignore unused variable warning because it is not true

    // Return Data
    // -----------
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "OK"));
}

long int GetFileSize(char *file) {
    long int ret = 0;

    FILE *fp = fopen (file, "r");
    if(fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        ret = ftell(fp);
        fclose(fp);
    }

    return ret;
}

void PublicGetFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    v8::Local<v8::String> ret(String::NewFromUtf8(isolate, ""));

    // Check Params
    // ------------
    if ((args.Length() == 1) &&
        (args[0]->IsNumber() == false)) {

        // Get Params
        // ----------
        v8::String::Utf8Value file_name(args[0]->ToString()); // *file_name is like c_str()

        if ((strcmp(*file_name, "") != 0) && (strlen(*file_name) > 3) &&
            ((*file_name)[strlen(*file_name) - 3] == '.') &&
            ((*file_name)[strlen(*file_name) - 2] == 'g') &&
            ((*file_name)[strlen(*file_name) - 1] == 'z')) {

            SGZip w_gz;
            FILE *w_handle = fzopen(*file_name, "r", &w_gz);


            std::string ch_static = " ";

            if (w_handle != NULL) {
                while (!fzeof(w_handle, &w_gz)) {
                    ch_static.at(0) = fzgetc(w_handle, &w_gz);
                    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ch_static.c_str()));
                }

                fzclose(w_handle, &w_gz);
            }

        } else {
            char *buffer = NULL;

            long int file_size = GetFileSize(*file_name);
            if (file_size != 0) {
                buffer = (char *)malloc((file_size + 1)*(sizeof(char)));
                if (buffer != NULL) {
                    memset(buffer, '\x0', file_size + 1);

                    FILE *fp = fopen (*file_name, "r");

                    if(fp != NULL) {
                        fread(buffer, file_size, sizeof(char), fp);
                    }

                    fclose(fp);

                    ret = String::NewFromUtf8(isolate, buffer);
                    free(buffer);
                    buffer = NULL;
                }
            }
        }
    }

    // Return Data
    // -----------
    args.GetReturnValue().Set(ret);
}

// =============================================================================
// INIT
// =============================================================================

void init(Local<Object> exports) {

    index_file_name_.Reset(Nan::New("").ToLocalChecked());

    NODE_SET_METHOD(exports, "get_sequences_by_pos", PublicGetSequencesByPos);
    NODE_SET_METHOD(exports, "close_files",          PublicCloseFiles);
    NODE_SET_METHOD(exports, "get_statistics",       PublicGetFile);
    NODE_SET_METHOD(exports, "get_gff",              PublicGetFile);
    NODE_SET_METHOD(exports, "get_weights",          PublicGetFile);
}

NODE_MODULE(addon, init)

}  // namespace demo





/*
    // DEBUG *******************************************************************
    FILE *h = fopen("sortida.txt", "a+");
    if (h != NULL) { 
        fprintf(h, "OpenIndexFile::End:  tfa_idx.items = %ld\n", tfa_idx.items);
        fclose(h);
    }
    // DEBUG *******************************************************************
*/

/*
Notes:
    #include <ctime>
    clock_t begin = clock();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, ",\"time\":"));
    ret = v8::String::Concat(ret, String::NewFromUtf8(isolate, to_string(elapsed_secs).c_str()));
*/


