#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    echo "Mac OS X platform detected..."
    open -a XQuartz
    echo "Waiting XQuartx..."
    sleep 10
    NGASP_PATH=`pwd`
    echo $NGASP_PATH
    echo "next sentence only works with net connection"
    ip=$(ifconfig en0 | awk '$1=="inet" {print $2}')
    echo $ip
    xhost + $ip
    echo "Opening docker..."
    docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -e DISPLAY=$ip:0  -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /develop/webapp/start_ngasp.sh
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    echo "GNU/Linux platform detected..."
    NGASP_PATH=`pwd`
    cd docker/development-environment
    # docker run -it --rm --privileged --net host --memory 512mb -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix -v $XAUTH:$XAUTH -e XAUTHORITY=$XAUTH development-environment /bin/bash
    # gnome-terminal -e "XAUTH=`mktemp`;xauth nlist ${DISPLAY}| sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -;docker run -it --rm --privileged --net host -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix -v $XAUTH:$XAUTH -e XAUTHORITY=$XAUTH development-environment /develop/webapp/start_ngasp.sh"
    # gnome-terminal -e "docker run -it --rm --privileged --net host -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /develop/webapp/start_ngasp.sh"
    XAUTH=`mktemp`
    xauth nlist ${DISPLAY}| sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
    # The shm-size is for chrome. Without this option it crashes when changing the window size
    gnome-terminal -e "docker run -it --rm --privileged --net host  --shm-size=1g --memory 1024mb -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix -v $XAUTH:$XAUTH -e XAUTHORITY=$XAUTH development-environment /develop/webapp/start_ngasp.sh"
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo "32 bits Windows NT platform detected..."
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
    echo "64 bits Windows NT platform detected..."
fi

