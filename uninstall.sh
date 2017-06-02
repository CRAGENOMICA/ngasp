#!/bin/bash

# docker stop $(docker ps -a -q)
# docker rm $(docker ps -a -q)
# docker rmi -f $(docker images -q)
docker rmi -f development-environment
docker rmi -f compiler-environment
docker rmi -f step2
docker rmi -f step1
docker rmi -f centos

