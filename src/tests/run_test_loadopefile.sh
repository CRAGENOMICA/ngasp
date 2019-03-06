#!/bin/sh

############################################################
# Constants
############################################################

OPERATIONS_FILE='loadopefile -f cmd -i ./operations_file.txt'
NGASP_EXEC='../backend/Debug/ngaSP_backend'


############################################################
# Valgrind Configuration
############################################################

if [ "$1" == "s" ]; then
  VALGRIND_PARAMS='--leak-check=yes --track-origins=yes --suppressions=ngaSP-supression.txt --gen-suppressions=yes'
else
  VALGRIND_PARAMS='--leak-check=yes --track-origins=yes --suppressions=ngaSP-supression.txt'
fi



valgrind $VALGRID_PARAMS $NGASP_EXEC $OPERATIONS_FILE


