#!/bin/bash

# ==============================================================================
# COMPILER ENVIRONMENT CREATION SCRIPT
# ==============================================================================

# *****************************
# *** Build Required Images ***
# *****************************

cd step1
docker build -t step1 .
cd ..

cd step2
docker build -t step2 .
cd ..

# **********************************
# *** Build compiler environment ***
# **********************************

docker-compose -f compose.yml build

docker-compose -f compose.yml start


