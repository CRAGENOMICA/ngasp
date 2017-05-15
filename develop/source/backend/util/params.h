/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 */
/**
 *  \brief     params.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 12, 2017
 *  \pre
 *  \bug
 *  \warning
 *  \copyright
 *  \usage
                START_PARAMS
                    ADD_PARAM("samtools");
                    ADD_PARAM("mpileup");
                    ADD_PARAM("-q");
                    ADD_PARAM("20");
                    ADD_PARAM("-Q");
                    ADD_PARAM("20");
                    ADD_PARAM("-B");
                    ADD_PARAM("-f");
                    ADD_PARAM("reference.fa");
                    ADD_PARAM("-o");
                    ADD_PARAM("ouput.mpileup");
                    ADD_PARAM("input_1.bam");
                    ADD_PARAM("input_2.bam");
                END_PARAMS

                int ret = 0;
                if ((ret = samtools_main(argc, (*argv))) != 0) {
                    ERROR_MSG << "samtools mpileup did not work. Error code = " << ret << "..."  END_MSG;
                }

                REMOVE_PARAMS
 */

#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <string.h>

#define START_PARAMS char ***argv = new char**[1]; int argc = 0; int params_i = 0; std::string params_debug; for (int params_t = 0; params_t < 2; params_t++) { // two iterations: the first one counts the number of parameters and the second adds those parameters to the argv structure.
#define ADD_PARAM(p) AddParam((params_t==0), argv, p, argc, params_i, params_debug);
#define END_PARAMS } DEBUG_MSG << params_debug END_MSG;
#define REMOVE_PARAMS for (params_i = 0; params_i < argc; params_i++) { if ((*argv)[params_i] != NULL) { delete (*argv)[params_i]; (*argv)[params_i] = NULL; } } delete [](*argv);  delete argv;

void AddParam(bool counting, char ***argv, std::string param, int &argc, int &i, std::string &debug);

#endif /*PARAMS_H */
