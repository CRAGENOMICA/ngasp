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
    rm -rf /app &&\
    rm -rf /var/tmp &&\
    rm -rf /develop/.gradle &&\
    rm -rf /develop/source &&\
    rm -rf /develop/tests &&\
    rm -rf /develop/data && yum -y clean all


# ==============================================================================
# START
# ==============================================================================

WORKDIR /develop/webapp
#ENTRYPOINT ["/develop/webapp/start_ngasp.sh"]
ENTRYPOINT ["/bin/bash"]