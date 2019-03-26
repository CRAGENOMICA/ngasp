# ==============================================================================
# NGASP DOCKERFILE
# ==============================================================================
# Usage:
#
#   - Build : docker build -t ngasp .
#   - Run   : xhost +
#             docker run --rm --net host ngasp

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM centos:7

LABEL maintainer="Héctor Gracia <hector.gracia@cragenomica.es>"

RUN mkdir -p /opt/lib
#RUN yum update -y && yum -y clean all

# ****************
# *** Packages ***
# ****************

RUN yum update -y && yum install -y kernel-headers kernel-devel && \
    yum install -y gcc-c++ libstdc++-devel && yum -y clean all
RUN yum install -y make \
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
    ncurses-devel \
    openmpi-devel && yum -y clean all
    
# ****************
# *** Java JDK ***
# ****************

RUN curl -o epel.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm -LOk && \
    rpm -Uvh epel.rpm && yum install -y http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64.rpm http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-headless-1.8.0.131-3.b12.el7_3.x86_64.rpm && yum install -y nodejs && yum clean all

# ==============================================================================
# ENV REQUIREMENTS
# ==============================================================================

ENV JAVA_HOME /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64/jre
ENV PATH "/app/gradle/gradle-3.1/bin:${PATH}"
ENV OPEN_MPI_HOME /opt/lib/openmpi
ENV LD_LIBRARY_PATH "/opt/lib/openmpi/lib:${LD_LIBRARY_PATH}"
ENV PATH "/opt/lib/openmpi/bin:${PATH}"
VOLUME ["/tmp/.X11-unix", "/tmp/.X11-unix"]
ENV DISPLAY :0.0
RUN export DISPLAY=:0.0

# ==============================================================================
# Compilation
# ==============================================================================

# para que continue funcionando todo hace falta que exista la carpeta develop y
# contenga todo lo que hay en src
RUN mkdir /develop 
COPY ./src /develop

#Añado compilacion de las librerias
RUN /bin/bash /develop/compile_all.sh &&\
    rm -rf /tmp/gsl &&\
    rm -rf /tmp/zlib &&\
    rm -rf /tmp/htslib &&\
    rm -rf /tmp/openmpi &&\
    rm -rf /tmp/fastaconvtr &&\
    rm -rf /tmp/ghcaller &&\
    rm -rf /tmp/mstatspop &&\
    rm -rf /tmp/npstat &&\
    rm -rf /develop/.gradle &&\
    rm -rf /develop/source &&\
    rm -rf /develop/webapp/node_modules &&\
    rm -rf /develop/webapp/public &&\
    rm -rf /develop/tests &&\
    rm -rf /develop/data && yum -y clean all


# ==============================================================================
# START
# ==============================================================================

WORKDIR /develop/webapp
#ENTRYPOINT ["/develop/webapp/start_ngasp.sh"]
ENTRYPOINT ["/bin/bash"]