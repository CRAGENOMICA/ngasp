#!/bin/bash

cd addons/tfa_addon
% export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64:/opt/lib/openmpi/lib:/opt/lib/openmpi/lib:/opt/lib/openmpi/lib:/opt/lib/openmpi/lib
node-gyp configure
node-gyp build
cd ../..

