/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
/**
 *  \brief     CFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CFile.h"
#include "CStringTools.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <streambuf>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// The instruction "fdin_.exceptions" is like to set exceptions = true
// to file operations.
// So, all file operations have been surrounded by try catch and if the catch
// is reached then the function where is the try/catch returns false.

CFile::CFile(const std::string &file_name) {
    set_name(file_name);
    set_status(FileStatus::CLOSED);
}

CFile::~CFile() {
    set_name("");
    set_status(FileStatus::CLOSED);
}

bool CFile::Open() {
    bool success = false;

    try {
        if (status() == FileStatus::CLOSED) {
            fdin_.open(name().c_str(), std::ifstream::in);

            fdin_.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            if (fdin_.is_open()) {
                set_status(FileStatus::OPEN);
                success = true;
            }
        }
    } catch (...) {
    }

    return success;
}

bool CFile::ReplaceContentBy(const std::string &file_name,
        const std::string &buffer) {
    bool success = true;

    std::ofstream ofs(file_name, std::ofstream::out);

    ofs << buffer;

    ofs.close();

    return success;
}

bool CFile::Append(const std::string &file_name,
        const std::string &buffer) {
    bool success = true;

    try {
        std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::app);
        ofs << buffer;
        ofs.close();
    } catch (...) {
        std::cout << "CFile::Append error for file '" << file_name << "'..." << std::endl;
    }

    return success;
}

bool CFile::Close() {
    bool success = false;

    try {
        if (status() == FileStatus::OPEN) {
            fdin_.close();

            if (!fdin_.is_open()) {
                set_status(FileStatus::CLOSED);
                success = true;
            }
        }
    } catch (...) {
    }

    return success;
}

bool CFile::ReadLine(std::string *line) {
    // Version 1
    //  bool success = false;
    //
    //  if (status() == FileStatus::OPEN) {
    //    if (std::getline(fdin_, *line) > 0) {
    //      success = true;
    //    }
    //  }
    //
    //  return success;

    // Version 2
    //  bool success = false;
    //
    //  if (status() == FileStatus::OPEN) {
    //    try {
    //      while(std::getline(fdin_, *line));
    //      success = true;
    //    } catch(std::ifstream::failure e){
    //    }
    //  }
    //
    //  return success;
    //

    bool success = false;

    try {
        if (status() == FileStatus::OPEN) {
            if (std::getline(fdin_, *line)) {
                success = true;
            }
        }
    } catch (...) {
    }

    return success;
}

//std::string CFile::ReadAll(void) {
//  std::string ret;
//  std::string line;
//
//  while(ReadLine(&line)) {
//    ret += line;
//    ret += "\n";
//  }
//
//  return ret;
//}

bool CFile::ReadAll(const std::string &file_name, std::string &buffer) {
    bool success = true;

    try {
        std::ifstream ifs(file_name);
        ifs.seekg(0, std::ios::end);
        buffer.reserve(ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        buffer.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();
    } catch (...) {
        std::cout << "CFile::ReadAll error for file '" << file_name << "'..." << std::endl;
    }

    return success;
}

bool CFile::WriteLine(const std::string &line) {
    bool success = false;

    return success;
}

bool CFile::Remove(const std::string &file_name) {
    return (remove(file_name.c_str()) == 0);
}

bool CFile::CreateDirectories(const std::string &dir_path) {
    bool ret = false;

#ifdef __WIN32__
    std::string win_path = dir_path;
    CStringTools::Replace(win_path, "/", "\\");
    mkdir(win_path.c_str());
#else
    mkdir(dir_path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
#endif  


    /*#include <boost/filesystem.hpp>
     * -lboost_system
     * boost::filesystem::path dir(dir_path.c_str());
    if(boost::filesystem::create_directories(dir)) {
      ret = true;
    }
     * */
    return ret;
}

bool CFile::Exists(const std::string &file_name) {
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

std::string CFile::GetCurrentWorkingDirectory(void) {
    std::string ret;
    char cCurrentPath[FILENAME_MAX];
    if (GetCurrentDir(cCurrentPath, sizeof (cCurrentPath))) {
        cCurrentPath[sizeof (cCurrentPath) - 1] = '\0'; // not really required
        ret = cCurrentPath;
    } else {
        ret = errno;
    }

    return ret;
}

/*
 * file_name : "/home/jjene/Documents/contacts.txt"
 * return    : "/home/jjene/Documents/contacts"
 */
std::string CFile::GetPathFileNameWithoutExtension(std::string file_name) {
    std::string ret;

    std::size_t loc_end = file_name.find_last_of(".");
    ret = file_name.substr(0, loc_end);

    return ret;
}

/*
 * file_name : "/home/jjene/Documents/contacts.txt"
 * return    : "/home/jjene/Documents/" <---- with the last '/'
 */
std::string CFile::GetPathFromFileName(std::string file_name) {
    std::string ret;

    std::size_t loc_end = file_name.find_last_of("/");
    ret = file_name.substr(0, loc_end);
    ret += "/";

    return ret;   
}

/*
 * file_name : "/home/jjene/Documents/contacts.txt"
 * return    : "contacts"
 */
std::string CFile::GetFileNameWithoutExtension(std::string file_name) {
    std::string ret;

    std::size_t loc_start = file_name.find_last_of("/") + 1;
    std::size_t loc_end = file_name.find_last_of(".");
    ret = file_name.substr(loc_start, loc_end);

    return ret;
}

/*
 * file_name : "/home/jjene/Documents/contacts.txt"
 * return    : "txt"
 */
std::string CFile::GetExtensionFromFileName(std::string file_name) {
    std::string ret;

    std::size_t loc = file_name.find_last_of(".");
    ret = file_name.substr(loc + 1);

    return ret;
}

/*
 * Case 1: "with iteration_value"
 * file_name : "/home/jjene/Documents/contacts.txt"
 * iteration_number: 5
 * iteration_value: chromosome
 * return    : "/home/jjene/Documents/contacts_chromosome_5.txt"
 * 
 * Case 2: "without iteration_value"
 * file_name : "/home/jjene/Documents/contacts.txt"
 * iteration_number: 5
 * iteration_value: 
 * return    : "/home/jjene/Documents/contacts_5.txt"
 */
std::string CFile::ConcatenateIterationToFilePathName(std::string file_name, int64_t iteration_number, std::string iteration_value) {
    std::string path_name;

    std::size_t loc_end = file_name.find_last_of(".");
    path_name = file_name.substr(0, loc_end);

    //if (iteration_value != "") {
    //    path_name += "_";
    //    path_name += iteration_value;
    //}

    path_name += ".iteration";

    path_name += ".";
    path_name += std::to_string(iteration_number);

    path_name += ".";
    path_name += GetExtensionFromFileName(file_name);

    return path_name;
}

#define POSITION_FILE_EXTENSION ".pos"

  
void CFile::MoveToLastAccessedPosition(const std::string & file_name, std::ifstream & file) {
    std::string BED_last_pos = file_name + POSITION_FILE_EXTENSION;
    std::string buffer;
    std::streampos last_pos = 0;

    // Get the last file read position
    
    if (CFile::Exists(BED_last_pos)) {
        if (CFile::ReadAll(BED_last_pos, buffer)) { // Get the value as string
            std::streamoff aux = 0; // Convert the string into the intermediate streamoff type
            std::istringstream ss(buffer);
            ss >> aux;
            last_pos = aux; // Convert the streamoff into the final streampos type
        }
    }

    // Move to the last read position

    file.seekg(last_pos, std::ios::cur);
}

// last_position is file.tellg() but it can not be executed inside the function because the current position maybe it is not
// the last position that we want to store.
void CFile::StoreLastAccessedPosition(const std::string & file_name, std::ifstream & file, std::streampos last_position) {
    std::string BED_last_pos = file_name + POSITION_FILE_EXTENSION;
    std::string buffer;
        
    if (last_position == file.end) {
        // Remove the position file
        CFile::Remove(BED_last_pos);
    } else {        
        // Save position on file

        std::streamoff aux = last_position; // Convert the streampos into the intermediate streamoff type
        buffer = CStringTools::ToString(aux); // Covert the streamoff  to the final string type
        CFile::ReplaceContentBy(BED_last_pos, buffer); // Save the pos as string
    }
}
