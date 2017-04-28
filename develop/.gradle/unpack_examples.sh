# *****************************************************
# This script uncompresses all compressed input files
# *****************************************************

if [ -d /home/ci_ngasp/ngasp/examples ]; then
  cd /home/ci_ngasp/ngasp/examples
else
  if [ -d /Users/ci_ngasp/ngasp/examples ]; then
    cd /Users/ci_ngasp/ngasp/examples
  fi
fi

unzip -o *.zip

