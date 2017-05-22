#!/bin/bash

cd /develop/webapp

# Close previous Node.js & ngasp instances
killall -q node
killall -q ngasp

# Open Node.js
node server.js &
echo
echo "Waiting for NodeJs to start..."
echo
sleep 2

# Open one Local Manager (one instance of ngasp)
./bin/ngasp tcp --ip 0.0.0.0 --port 6969 &
echo
echo "Waiting for local manager to start..."
echo
sleep 2

echo "******************************************"
echo "* Open http://localhost:3000 on the host *"
echo "******************************************"
# xdg-open

firefox http://localhost:3000 &

cd tfaviewer
./start_viewer.sh
cd ..


