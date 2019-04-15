#posible CI

#TODO esto hay que pensarlo mas, porque ahora mismo es bastante engorroso

#TODO añadir a este docker que guarde los binarios en algún repositorio
docker build -f 'Dockerfile_develop' -t ngasp:develop .

#recuperar los binarios del repositorio anterior y crear el docker con solo localManager
docker build -f 'Dockerfile_localManager' -t ngasp:localManager .
