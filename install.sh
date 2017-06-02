#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    echo "Mac OS X platform detected..."
    cd docker
    docker-compose -f compose.yml build
    cd development-environment
    docker build -t development-environment .
    cd ../..
    # Take an image and make the image its own icon:
    sips -i icons/ngasp_icon.png
    # Extract the icon to its own resource file:
    DeRez -only icns icons/ngasp_icon.png > icons/tmpicns.rsrc
    # append this resource to the file you want to icon-ize.
    Rez -append icons/tmpicns.rsrc -o ./runme.sh
    # Use the resource to set the icon.
    SetFile -a C ./runme.sh
    # clean up.
    rm icons/tmpicns.rsrc
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    echo "GNU/Linux platform detected..."
    cd docker
    docker-compose -f compose.yml build
    cd development-environment
    docker build -t development-environment .
    cd ../..
    NGASP_PATH=`pwd`
    echo "[Desktop Entry]" > ngasp.desktop
    echo "Type=Application" >> ngasp.desktop
    echo "Name=ngasp" >> ngasp.desktop
    echo "Exec=/bin/bash -c 'cd \"\$(dirname %k)\" && $NGASP_PATH/runme.sh'" >> ngasp.desktop
    echo "Icon=$NGASP_PATH/icons/ngasp_icon_black.png" >> ngasp.desktop
    echo "Name[es_ES]=ngasp" >> ngasp.desktop
    chmod +x ngasp.desktop 
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo "32 bits Windows NT platform detected..."
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
    echo "64 bits Windows NT platform detected..."
fi

