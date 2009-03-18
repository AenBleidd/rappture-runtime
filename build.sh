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

# Fail script on error.
set -e

# You may want to specify a destination directory.  The default is myrappture.

if test $# = 0; then
  destdir=`pwd`/myrappture
else 
  destdir=$1
fi

mkdir -p $destdir

# stage1: tcl, tk
# expat, zlib if enabled with --with-xxx
stage1_flags="--with-expat --with-zlib"

# stage2: blt, htmlwidget, itk, shape, tcllib, tdom, tkimg, tls, vornoi
stage2_flags=""

# stage3: pymol, vtk, dx if enabled
stage3_flags="--with-vtk --with-pymol"
stage3_flags=""

MAKE=make
case $host_os in 
   *Darwin* )
      DYLD_LIBRARY_PATH=$destdir/lib
      export DYLD_LIBRARY_PATH
      ;;
   *Linux*  )
      LD_LIBRARY_PATH=$destdir/lib
      export LD_LIBRARY_PATH
      ;;
   *FreeBSD* )
      MAKE=gmake
      LD_LIBRARY_PATH=$destdir/lib
      export LD_LIBRARY_PATH
      ;;
esac

# X11's xmkmf must be in the PATH to correctly determine where the X11 includes and 
# libraries are located.

PATH=/usr/local/bin:/usr/bin:/bin:/usr/X11R6/bin:/usr/X11/bin:/usr/openwin/bin:$PATH:$destdir/bin

export MAKE PATH

stage1() {
    pwd=`pwd`
    mkdir -p stage1
    cd stage1
    ../runtime/configure --prefix=$destdir --exec_prefix=$destdir $stage1_flags  
    $MAKE all 
    $MAKE install 
    cd $pwd
}

stage2() {
    pwd=`pwd`
    mkdir -p stage2
    cd stage2
    ../runtime/configure --prefix=$destdir --exec_prefix=$destdir $stage2_flags
    $MAKE all
    $MAKE install
    cd $pwd
}

stage3() {
    pwd=`pwd`
    mkdir -p stage3
    cd stage3
    ../runtime/configure --prefix=$destdir --exec_prefix=$destdir $stage3_flags
    $MAKE all
    $MAKE install 
    cd $pwd
}

stage1 2>&1 | tee stage1.log
stage2 2>&1 | tee stage2.log
stage3 2>&1 | tee stage3.log

# Can't assume symbol links to wish or tclsh exist if we are going to use a 
# installed version.  Either create the correct links for don't use "wish" and "tclsh".

# Need these links. 
cd $destdir/bin
ln -sf wish8.4 wish
ln -sf tclsh8.4 tclsh

echo "To use this build, do one of the following"
echo "export PATH=`pwd`:\$PATH"
echo "setenv PATH \"`pwd`:\$PATH\""
exit 0
