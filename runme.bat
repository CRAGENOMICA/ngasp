set NGASP_PATH=%cd%
cd docker\development-environment
docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -e DISPLAY=%DISPLAY% -v %NGASP_PATH%\develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /develop/webapp/start_ngasp.sh

