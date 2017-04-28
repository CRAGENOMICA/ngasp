#!/bin/sh
# Experiments from "runexamples_linux.sh"


############################################################
# Constants
############################################################


RED='\033[1;31m'
BLUE='\033[1;34m'
GREEN='\033[0;32m'
NO_COLOR='\033[0m'
TEST_OK='Result: Pass' 
TEST_ERROR='Result: Fail'
NGASP_EXEC='../backend/Debug/ngaSP_backend'
PARAMS='mstatspop -f fasta -i ../examples/MC1R_PigsOutg_aligned.fas -o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g ../examples/MC1R.gff nonsynonymous Nuclear_Universal'

############################################################
# Global Variables
############################################################


############################################################
# Main Function
############################################################

main()
{
	$NGASP_EXEC $PARAMS
# | grep "Segmentation fault"
}

main


