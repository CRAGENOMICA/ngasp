#!/bin/sh

############################################################
# Constants
############################################################

OPERATIONS_FILE='./operations_file.txt'
NGASP_EXEC='/develop/webapp/bin/ngasp'
#NGASP_EXEC='../backend/Debug/ngaSP_backend'


############################################################
# Execute stdin test
############################################################

cat $OPERATIONS_FILE | $NGASP_EXEC -


