/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 */
/**
 *  \brief     params.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 12, 2017
 *  \pre
 *  \bug
 *  \warning
 *  \copyright
 */

#include "params.h"

void AddParam(bool counting, char ***argv, std::string param, int &argc, int &i, std::string &debug) {
    if (counting) {
        argc++;
    } else {
        if (i == 0) {
            (*argv) = new char*[argc + 1];
            (*argv)[argc] = NULL;
        } else {
            debug += " ";
        }

        (*argv)[i] = new char[param.length() + 1];    // "pen" length is 3. reserved 3+1 [p][e][n]['\x0]
        strcpy((*argv)[i], param.c_str());
        (*argv)[i][param.length()] = '\x0';
        debug += param;
        i++;
    }
}


