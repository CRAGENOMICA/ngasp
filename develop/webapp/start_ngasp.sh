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
sleep 5

# Open one Local Manager (one instance of ngasp)
./bin/ngasp tcp --ip 0.0.0.0 --port 6969 &
echo
echo "Waiting for local manager to start..."
echo
sleep 5

cd tfaviewer
# Do not do: ./stop_viewer.sh
./start_viewer.sh
cd ..

echo
echo "Opening http://localhost:3000..."
echo
systemd-machine-id-setup
google-chrome --no-sandbox --disable-bundled-ppapi-flash --app=http://localhost:3000
# xdg-open

