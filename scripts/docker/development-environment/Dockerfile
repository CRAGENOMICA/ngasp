# ==============================================================================
# DEVELOPMENT ENVIRONMENT DOCKERFILE
# ==============================================================================
# 
# Usage:
#
#   - Run   : docker run -it --rm --privileged -p 3000:3000 -e DISPLAY=$DISPLAY -v /home/jjene/all/Projects/NetBeansProjects/ngasp/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /bin/bash
#   - Build : docker build -t development-environment .

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM compiler-environment

# ==============================================================================
# GUI APPS REQUIREMENTS
# ==============================================================================

VOLUME ["/tmp/.X11-unix", "/tmp/.X11-unix"]
ENV DISPLAY :0.0
RUN export DISPLAY=:0.0

# ==============================================================================
# TOOLS
# ==============================================================================

# ****************
# *** netbeans ***
# ****************

# COPY ./netbeans-8.2-linux.sh /tmp/netbeans-8.2-linux.sh
# COPY ./jdk-8u111-nb-8_2-linux-x64.sh /tmp/jdk-8u111-nb-8_2-linux-x64.sh

RUN curl -o /tmp/jdk-8u111-nb-8_2-linux-x64.sh https://bioinformatics.cragenomica.es/projects/ngaSP/jdk/jdk-8u111-nb-8_2-linux-x64.sh -LOk && \
    chmod +x /tmp/jdk-8u111-nb-8_2-linux-x64.sh && \
    /tmp/jdk-8u111-nb-8_2-linux-x64.sh --silent
RUN curl -o /tmp/netbeans-8.2-cpp-linux-x64.sh http://download.netbeans.org/netbeans/8.2/final/bundles/netbeans-8.2-cpp-linux-x64.sh -LOk && \
    chmod +x /tmp/netbeans-8.2-cpp-linux-x64.sh && \
    /tmp/netbeans-8.2-cpp-linux-x64.sh --silent
ENV PATH /usr/local/netbeans-8.2/bin:$PATH

# ***********************
# *** psmisc: killall ***
# ***********************

RUN yum install -y psmisc

#### # *************************************************************
#### # *** This does not solve that Netbeans fonts are too small ***
#### # *************************************************************
#### 
#### RUN yum groupinstall -Y "Fonts"
#### 
#### # Copy local fonts in an indexable place
#### RUN mkdir ~/.fonts
#### COPY fonts ~/.fonts
#### RUN fc-cache -f -v

# ==============================================================================
# START
# ==============================================================================

WORKDIR /app


