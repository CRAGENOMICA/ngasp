# Discard changes

git checkout .

# Remove temp files

rm -f .swp
rm -f ./develop/webapp/tmp/*

# Get last source code 

git pull

# Reinstall

./install.sh
