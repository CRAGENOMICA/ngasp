#posible CI

#TODO esto hay que pensarlo mas, porque ahora mismo es bastante engorroso

docker build -f 'Dockerfile_develop' -t ngasp:develop .
#este paso no esta muy bien pensado
#una vez compilado todo, sacar las librerias y los binarios y construir el docker lijero
docker run --rm --net host -v `pwd`/src/librerias:/develop/librerias -v `pwd`/src/webapp/bin:/develop/webapp/bin --entrypoint /develop/librerias/extract_libraries.sh ngasp:develop
docker build -f 'Dockerfile_localManager' -t ngasp:localManager .
