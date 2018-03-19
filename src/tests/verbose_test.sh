#!/bin/sh

############################################################
# ngaSP Configuration
############################################################

NGASP_EXEC='../backend/Debug/ngaSP_backend'
NGASP_PARAMS='verbose -l debug'

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


