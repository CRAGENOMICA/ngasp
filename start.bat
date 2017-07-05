set NGASP_PATH=%cd%
start cmd /k docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -v %NGASP_PATH%\\develop:/develop development-environment /bin/bash -c "/develop/webapp/start_ngasp_win.sh"


sleep 5
start microsoft-edge:http://localhost:3000

REM /develop/webapp/start_ngasp_win.sh

REM If /develop volume is empty in windows container:
REM    1) Docker > Settings > Shared Drives > [x] C
REM If it continues empty:
REM    1) Docker > Reset > Reset to factory defaults...
REM    2) Docker > Settings > Shared Drives > [x] C
