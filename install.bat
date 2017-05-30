cd docker
docker-compose -f compose.yml build
cd development-environment
docker build -t development-environment .
cd ..\..

