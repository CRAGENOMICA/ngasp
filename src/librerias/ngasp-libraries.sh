mkdir -p /lib64/
mkdir -p /opt/lib/openmpi/lib/
cd /develop/librerias
mv libboost_iostreams.so.1.53.0 /lib64/libboost_iostreams.so.1.53.0
mv libboost_chrono.so.1.53.0 /lib64/libboost_chrono.so.1.53.0
mv libboost_filesystem.so.1.53.0 /lib64/libboost_filesystem.so.1.53.0
mv libboost_regex.so.1.53.0 /lib64/libboost_regex.so.1.53.0
mv libncurses.so.5 /lib64/libncurses.so.5
mv libtinfo.so.5 /lib64/libtinfo.so.5
mv libboost_system.so.1.53.0 /lib64/libboost_system.so.1.53.0
mv libz.so.1 /lib64/libz.so.1
mv libstdc++.so.6 /lib64/libstdc++.so.6
mv libm.so.6 /lib64/libm.so.6
mv libgcc_s.so.1 /lib64/libgcc_s.so.1
mv libpthread.so.0 /lib64/libpthread.so.0
mv libc.so.6 /lib64/libc.so.6
mv libbz2.so.1 /lib64/libbz2.so.1
mv librt.so.1 /lib64/librt.so.1
mv libicuuc.so.50 /lib64/libicuuc.so.50
mv libicui18n.so.50 /lib64/libicui18n.so.50
mv libicudata.so.50 /lib64/libicudata.so.50
mv libdl.so.2 /lib64/libdl.so.2
mv ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
mv libmpi.so.12 /opt/lib/openmpi/lib/libmpi.so.12
mv libmpi_cxx.so.1 /opt/lib/openmpi/lib/libmpi_cxx.so.1
mv libopen-rte.so.12 /opt/lib/openmpi/lib/libopen-rte.so.12
mv libopen-pal.so.13 /opt/lib/openmpi/lib/libopen-pal.so.13
mv libutil.so.1 /lib64/libutil.so.1

yum install node && yum clean all