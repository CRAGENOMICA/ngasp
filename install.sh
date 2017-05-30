#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    echo "Mac OS X platform detected..."
    cd docker
    docker-compose -f compose.yml build
    cd development-environment
    docker build -t development-environment .
    cd ../..
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    echo "GNU/Linux platform detected..."
    cd docker
    docker-compose -f compose.yml build
    cd development-environment
    docker build -t development-environment .
    cd ../..
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo "32 bits Windows NT platform detected..."
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
    echo "64 bits Windows NT platform detected..."
fi

