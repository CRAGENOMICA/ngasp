# Do not limit memory (--memory 512mb) if you have to compile the backend with Gradle.

docker run -it --rm --privileged --net host -p 3000:3000 -p 3001:3001 -e DISPLAY=$DISPLAY -v `pwd`/develop:/develop -v /tmp/.X11-unix:/tmp/.X11-unix development-environment /bin/bash
