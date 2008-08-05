#!/bin/bash

# Fail script on error.
set -e

host_os=`uname -s`
echo $system

# Look in current directory and up one level
# for runtime and rappture directories. Set
# base_dir.
if [ -d runtime ]; then
    base_dir=`pwd`
elif [ -d ../runtime ]; then
    cd ..
    base_dir=`pwd`
else
    echo "runtime directory not found. Exiting."
    exit 1
fi
if [ ! -d $base_dir/rappture ]; then
    echo "rappture directory not found. Exiting."
    exit 1
fi

build_dir=$base_dir"/builds/"`date +%Y%m%d`
mkdir -p $build_dir

# build_dir is temporary install directory for the rappture build.
# We'll use this later to tar up the entire distribution.

# stage1: tcl, tk
# expat, zlib if enabled with --with-xxx
stage1_flags=""

# stage2: blt, htmlwidget, itk, shape, tcllib, tdom, tkimg, tls, vornoi
stage2_flags=""

# stage3: pymol, vtk, dx if enabled
stage3_flags="--with-vtk --with-pymol"
# Don't build vtk or pymol yet on BAT.
stage3_flags=""

rappture_flags=""

MAKE=make
case $host_os in 
   *Darwin* )
      DYLD_LIBRARY_PATH=$build_dir/lib
      export DYLD_LIBRARY_PATH
      ;;
   *Linux*  )
      LD_LIBRARY_PATH=$build_dir/lib
      export LD_LIBRARY_PATH
      ;;
   *FreeBSD* )
      MAKE=gmake
      LD_LIBRARY_PATH=$build_dir/lib
      export LD_LIBRARY_PATH
      ;;
esac

PATH=/usr/local/bin:/usr/bin:/bin:/usr/X11R6/bin:/usr/X11/bin:/usr/openwin/bin:$PATH:$build_dir/bin

export MAKE PATH

stage1() {
    pwd=`pwd`
    mkdir -p stage1
    cd stage1
    $base_dir/runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$stage1_flags  2>&1 | tee config.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE all 2>&1 | tee make.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE install 2>&1 | tee install.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    cd $pwd
}

stage2() {
    pwd=`pwd`
    mkdir -p stage2
    cd stage2
    $base_dir/runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
	$stage2_flags 2>&1 | tee config.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE all 2>&1 | tee make.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE install 2>&1 | tee install.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    cd $pwd
}

stage3() {
    pwd=`pwd`
    mkdir -p stage3
    cd stage3
    $base_dir/runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$stage3_flags 2>&1 | tee config.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE all 2>&1 | tee make.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE install 2>&1 | tee install.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi
    cd $pwd
}

rappture() {
    pwd=`pwd`
    mkdir -p stage.rappture
    cd stage.rappture
    $base_dir/rappture/configure --prefix=$build_dir --exec_prefix=$build_dir \
    	$rappture_flags 2>&1 | tee config.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE all 2>&1 | tee -a make.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    $MAKE install 2>&1 | tee install.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
	exit 4
    fi

    cd $pwd
}

stage1
stage2
stage3
rappture

# Need these links. 
cd $build_dir/bin
ln -sf wish8.4 wish
ln -sf tclsh8.4 tclsh

echo "To use this build, do one of the following"
echo "export PATH=`pwd`:\$PATH"
echo "setenv PATH \"`pwd`:\$PATH\""
exit 0
