#include <cstddef>
#include <cstdio>
#include <stdint.h> /* int64_t */
#include <string>   /* std::string */
#include <cstring>  /* strlen*/
#include <math.h>   /* pow(base, b) */
#include <iostream> /* cout */

template <class T>
void f(char *type_name, T a) {
    int column = 0;
    int bytes  = 0;
    int bits   = 0;

    for(int t = 0; t < 2; t++) {
        if ((t == 1) && (strcmp(type_name, "char") == 0)) continue;
        column = 25;
        column -= strlen(type_name);

        if (t == 0) {
            column -= strlen("unsigned ");
        }

        for (int i = 0; i < column; i++) {
            std::cout << " ";
        }

        if (t == 0) {
            std::cout << "unsigned ";
        }

        std::cout << type_name;


        int bytes  = (int) sizeof(T);
        int bits   = 8 * bytes;

        if (t == 1) {
            bits--;
            std::cout << ": "
                      << bytes << " bytes. "
                      << bits  << " bits. "
                      << "[-"
                      << std::fixed
                      << pow(2, bits) / 2
                      << ", "
                      << pow(2, bits) / 2
                      << "]"
                      << std::endl;
        } else {
            std::cout << ": "
                      << bytes << " bytes. "
                      << bits  << " bits. "
                      << "[0, "
                      << std::fixed
                      << pow(2, bits)
                      << "]"
                      << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    { char           v; f("char",           v); }
    { short          v; f("short",          v); }
    { int            v; f("int",            v); }
    { long           v; f("long",           v); }
    { long long      v; f("long long",      v); }
    { size_t         v; f("size_t",         v); }
    { float          v; f("float",          v); }
    { void *         v; f("void *",         v); }
    { double         v; f("double",         v); }
    { std::size_t    v; f("std::size_t",    v); }
    { long int       v; f("long int",       v); }
    { int64_t        v; f("int64_t",        v); }
   
    printf("unsigned types have one bit less for the sign.");

    return 0;
}

