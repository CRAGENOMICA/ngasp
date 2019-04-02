#!/bin/bash

# ==============================================================================
# SOURCE CODE COMPILATION
# ==============================================================================
# Note:
#   This file works inside the docker environment.
# ==============================================================================

# ****************
# *** Packages ***
# ****************

mkdir -p /opt/lib
mkdir -p /app

#TOCHECK quito el update por ahora
#yum update -y &&
yum install -y kernel-headers kernel-devel && \
    yum install -y gcc-c++ libstdc++-devel && yum -y clean all
yum install -y make \
    bzip2 \
    boost \
    boost-devel \
    boost-system \
    boost-filesystem \
    boost-thread \
    wget \
    git \
    zip \
    unzip \
    psmisc \
    ncurses-devel && yum -y clean all

# ****************
# *** Java JDK ***
# ****************

yum groupinstall -y "Development Tools" && yum clean all

curl -o epel.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm -LOk && \
    rpm -Uvh epel.rpm 
yum install -y http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64.rpm http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-headless-1.8.0.131-3.b12.el7_3.x86_64.rpm && yum clean all
yum install -y nodejs && yum clean all

cd /develop

# ***********
# *** gsl ***
# ***********

mkdir -p /tmp/gsl && \
    curl -o /tmp/gsl-2.2.tar.gz ftp://ftp.gnu.org/gnu/gsl/gsl-2.2.tar.gz -LOk && \
    tar -zxvf /tmp/gsl-2.2.tar.gz -C /tmp/gsl && \
    rm /tmp/gsl-2.2.tar.gz && \
    cd /tmp/gsl/gsl-2.2 && \
    ./configure --prefix=/opt/lib/gsl && \
    make && \
    make install && rm -rf /tmp/gsl

# ************
# *** zlib ***
# ************

mkdir -p /tmp/zlib && \
    curl -o  /tmp/zlib/zlib-1.2.10.tar.gz http://zlib.net/fossils/zlib-1.2.10.tar.gz -LOk && \
    tar -zxvf /tmp/zlib/zlib-1.2.10.tar.gz -C /tmp/zlib && \
    rm /tmp/zlib/zlib-1.2.10.tar.gz && \
    cd /tmp/zlib/zlib-1.2.10 && \
    ./configure --prefix=/opt/lib/zlib && \
    make && \
    make install && rm -rf /tmp/zlib

# **************
# *** Htslib ***
# **************

mkdir -p /tmp/htslib && \
    curl -o /tmp/htslib/htslib-1.3.1.tar.bz2 https://github.com/samtools/htslib/releases/download/1.3.1/htslib-1.3.1.tar.bz2 -LOk && \
    tar jxf /tmp/htslib/htslib-1.3.1.tar.bz2 -C /tmp/htslib && \
    rm /tmp/htslib/htslib-1.3.1.tar.bz2 && \
    cd /tmp/htslib/htslib-1.3.1 && \
    ./configure --prefix=/opt/lib/htslib && \
    make && \
    make install && rm -rf /tmp/htslib

# ***************
# *** openmpi ***
# ***************

mkdir /tmp/openmpi && \
    cd /tmp/openmpi && \
    curl -o openmpi-1.10.1.tar.bz2 https://www.open-mpi.org/software/ompi/v1.10/downloads/openmpi-1.10.1.tar.bz2 -LOk && \
    tar -jxf openmpi-1.10.1.tar.bz2 && \
    cd openmpi-1.10.1/ && \
    ./configure --prefix=/opt/lib/openmpi && \
    make all && \
    make install && rm -rf /tmp/openmpi


# **************
# *** Gradle ***
# **************

mkdir -p /app/gradle && \
    curl -o /app/gradle/gradle-3.1-bin.zip https://services.gradle.org/distributions/gradle-3.1-bin.zip -LOk && \
    unzip -o /app/gradle/gradle-3.1-bin.zip -d /app/gradle && \
    rm /app/gradle/gradle-3.1-bin.zip && \
    echo "export PATH=\$PATH:/app/gradle/gradle-3.1/bin" > /etc/profile.d/gradle.sh && \
    echo "export PATH=\$PATH:/app/gradle/gradle-3.1/bin" >> ~/.bashrc

# *************
# *** yaml *** 
# *************

mkdir -p /opt/lib/yaml && \
    cd /opt/lib/yaml && \
    wget https://github.com/jbeder/yaml-cpp/archive/master.zip && \
    unzip -o master.zip && \
    rm master.zip

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

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/lib/zlib/:/opt/lib/gsl/
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

#ya esta en el dockerfile
#gsl installation (dependency)
# mkdir -p /tmp/gsl
#     curl -o /tmp/gsl-2.2.tar.gz ftp://ftp.gnu.org/gnu/gsl/gsl-2.2.tar.gz -LOk
#     tar -zxvf /tmp/gsl-2.2.tar.gz -C /tmp/gsl && \
#     rm /tmp/gsl-2.2.tar.gz && \
#     cd /tmp/gsl/gsl-2.2 && \
#     ./configure && \
#     make && \
#     make install


# ***************
# *** chrome  ***
# ***************

#yum -y install mesa-dri-drivers libexif libcanberra-gtk2 libcanberra; yum clean all
#wget -O /root/google-chrome-stable_current_x86_64.rpm "https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm" 
#yum -y install /root/google-chrome-stable_current_x86_64.rpm; yum clean all
#dbus-uuidgen > /etc/machine-id
#yum install -y chromium
#yum -y install  liberation-mono-fonts  liberation-narrow-fonts liberation-sans-fonts  liberation-serif-fonts
#yum clean all && rm -rf /root/google-chrome-stable_current_x86_64.rpm


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

# ***************
# *** Clean ***
# ***************

yum erase kernel-headers \
    kernel-devel \
    gcc-c++ \
    libstdc++-devel \
    make \
    bzip2 \
    boost-devel \
    wget \
    git \
    zip \
    unzip \
    ncurses-devel && yum -y clean all

yum group remove "Development Tools"

rm -rf /tmp/gsl &&\
rm -rf /tmp/zlib &&\
rm -rf /tmp/htslib &&\
rm -rf /tmp/openmpi &&\
rm -rf /tmp/fastaconvtr &&\
rm -rf /tmp/ghcaller &&\
rm -rf /tmp/mstatspop &&\
rm -rf /tmp/npstat &&\
rm -rf /app &&\
rm -rf /var/tmp &&\
rm -rf /usr/include &&\
rm -rf /develop/.gradle &&\
rm -rf /develop/source &&\
rm -rf /develop/tests &&\
rm -rf /develop/data && yum -y clean all