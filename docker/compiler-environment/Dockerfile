# ==============================================================================
# COMPILER ENVIRONMENT DOCKERFILE
# ==============================================================================
# 
# Usage:
#
#   - Build : docker build -t compiler-environment .
#   - Interactive : docker run -ti --rm -v /home/jjene/NetBeansProjects/ngasp/develop:/develop compiler-environment /bin/bash
#                   cd /develop
#                   ./compile_all.sh
#   - Automatic   : docker run -ti --rm -v /home/jjene/NetBeansProjects/ngasp/develop:/develop compiler-environment /develop/compile_all.sh 

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM step2

# ==============================================================================
# DEVELOPMENT TOOLS
# ==============================================================================

# *************
# *** wget ***
# *************

RUN yum install -y wget

# *******************
# *** Zip / Unzip ***
# *******************

RUN yum install -y zip unzip

# *************
# *** vim ***
# *************

RUN yum install -y vim

# ==============================================================================
# DEVELOPMENT COMPILERS
# ==============================================================================

# *************************
# *** Development Tools ***
# *************************

RUN yum groupinstall -y "Development Tools"

# ****************
# *** Java JDK ***
# ****************

RUN yum install -y java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64
ENV JAVA_HOME /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64/jre
# Fond out the JAVA_HOME value using "RUN update-alternatives --display java"

# **************
# *** Gradle ***
# **************

RUN mkdir -p /app/gradle && \
    curl -o /app/gradle/gradle-3.1-bin.zip https://services.gradle.org/distributions/gradle-3.1-bin.zip -LOk && \
    unzip -o /app/gradle/gradle-3.1-bin.zip -d /app/gradle && \
    rm /app/gradle/gradle-3.1-bin.zip && \
    echo "export PATH=\$PATH:/app/gradle/gradle-3.1/bin" > /etc/profile.d/gradle.sh && \
    echo "export PATH=\$PATH:/app/gradle/gradle-3.1/bin" >> ~/.bashrc
ENV PATH "/app/gradle/gradle-3.1/bin:${PATH}"


# ==============================================================================
# COMPILATION LIBRARIES
# ==============================================================================

# ***************
# *** ncurses ***
# ***************

RUN yum install -y ncurses-devel

# *********************
# *** openmpi devel ***
# *********************

RUN yum install -y openmpi openmpi-devel

# *************
# *** seqan ***
# *************

#### Not necessary to be installed because the version 2.0.1.0 is
#### stored in the repository
#### 
#### RUN mkdir -p /opt/lib/seqan && \
####     cd /opt/lib/seqan && \
####     wget https://github.com/seqan/seqan/archive/master.zip && \
####     unzip -o master.zip && \
####     rm master.zip

# *************
# *** yaml *** 
# *************

RUN mkdir -p /opt/lib/yaml && \
    cd /opt/lib/yaml && \
    wget https://github.com/jbeder/yaml-cpp/archive/master.zip && \
    unzip -o master.zip && \
    rm master.zip

# ==============================================================================
# GCC / G++ 6.3 (32/64 bits) (The installation lapses more than one hour)
# ==============================================================================

#### # ****************************
#### # *** GMP. GCC Requirement ***
#### # ****************************
#### 
#### RUN mkdir -p /tmp/gmp && \
#### cd /tmp/gmp && \
#### curl -o /tmp/gmp/gmp-6.1.0.tar.bz2 ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-6.1.0.tar.bz2 -LOk && \
#### tar -jxf gmp-6.1.0.tar.bz2 && \
#### cd gmp-6.1.0/ && \
#### ./configure && \
#### make && \
#### make check && \
#### make install && \
#### rm /tmp/gmp/gmp-6.1.0.tar.bz2
#### 
#### # *****************************
#### # *** MPFR. GCC Requirement ***
#### # *****************************
#### 
#### RUN mkdir -p /tmp/mpfr && \
#### cd /tmp/mpfr && \
#### curl -o /tmp/mpfr/mpfr-3.1.4.tar.bz2 ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-3.1.4.tar.bz2 -LOk && \
#### tar -jxf mpfr-3.1.4.tar.bz2 && \
#### cd mpfr-3.1.4/ && \
#### ./configure && \
#### make && \
#### make check && \
#### make install && \
#### rm /tmp/mpfr/mpfr-3.1.4.tar.bz2
#### 
#### # ****************************
#### # *** MPC. GCC Requirement ***
#### # ****************************
#### 
#### RUN mkdir -p /tmp/mpc && \
#### cd /tmp/mpc && \
#### curl -o /tmp/mpc/mpc-1.0.3.tar.gz ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-1.0.3.tar.gz -LOk && \
#### tar -zxvf mpc-1.0.3.tar.gz -C /tmp/mpc && \
#### cd mpc-1.0.3/ && \
#### ./configure && \
#### make && \
#### make check && \
#### make install && \
#### rm /tmp/mpc/mpc-1.0.3.tar.gz
#### 
#### # *******************************************************************************
#### # *** 32 bit libc dev package. GCC Requirement to enable multilib (32/64 bit) ***
#### # *******************************************************************************
#### 
#### RUN yum install -y glibc-devel.i686
#### 
#### # *********************************************
#### # *** GCC 6.3 with c++14. SeqAn Requirement ***
#### # *********************************************
#### 
#### RUN mkdir -p /tmp/gcc && \
#### curl -o /tmp/gcc/gcc-6.3.0.tar.gz ftp://ftp.lip6.fr/pub/gcc/releases/gcc-6.3.0/gcc-6.3.0.tar.gz -LOk && \
#### tar -zxvf /tmp/gcc/gcc-6.3.0.tar.gz -C /tmp/gcc && \
#### cd /tmp/gcc/gcc-6.3.0/ && \
#### ./configure --prefix=/usr/bin --enable-multilib --with-system-zlib && \
#### make && \
#### make install && \
#### rm /tmp/gcc/gcc-6.3.0.tar.gz

# ==============================================================================
# START
# ==============================================================================

WORKDIR /app


