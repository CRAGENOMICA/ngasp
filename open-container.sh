# From Linux
NGASP_PATH=`pwd`
cd docker/development-environment
docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /bin/bash

# From Mac OS X
# ip=$(ifconfig en0 | awk '$1=="inet" {print $2}')
# xhost + $ip
# docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -e DISPLAY=$ip:0  -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /bin/bash

