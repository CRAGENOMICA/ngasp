#!/bin/bash

# ==============================================================================
# SOURCE CODE COMPILATION
# ==============================================================================
# Note:
#   This file works inside the docker environment.
# ==============================================================================

cd /develop

# *******************
# *** fastaconvtr ***
# *******************

mkdir /tmp/fastaconvtr
cd /tmp/fastaconvtr
# wget https://bioinformatics.cragenomica.es/numgenomics/people/sebas/software/files/page3_5.zip
# unzip -o page3_5.zip
# cd fastaconvtr_pack
wget https://github.com/CRAGENOMICA/fastaconvtr/archive/master.zip
unzip -o master.zip
cd fastaconvtr-master
gcc ./sources/*.c -lm -o /develop/webapp/bin/fastaconvtr -Wall -pedantic -lz

# **************
# *** npstat ***
# **************

mkdir /tmp/npstat
cd /tmp/npstat
wget https://github.com/lucaferretti/npstat/archive/master.zip
unzip -o master.zip
cd npstat-master
gcc -o /develop/webapp/bin/npstat NPStat-v1.c /usr/local/lib/libgsl.a /usr/local/lib/libgslcblas.a -lm

# *******************
# *** Samtoolslib ***
# *******************

cd /develop
gradle clean -b /develop/.gradle/build_samtoolslib.gradle
gradle build_and_export_lib -b /develop/.gradle/build_samtoolslib.gradle

# ****************
# *** ghcaller ***
# ****************

mkdir /tmp/ghcaller
cd /tmp/ghcaller
# wget https://bioinformatics.cragenomica.es/projects/ghcaller/binaries/ghcaller-mpi_0.2.2_src.tgz 
# tar -xvf ghcaller-mpi_0.2.2_src.tgz
# cd pghcaller-0.2.2
wget https://github.com/CRAGENOMICA/pGHcaller/archive/master.zip
unzip -o master.zip
cd pGHcaller-master
./bootstrap
./configure
make
cp ./src/pghcaller /develop/webapp/bin
cp ./scripts/ghcaller /develop/webapp/bin


# ********************************
# *** mstatspop                ***
# *** Requirements: zlib & gsl ***
# ********************************

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/:
mkdir /tmp/mstatspop
cd /tmp/mstatspop
# wget https://bioinformatics.cragenomica.es/numgenomics/people/sebas/software/files/page3_4.zip
# unzip -o page3_4.zip
# cd mstatspop_pack*
wget https://github.com/CRAGENOMICA/mstatspop/archive/master.zip
unzip -o master.zip
cd mstatspop-master
gcc ./sources/*.c -lgsl -lgslcblas -lm -Wall -DinGSL=1 -O3 -lz -o /develop/webapp/bin/mstatspop



#zlib 1.2.8 installation (dependency)
#
#mkdir -p ./zlib
#wget http://zlib.net/zlib-1.2.8.tar.gz -P ./zlib
#tar -zxvf ./zlib/zlib-1.2.8.tar.gz -C ./zlib
#rm ./zlib/zlib-1.2.8.tar.gz
#cd ./zlib/zlib-1.2.8
#./configure
#make
#sudo make install

#gsl installation (dependency)
mkdir -p /tmp/gsl
    curl -o /tmp/gsl-2.2.tar.gz ftp://ftp.gnu.org/gnu/gsl/gsl-2.2.tar.gz -LOk
    tar -zxvf /tmp/gsl-2.2.tar.gz -C /tmp/gsl && \
    rm /tmp/gsl-2.2.tar.gz && \
    cd /tmp/gsl/gsl-2.2 && \
    ./configure && \
    make && \
    make install




# **************************************
# *** Get the project version number ***
# **************************************

# cd /develop
# RUN /develop/.gradle/get_project_version.sh


# ***************
# *** backend ***
# ***************

cd /develop
gradle build -b .gradle/build_backend.gradle

chmod 777 /develop/webapp/bin/*

# ************************************************************************
# *** Assign docker user permissions to the 'group' and to the 'other' ***
# *** in orther to be accessible from the host                         ***
# ************************************************************************

chmod -R g=u /develop
chmod -R o=u /develop                                                           

