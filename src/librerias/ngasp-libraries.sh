mkdir -p /lib64/
mkdir -p /opt/lib/openmpi/lib/
mkdir -p /usr/local/lib/
cd /develop/librerias
mv libboost_iostreams.so.1.53.0 /lib64/libboost_iostreams.so.1.53.0
mv libboost_chrono.so.1.53.0 /lib64/libboost_chrono.so.1.53.0
mv libboost_filesystem.so.1.53.0 /lib64/libboost_filesystem.so.1.53.0
mv libboost_regex.so.1.53.0 /lib64/libboost_regex.so.1.53.0
mv libicuuc.so.50 /lib64/libicuuc.so.50
mv libicui18n.so.50 /lib64/libicui18n.so.50
mv libicudata.so.50 /lib64/libicudata.so.50
mv libboost_system.so.1.53.0 /lib64/libboost_system.so.1.53.0
mv libmpi.so.12 /opt/lib/openmpi/lib/libmpi.so.12
mv libmpi_cxx.so.1 /opt/lib/openmpi/lib/libmpi_cxx.so.1
mv libopen-rte.so.12 /opt/lib/openmpi/lib/libopen-rte.so.12
mv libopen-pal.so.13 /opt/lib/openmpi/lib/libopen-pal.so.13
mv libgsl.so.19 /usr/local/lib/libgsl.so.19
mv libgslcblas.so.0 /usr/local/lib/libgslcblas.so.0
ldconfig -n -v /lib64/
ldconfig -n -v /opt/lib/openmpi/lib/
ldconfig -n -v /usr/local/lib/
#Node instalation, needed for central-manager
#curl -o epel.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm -LOk && \
#    rpm -Uvh epel.rpm 
#yum install -y http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-1.8.0.131-3.b12.el7_3.x86_64.rpm http://vault.centos.org/7.3.1611/updates/x86_64/Packages/java-1.8.0-openjdk-headless-1.8.0.131-3.b12.el7_3.x86_64.rpm && yum clean all
#yum install -y nodejs && yum clean all