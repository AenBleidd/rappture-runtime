AC_INIT([rappture-runtime],[1.9])
AC_CONFIG_SRCDIR([README])

AC_PREFIX

#------------------------------------------------------------------------
# Handle the --prefix=... option
#------------------------------------------------------------------------

if test "${prefix}" = "NONE"; then
    prefix=/usr/local
fi
if test "${exec_prefix}" = "NONE"; then
    exec_prefix=$prefix
fi
libdir=$exec_prefix/lib
includedir=$prefix/include

topsrcdir=`cd $srcdir; pwd`
RR_SRC_DIR=`pwd`
AC_SUBST(RR_SRC_DIR)

dnl find and test the C compiler
AC_PROG_CC
AC_LANG_C

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_HEADER_STDC
AC_CHECK_FUNC(atol,,[AC_MSG_ERROR([oops! no atol ?!?])])

blt=blt2.4z
cmake=cmake-2.8.12.2
expat=expat-2.0.1
expect=expect5.45
gdcm=gdcm-2.4.1
htmlwidget=htmlwidget-3a14
itcl=itcl3.3
itk=itk3.3
shape=shape0.4/unix
##sqlite=sqlite-3071502
sqlitetcl=sqlite-3071502/tea
tcl=tcl8.4.19/unix
tcllib=tcllib-1.12
tdom=tDOM-0.8.2
tk=tk8.4.19/unix
tkimg=tkimg1.3
tls=tls1.6
voronoi=voronoi
vtk=vtk-6.2.0
vtk_dicom=vtk-dicom
zlib=zlib
glew=glew

# Option default 
# 
default_blt=yes
default_cmake=no
default_expat=no
default_expect=yes
default_gdcm=no
default_htmlwidget=yes
default_itcl=yes
default_itk=yes
default_matlab=yes
default_shape=yes
#default_sqlite=yes
default_sqlitetcl=yes
default_tcl=yes
default_tcllib=yes
default_tdom=yes
default_tk=yes
default_tkimg=yes
default_tls=yes
default_voronoi=yes
default_vtk=no
default_vtk_dicom=no
default_zlib=no
default_glew=no

AC_ARG_ENABLE(64bit,       [  --enable-64bit              Enable 64bit support (where applicable)])
X86_64=
if test "x$enable_64bit" != "x" ; then
    echo Enabling 64-bit support
    X86_64="--enable-64bit"
fi

AC_ARG_WITH([blt],
  [AS_HELP_STRING([--with-blt[=DIR]], 
    [Build blt @<:@default=yes@:>@])], 
	[], [with_blt=$default_blt])

AC_ARG_WITH([cmake],
  [AS_HELP_STRING([--with-cmake[=DIR]], 
     [Build cmake @<:@default=yes@:>@])],
        [], [with_cmake=$default_cmake])

AC_ARG_WITH([expat],
  [AS_HELP_STRING([--with-expat[=DIR]], 
    [Build expat @<:@default=yes@:>@])], 
	[], [with_expat=$default_expat])

AC_ARG_WITH([expect],
  [AS_HELP_STRING([--with-expect[=DIR]], 
    [Build expect @<:@default=yes@:>@])], 
	[], [with_expect=$default_expect])

AC_ARG_WITH([gdcm],
  [AS_HELP_STRING([--with-gdcm[=DIR]], 
    [Build gdcm @<:@default=no@:>@])], 
	[], [with_gdcm=$default_gdcm])

AC_ARG_WITH([htmlwidget],
  [AS_HELP_STRING([--with-htmlwidget[=DIR]], 
    [Build htmlwidget @<:@default=yes@:>@])], 
	[], [with_htmlwidget=$default_htmlwidget])

AC_ARG_WITH([itcl],
  [AS_HELP_STRING([--with-itcl[=DIR]], 
    [Build itcl @<:@default=yes@:>@])], 
	[], [with_itcl=$default_itcl])

AC_ARG_WITH([itk],
  [AS_HELP_STRING([--with-itk[=DIR]], 
    [Build itk @<:@default=yes@:>@])], 
	[], [with_itk=$default_itk])

AC_ARG_WITH([shape],
  [AS_HELP_STRING([--with-shape[=DIR]], 
    [Build shape @<:@default=yes@:>@])], 
	[], [with_shape=$default_shape])

#AC_ARG_WITH([sqlite],
#  [AS_HELP_STRING([--with-sqlite[=DIR]], 
#    [Build sqlite @<:@default=yes@:>@])], 
#	[], [with_sqlite=$default_sqlite])

AC_ARG_WITH([sqlitetcl],
  [AS_HELP_STRING([--with-sqlitetcl[=DIR]], 
    [Build sqlitetcl @<:@default=yes@:>@])], 
	[], [with_sqlitetcl=$default_sqlitetcl])

AC_ARG_WITH([tdom],
  [AS_HELP_STRING([--with-tdom[=DIR]], 
    [Build tDOM @<:@default=yes@:>@])], 
	[], [with_tdom=$default_tdom])

AC_ARG_WITH([tcl],
  [AS_HELP_STRING([--with-tcl[=DIR]], 
    [Build tcl @<:@default=yes@:>@])], 
	[], [with_tcl=$default_tcl])

AC_ARG_WITH([tcllib],
  [AS_HELP_STRING([--with-tcllib[=DIR]], 
    [Build tcllib @<:@default=yes@:>@])], 
	[], [with_tcllib=$default_tcllib])

AC_ARG_WITH([tk],
  [AS_HELP_STRING([--with-tk[=DIR]], 
    [Build tk @<:@default=yes@:>@])], 
	[], [with_tk=$default_tk])

AC_ARG_WITH([tkimg],
  [AS_HELP_STRING([--with-tkimg[=DIR]], 
    [Build tkimg @<:@default=yes@:>@])], 
	[], [with_tkimg=$default_tkimg])

AC_ARG_WITH([tls],
  [AS_HELP_STRING([--with-tls[=DIR]], 
    [Build tls @<:@default=yes@:>@])], 
	[], [with_tls=$default_tls])

AC_ARG_WITH([vtk],
  [AS_HELP_STRING([--with-vtk[=DIR]], 
    [Build vtk @<:@default=no@:>@])], 
	[], [with_vtk=$default_vtk])

AC_ARG_WITH([vtk-dicom],
  [AS_HELP_STRING([--with-vtk-dicom[=DIR]], 
    [Build vtk-dicom @<:@default=no@:>@])], 
	[], [with_vtk_dicom=$default_vtk_dicom])

AC_ARG_WITH([zlib],
  [AS_HELP_STRING([--with-zlib[=DIR]], 
    [Build zlib @<:@default=no@:>@])], 
	[], [with_zlib=$default_zlib])

AC_ARG_WITH([glew],
  [AS_HELP_STRING([--with-glew[=DIR]], 
    [Build glew @<:@default=no@:>@])], 
	[], [with_glew=$default_glew])

AC_ARG_WITH([voronoi],
  [AS_HELP_STRING([--with-voronoi[=DIR]], 
    [Build voronoi @<:@default=no@:>@])], 
	[], [with_voronoi=$default_voronoi])

AC_ARG_WITH([matlab],
  [AS_HELP_STRING([--with-matlab[=DIR]], 
    [Build matlab @<:@default=no@:>@])], 
	[], [with_matlab=$default_matlab])

stage1_targets="cmake expat glew tcl tk zlib"
stage2_targets="blt expect gdcm htmlwidget itcl itk shape sqlite sqlitetcl tcllib tdom tkimg tls voronoi vtk"
stage3_targets="vtk_dicom"

if test "${with_expat}" = "no" ; then
  AC_CHECK_LIB(expat, XML_ParserCreate, [with_expat="no"], 
	[with_expat="yes"])
fi
if test "${with_zlib}" = "no" ; then
  AC_CHECK_LIB(z, deflate, [with_zlib="no"], [with_zlib="yes"])
fi

stage1_dirs=""
for i in $stage1_targets ; do
  withval=with_${i}
  var=`echo ${i}_DIR | tr "a-z" "A-Z"`
  eval ${var}=""
  if test "x${!withval}" != "xno"; then
    eval ${var}=${!i}
    stage1_dirs="$stage1_dirs ${!i}"
  fi
done
stage2_dirs=""
for i in $stage2_targets ; do
  withval=with_${i}
  var=`echo ${i}_DIR | tr "a-z" "A-Z"`
  eval ${var}=""
  if test "x${!withval}" != "xno"; then
    eval ${var}=${!i}
    stage2_dirs="$stage2_dirs ${!i}"
  fi
done
stage3_dirs=""
for i in $stage3_targets ; do
  withval=with_${i}
  var=`echo ${i}_DIR | tr "a-z" "A-Z"`
  eval ${var}=""
  if test "x${!withval}" != "xno"; then
    eval ${var}=${!i}
    stage3_dirs="$stage3_dirs ${!i}"
  fi
done

AC_SUBST(X86_64)

if test "x${STAGE}" = "x"; then
   cwd=`pwd`
   STAGE=`basename $cwd`
fi

my_subdirs=""
my_makefile=""
if test "${STAGE}" = "x" ; then
  AC_ERROR([must specify build stage: use STAGE environment variable (ex. STAGE=stage1)])
fi

if test "${STAGE}" = "stage1"; then
  my_subdirs=$stage1_dirs
  my_makefile="Makefile:stages/Makefile-stage1.in"
  ac_configure_args="$ac_configure_args --enable-shared --disable-threads"
fi
if test "${STAGE}" = "stage2"; then
  my_subdirs=$stage2_dirs
  my_makefile="Makefile:stages/Makefile-stage2.in"
  ac_configure_args="$ac_configure_args --enable-shared --disable-threads --with-tclincls=$includedir --with-tkincls=$includedir --with-ssl-dir=/usr --with-tk=$libdir --with-tcl=$libdir --with-tcllibs=$libdir --with-tklibs=$libdir --with-tclconf=$libdir --with-tkconf=$libdir --with-tclinclude=$topsrcdir/$tcl/../generic --with-system-sqlite"
fi
if test "${STAGE}" = "stage3"; then
  my_subdirs=$stage3_dirs
  my_makefile="Makefile:stages/Makefile-stage3.in"
  ac_configure_args="$ac_configure_args --enable-shared --disable-threads --with-tclincls=$includedir --with-tkincls=$includedir --with-ssl-dir=/usr --with-tk=$libdir --with-tcl=$libdir --with-tcllibs=$libdir --with-tklibs=$libdir --with-tclconf=$libdir --with-tkconf=$libdir"
fi

AC_PATH_X

if test "${x_includes}" = "NONE" ; then
   AC_ERROR([can't find X11 headers, required by tk, blt, htmlwidget, shape, tkimg])
fi
if test "${x_libraries}" = "NONE" ; then
   AC_ERROR([can't find X11 libraries, required by tk, blt, htmlwidget, shape, tkimg])
fi

AC_SUBST(BLT_DIR)
AC_SUBST(CMAKE_DIR)
AC_SUBST(EXPAT_DIR)
AC_SUBST(EXPECT_DIR)
AC_SUBST(GDCM_DIR)
AC_SUBST(GLEW_DIR)
AC_SUBST(HTMLWIDGET_DIR)
AC_SUBST(ITCL_DIR)
AC_SUBST(ITK_DIR)
AC_SUBST(SHAPE_DIR)
#AC_SUBST(SQLITE_DIR)
AC_SUBST(SQLITETCL_DIR)
AC_SUBST(TCLLIB_DIR)
AC_SUBST(TCL_DIR)
AC_SUBST(TDOM_DIR)
AC_SUBST(TKIMG_DIR)
AC_SUBST(TK_DIR)
AC_SUBST(TLS_DIR)
AC_SUBST(VORONOI_DIR)
AC_SUBST(VTK_DIR)
AC_SUBST(VTK_DICOM_DIR)
AC_SUBST(ZLIB_DIR)

if test "x${my_subdirs}" != "x"; then
  AC_CONFIG_SUBDIRS([ ${my_subdirs} ])
fi
if test "x${my_makefile}" != "x"; then
  AC_OUTPUT([ ${my_makefile} ])
fi
