#posible CI

#TODO cambiar el nombre a dockerfile_compile
docker build -f 'Dockerfile_1GB' -t ngasp-c .
#este paso no esta muy bien pensado
#una vez compilado todo, sacar laas librerias y los binarios y construir el docker lijero
docker run --rm --net host -v `pwd`/src/librerias:/develop/librerias -v `pwd`/src/webapp/bin:/develop/webapp/bin --entrypoint /develop/librerias/extract_libraries.sh ngasp
docker build -f Dockerfile -t ngasp .
