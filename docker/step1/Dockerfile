# ==============================================================================
# STEP 1 DOCKERFILE
# ==============================================================================
# 
# Usage:
#
#   - Build : docker build -t step1 .
#   - Run   : docker run -ti --rm step1 /bin/bash
#

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM centos:latest

RUN yum update -y && \
    mkdir -p /app && \
    mkdir -p /opt/lib

# ==============================================================================
# MINIMUM COMPILERS
# ==============================================================================

# ********************
# *** C++ compiler ***
# ********************

RUN yum install -y kernel-headers kernel-devel && \
    yum install -y gcc-c++ libstdc++-devel

# ************
# *** Make ***
# ************

RUN yum install -y make

# ==============================================================================
# TOOLS
# ==============================================================================

# *************
# *** bzip2 ***
# *************

RUN yum install -y bzip2

# ==============================================================================
# RUNTIME LIBRARIES
# ==============================================================================

# ***********
# *** gsl ***
# ***********

RUN mkdir -p /tmp/gsl && \
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

RUN mkdir -p /tmp/zlib && \
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

RUN mkdir -p /tmp/htslib && \
    curl -o /tmp/htslib/htslib-1.3.1.tar.bz2 https://github.com/samtools/htslib/releases/download/1.3.1/htslib-1.3.1.tar.bz2 -LOk && \
    tar jxf /tmp/htslib/htslib-1.3.1.tar.bz2 -C /tmp/htslib && \
    rm /tmp/htslib/htslib-1.3.1.tar.bz2 && \
    cd /tmp/htslib/htslib-1.3.1 && \
    ./configure && \
    make && \
    make install

# *************
# *** boost ***
# *************

RUN yum install -y boost boost-devel boost-system boost-filesystem boost-thread

# ***************
# *** openmpi ***
# ***************

# RUN yum install -y openmpi openmpi-devel

RUN mkdir /tmp/openmpi && \
    cd /tmp/openmpi && \
    curl -o openmpi-1.10.1.tar.bz2 https://www.open-mpi.org/software/ompi/v1.10/downloads/openmpi-1.10.1.tar.bz2 -LOk && \
    tar -jxf openmpi-1.10.1.tar.bz2 && \
    cd openmpi-1.10.1/ && \
    ./configure --prefix=/opt/lib/openmpi && \
    make all && \
    make install
ENV OPEN_MPI_HOME /opt/lib/openmpi
ENV LD_LIBRARY_PATH "/opt/lib/openmpi/lib:${LD_LIBRARY_PATH}"
ENV PATH "/opt/lib/openmpi/bin:${PATH}"

# ****************
# *** samtools ***
# ****************

RUN yum install -y samtools

# ==============================================================================
# START
# ==============================================================================

WORKDIR /app

