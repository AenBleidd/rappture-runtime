#!/bin/bash

# This is a demonstration build script for the rappture runtime environment.  
# Ideally it should be as simple as 
#
#	configure
#	make
#	make install
#
# Because of build dependencies, Tcl/Tk must be built and installed first.  
# Therefore there are at least 2 stages of configure-make-makeinstall: one for Tcl/Tk, 
# one for the rest of the runtime (and one for visualization - which is optional). 
#
#	mkdir stage1 stage2 stage3 
#
#  	cd stage1
#	../runtime/configure
#	make 
# 	make install
#
#  	cd stage2
#	../runtime/configure
#	make 
# 	make install
#
#  	cd stage3
#	../runtime/configure
#	make 
# 	make install
#
# This is basically what this script does. 
#
# The build normally should be done outside of the runtime directory.  You can
# use create a temporary directory and run configure from within it to create the
# necessary Makefiles and auxillary files to build.  You can dispose of the directory
# once the stage is built and installed.

#
# Notes:  There are several variations of this basic script.
#	  1. a demonstation script to help build rappture.
#	  2. a build script for the nanohub.
#	  3. a build script for the Build-and-test environment.
#
# 	  This script should not perform all three functions. 
#	  The demonstation script is supposed to be simple and obvious.
#	  The nanohub script will handle the peculiarities of the nanohub 
#	  deployment process.  The Build-and-test script is also peculiar 
#	  to the build-and-test environment.

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
stage1_flags="--with-expat --with-zlib"

# stage2: blt, htmlwidget, itk, shape, tcllib, tdom, tkimg, tls, vornoi, vtk
stage2_flags="--with-vtk"

# stage3: pymol, dx if enabled
stage3_flags="--with-pymol"
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

  if test -d "stage1" ; then
    cd stage1
  else 
    mkdir -p stage1
    cd stage1
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
	$stage1_flags  2>&1 | tee config.log
  fi
  $MAKE all 2>&1 | tee make.log
  $MAKE install 2>&1 | tee install.log
  cd $pwd
}

stage2() {
  pwd=`pwd`
  if test -d "stage2" ; then
    cd stage2
  else
    mkdir -p stage2
    cd stage2
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
	$stage2_flags 2>&1 | tee config.log
  fi
  $MAKE all 2>&1 | tee make.log
  $MAKE install 2>&1 | tee install.log
  cd $pwd
}

stage3() {
  pwd=`pwd`
  if test -d "stage3" ; then
    cd stage3
  else
    mkdir -p stage3
    cd stage3
    ../runtime/configure --prefix=$build_dir --exec_prefix=$build_dir \
	$stage3_flags 2>&1 | tee config.log
  fi
  $MAKE all 2>&1 | tee make.log
  $MAKE install 2>&1 | tee install.log
  cd $pwd
}

rappture() {
  pwd=`pwd`
  if test -d "stage.rappture" ; then
    cd stage.rappture
  else
    mkdir -p stage.rappture
    cd stage.rappture
    ../rappture/configure --prefix=$build_dir --exec_prefix=$build_dir \
     $rappture_flags 2>&1 | tee config.log
  fi
  $MAKE all 2>&1 | tee -a make.log
  $MAKE install 2>&1 | tee install.log
  cd $pwd
}

stage1
stage2
stage3
rappture

echo "To use this build, do one of the following"
echo "export PATH=`pwd`:\$PATH"
echo "setenv PATH \"`pwd`:\$PATH\""
exit 0
