open -a XQuartz
echo "Waiting XQuartx..."
sleep 5
NGASP_PATH=`pwd`
echo $NGASP_PATH
echo "next sentence only works with net connection"
ip=$(ifconfig en0 | awk '$1=="inet" {print $2}')
echo $ip
xhost + $ip
echo "Opening docker..."
echo "Do:"
echo "  $ cd /develop/webapp"
echo "  $ ./start_ngasp.sh"
echo "If firefox does not run do:"
echo "  $ systemd-machine-id-setup"
docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -e DISPLAY=$ip:0  -v $NGASP_PATH/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /bin/bash

