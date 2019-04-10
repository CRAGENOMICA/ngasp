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
cd /develop

yum install -y http://ftp.csuc.cat/centos/7.6.1810/updates/x86_64/Packages/kernel-headers-3.10.0-957.10.1.el7.x86_64.rpm \
               http://ftp.csuc.cat/centos/7.6.1810/updates/x86_64/Packages/kernel-devel-3.10.0-957.10.1.el7.x86_64.rpm && \
    yum install -y http://ftp.csuc.cat/centos/7.6.1810/updates/x86_64/Packages/gcc-c%2B%2B-4.8.5-36.el7_6.1.x86_64.rpm \
                   http://ftp.csuc.cat/centos/7.6.1810/updates/x86_64/Packages/libstdc%2B%2B-devel-4.8.5-36.el7_6.1.x86_64.rpm && yum -y clean all
yum install -y http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/make-3.82-23.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/bzip2-1.0.6-13.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/boost-1.53.0-27.el7.x86_64.rpm \
    http://ftp.csuc.cat/centos/7.6.1810/os/x86_64/Packages/boost-devel-1.53.0-27.el7.x86_64.rpm \
    http://ftp.csuc.cat/centos/7.6.1810/os/x86_64/Packages/boost-system-1.53.0-27.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/boost-filesystem-1.53.0-27.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/boost-thread-1.53.0-27.el7.x86_64.rpm \
    http://ftp.csuc.cat/centos/7.6.1810/os/x86_64/Packages/wget-1.14-18.el7.x86_64.rpm \
    http://ftp.csuc.cat/centos/7.6.1810/updates/x86_64/Packages/git-1.8.3.1-20.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/zip-3.0-11.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/unzip-6.0-19.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/psmisc-22.20-15.el7.x86_64.rpm \
    http://mirror.gadix.com/centos/7.6.1810/os/x86_64/Packages/ncurses-devel-5.9-14.20130511.el7_4.x86_64.rpm \
    && yum -y clean all

# ****************
# *** Java JDK ***
# ****************

yum groupinstall -y "Development Tools" && yum clean all

curl -o epel.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm -LOk && \
    rpm -Uvh epel.rpm 
yum install -y http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64.rpm http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-headless-1.8.0.131-3.b12.el7_3.x86_64.rpm && yum clean all
yum install -y nodejs && yum clean all

# ***********
# *** gsl ***
# ***********

mkdir -p /tmp/gsl && \
    curl -o /tmp/gsl-2.2.tar.gz ftp://ftp.gnu.org/gnu/gsl/gsl-2.2.tar.gz -LOk && \
    tar -zxvf /tmp/gsl-2.2.tar.gz -C /tmp/gsl && \
    rm /tmp/gsl-2.2.tar.gz && \
    cd /tmp/gsl/gsl-2.2 && \
    ./configure && \
    make && \
    make install

# ************
# *** zlib ***
# ************

mkdir -p /tmp/zlib && \
    curl -o  /tmp/zlib/zlib-1.2.10.tar.gz http://zlib.net/fossils/zlib-1.2.10.tar.gz -LOk && \
    tar -zxvf /tmp/zlib/zlib-1.2.10.tar.gz -C /tmp/zlib && \
    rm /tmp/zlib/zlib-1.2.10.tar.gz && \
    cd /tmp/zlib/zlib-1.2.10 && \
    ./configure && \
    make && \
    make install

# **************
# *** Htslib ***
# **************
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/:
mkdir -p /tmp/htslib && \
    curl -o /tmp/htslib/htslib-1.3.1.tar.bz2 https://github.com/samtools/htslib/releases/download/1.3.1/htslib-1.3.1.tar.bz2 -LOk && \
    tar jxf /tmp/htslib/htslib-1.3.1.tar.bz2 -C /tmp/htslib && \
    rm /tmp/htslib/htslib-1.3.1.tar.bz2 && \
    cd /tmp/htslib/htslib-1.3.1 && \
    ./configure && \
    make && \
    make install

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
    make install


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
#old yaml, por si no funciona correctamente con la versión 0.6.2
#wget https://github.com/jbeder/yaml-cpp/archive/master.zip && \

mkdir -p /opt/lib/yaml && \
    cd /opt/lib/yaml && \
    wget https://github.com/jbeder/yaml-cpp/tree/yaml-cpp-0.6.2 && \
    unzip -o master.zip && \
    rm master.zip

# *******************
# *** fastaconvtr ***
# *******************

mkdir /tmp/fastaconvtr
cd /tmp/fastaconvtr
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

mkdir /tmp/mstatspop
cd /tmp/mstatspop
wget https://github.com/CRAGENOMICA/mstatspop/archive/master.zip
unzip -o master.zip
cd mstatspop-master
gcc ./sources/*.c -lgsl -lgslcblas -lm -Wall -DinGSL=1 -O3 -lz -o /develop/webapp/bin/mstatspop

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

# yum erase make \
#     kernel-headers \
#     kernel-devel \
#     gcc-c++ \
#     libstdc++-devel \
#     bzip2 \
#     boost-devel \
#     wget \
#     git \
#     zip \
#     unzip \
#     ncurses-devel && yum -y clean all

#yum group remove "Development Tools"

#rm -rf /tmp/gsl &&\
#rm -rf /tmp/zlib &&\
#rm -rf /tmp/htslib &&\
#rm -rf /tmp/openmpi &&\
#rm -rf /tmp/fastaconvtr &&\
#rm -rf /tmp/ghcaller &&\
#rm -rf /tmp/mstatspop &&\
#rm -rf /tmp/npstat &&\
#rm -rf /app &&\
#rm -rf /var/tmp &&\
#rm -rf /usr/include &&\
#rm -rf /develop/.gradle &&\
#rm -rf /develop/source &&\
#rm -rf /develop/tests &&\
#rm -rf /develop/data && yum -y clean all