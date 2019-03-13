# ==============================================================================
# PRODUCTION DOCKERFILE
# ==============================================================================
# 
# Usage:
#
#   - Run   : docker run -it --rm --privileged -p 3000:3000 -e DISPLAY=$DISPLAY -v /home/jjene/all/Projects/NetBeansProjects/ngasp/src:/develop -v /tmp/.X11-unix:/tmp/.X11-unix production /bin/bash
#   - Build : docker build -t production .

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM step2

# ==============================================================================
# GUI APPS REQUIREMENTS
# ==============================================================================

VOLUME ["/tmp/.X11-unix", "/tmp/.X11-unix"]
ENV DISPLAY :0.0
RUN export DISPLAY=:0.0
#RUN xhost +

# *************
# *** git ***
# *************

RUN yum install -y git

# ==============================================================================
# NGASP GIT CODE DOWNLOAD
# ==============================================================================

#TODO: no descargar el master
#TODO: esto tal vez debería estar en el step2
#TODO: el cheout sera del latest supongo

#RUN mkdir /usr
WORKDIR /usr
RUN git clone https://github.com/CRAGENOMICA/ngasp.git
WORKDIR /usr/ngasp
RUN git checkout develop


# ==============================================================================
# START
# ==============================================================================

WORKDIR /usr/ngasp/src/webapp
ENTRYPOINT ["/usr/ngasp/src/webapp/start_ngasp.sh"]
#CMD [""]



