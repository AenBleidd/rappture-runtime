#!/bin/sh

host_os=`uname -s`
echo $system

base_dir=$HOME
build_dir=$base_dir"/builds/"`date +%Y%m%d`
mkdir -p $build_dir

case $host_os in 
   *Darwin* )
# Lots of broken configure scripts looking for /lib/cpp on the Mac.
# Set CPP manually here.
      CC="gcc -arch i386 -arch ppc"
      CXX="g++ -arch i386 -arch ppc"
      CPP="gcc -E"
      CXXCPP="gcc -E"
      F77="gfortran -arch i386 -arch ppc"
      export CPP CC F77 CXX CXXCPP
      DYLD_LIBRARY_PATH=$build_dir/lib
      export DYLD_LIBRARY_PATH
      config_flags="--without-pymol --without-vtk --with-matlab=no"
      ;;
   *Linux*  )
      LD_LIBRARY_PATH=$build_dir/lib
      export LD_LIBRARY_PATH
      config_flags="--without-pymol --without-vtk --with-matlab=no"
      ;;
esac

PATH=$PATH:$build_dir/bin
cd runtime
./configure --prefix=$build_dir $config_flags
make 
cd ../rappture
./configure --prefix=$build_dir $config_flags
make all
make install
#cp rappture/bin/*`date +%Y%m%d`*.tar.gz $base_dir"/tars/".
exit 0
