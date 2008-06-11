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

stage1() {
    pwd=`pwd`
    mkdir -p stage1
    cd stage1
    STAGE=stage1 ../runtime/configure --prefix=$build_dir \
	--exec_prefix=$build_dir
    make all
    make install
    cd $pwd
}

stage2() {
    pwd=`pwd`
    mkdir -p stage2
    cd stage2
    STAGE=stage2 ../runtime/configure --prefix=$build_dir \
	--exec_prefix=$build_dir
    make all
    make install
    cd $pwd
}

stage3() {
    pwd=`pwd`
    mkdir -p stage3
    cd stage3
    STAGE=stage3 ../runtime/configure --prefix=$build_dir \
	--exec_prefix=$build_dir
    make all
    make install
    cd $pwd
}

rappture() {
    pwd=`pwd`
    mkdir -p stage.rappture
    cd stage.rappture
    ../rappture/configure --prefix=$build_dir \
	--exec_prefix=$build_dir
    make all
    make install
    cd $pwd
}

stage1
stage2
rappture

exit 0
