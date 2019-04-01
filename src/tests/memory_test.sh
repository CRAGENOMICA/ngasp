#!/bin/sh

############################################################
# ngaSP Configuration
############################################################

NGASP_EXEC='/develop/webapp/bin/ngasp'
#NGASP_EXEC='../backend/Debug/ngaSP_backend'
# NGASP_PARAMS='mstatspop -f fasta -i ../examples/MC1R_PigsOutg_aligned.fas -o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g ../examples/MC1R.gff nonsynonymous Nuclear_Universal'
# NGASP_PARAMS='verbose -l silent'
# NGASP_PARAMS='-h'
# NGASP_PARAMS='-v debug'
NGASP_PARAMS='help'

############################################################
# Valgrind Configuration
############################################################


if [ "$1" == "s" ]; then
  VALGRIND_PARAMS='--leak-check=yes --track-origins=yes --suppressions=ngaSP-supression.txt --gen-suppressions=yes'
else
  VALGRIND_PARAMS='--leak-check=yes --track-origins=yes --suppressions=ngaSP-supression.txt'
fi


############################################################
# Main Function
############################################################

main()
{
	valgrind $VALGRIND_PARAMS $NGASP_EXEC $NGASP_PARAMS
}

main


