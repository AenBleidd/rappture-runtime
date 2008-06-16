#!/bin/sh

host_os=`uname -s`
echo $system

base_dir=`pwd`
build_dir=$base_dir"/builds/"`date +%Y%m%d`
mkdir -p $build_dir

stage1_flags=""
stage2_flags=""
stage3_flags=""
rappture_flags=""

case $host_os in 
   *Darwin* )
      DYLD_LIBRARY_PATH=$build_dir/lib
      export DYLD_LIBRARY_PATH
      ;;
   *Linux*  )
      LD_LIBRARY_PATH=$build_dir/lib
      export LD_LIBRARY_PATH
      ;;
esac

PATH=/usr/local/bin:/usr/bin:/bin:/usr/X11R6/bin:/usr/X11/bin:/usr/openwin/bin:$PATH:$build_dir/bin

stage1() {
    pwd=`pwd`
    mkdir -p stage1
    cd stage1
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$stage1_flags
    make -w all || exit 1
    make -w install || exit 1
    cd $pwd
}

stage2() {
    pwd=`pwd`
    mkdir -p stage2
    cd stage2
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
	$stage2_flags
    make -w all || exit 2
    make -w install || exit 2
    cd $pwd
}

stage3() {
    pwd=`pwd`
    mkdir -p stage3
    cd stage3
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$stage3_flags
    make -w all || exit 3
    make -w install || exit 3
    cd $pwd
}

rappture() {
    pwd=`pwd`
    mkdir -p stage.rappture
    cd stage.rappture
    ../rappture/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$rappture_flags
    make -w all || exit 4
    make -w install || exit 4
    cd $pwd
}

stage1
stage2
stage3
rappture

exit 0
