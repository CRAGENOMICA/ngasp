REM Do not limit memory (--memory 512mb) if you have to compile the backend with Gradle.


set NGASP_PATH=%cd%
docker run -it --rm --privileged -p 3000:3000 -p 3001:3001 -v %NGASP_PATH%\\develop:/develop development-environment /bin/bash
