###########################################################################
# Makefile - build and install all packages required by Rappture runtime
# 
# To build everything, type:
# 	./configure --prefix=/apps/rappture/20060907
# 	make all
# 	
# To build individual package, tcl, for example:
# 	make tcl
#
#############################################################################
basedir=/home/gah/rappture/runtime
RP_SRC=$(basedir)/rappture

prefix			= /usr/local/rappture
exec_prefix		= /usr/local/rappture
datadir			= ${datarootdir}
datarootdir		= ${prefix}/share
bindir			= ${exec_prefix}/bin
libdir			= ${exec_prefix}/lib
includedir		= ${prefix}/include
mandir			= ${datarootdir}/man

.PHONY: tcl tk itcl tdom blt tkimg htmlwidget shape expat scew tls tcllib vtk pymol zlib libb64 voronoi

#definitions for installation on various systems

build_dir=$(basedir)/build

ifndef mydate
build_date := $(shell date +%Y%m%d)
else
build_date = $(mydate)
endif

INSTALL_DIR_WEB=www-data@developer.nanohub.org:/var/www/downloads/rappture
Tarfile_linux=rappture-linux-i686-$(build_date)
Tarfile_mac=rappture-macosx-$(build_date)

all: rappture
pkgs: tcl tk itcl tdom blt tkimg htmlwidget shape expat scew tls tcllib vtk pymol zlib libb64 voronoi

#################################################
tcl:
ifeq (yes,yes)
	@echo "BUIDING TCL8.4.11...." 
	@if test -e $(basedir)/tcl8.4.11/unix/Makefile ; then \
		make -C $(basedir)/tcl8.4.11/unix distclean; \
	fi
	cd $(basedir)/tcl8.4.11/unix && ./configure --disable-shared --disable-threads --with-readline --prefix=$(prefix)  --libdir=$(libdir)
	make -C $(basedir)/tcl8.4.11/unix
	make -C $(basedir)/tcl8.4.11/unix install
	cd $(basedir)/tcl8.4.11/unix && ./configure --enable-shared --disable-threads --with-readline --prefix=$(prefix)  --libdir=$(libdir)
	make -C $(basedir)/tcl8.4.11/unix
	make -C $(basedir)/tcl8.4.11/unix install
	cd $(bindir); rm -f tclsh; ln -s tclsh8.4 tclsh
	@if test "`uname`" == "Linux"; then \
		cd $(libdir); rm -f libtcl8.4.so.0; ln -s libtcl8.4.so libtcl8.4.so.0; \
	fi
endif

#################################################
tk:
ifeq (yes,yes)
	@echo "BUIDING Tk8.4.11...." 
	@if test -e $(basedir)/tk8.4.11/unix/Makefile ; then \
		make -C $(basedir)/tk8.4.11/unix distclean; \
	fi
	cd $(basedir)/tk8.4.11/unix && ./configure --enable-shared --disable-threads --prefix=$(prefix) --with-tcl=$(libdir)  --libdir=$(libdir)
	make -C $(basedir)/tk8.4.11/unix
	make -C $(basedir)/tk8.4.11/unix install
	cd $(bindir); rm -f wish; ln -s wish8.4 wish;
	@if test "`uname`" == "Linux"; then \
		cd $(libdir); rm -f libtk8.4.so.0; ln -s libtk8.4.so libtk8.4.so.0; \
	fi
endif

#################################################
itcl:
ifeq (yes,yes)
	@echo "BUIDING itcl3.2.1...."
	@if test -e $(basedir)/itcl3.2.1/Makefile ; then \
		make -C $(basedir)/itcl3.2.1 distclean; \
	fi
	cd $(basedir)/itcl3.2.1 && ./configure --enable-shared --disable-threads --prefix=$(prefix) --with-tcl=$(libdir) --with-tk=$(libdir) --libdir=$(libdir)
	make -C $(basedir)/itcl3.2.1 all
	make -C $(basedir)/itcl3.2.1 install
endif

#################################################
tdom:
ifeq (yes,yes)
	@echo "BUIDING tdom-0.8.0..."
	@if test -e $(basedir)/tDOM-0.8.0/Makefile ; then \
		make -C $(basedir)/tDOM-0.8.0 distclean; \
	fi
	cd $(basedir)/tDOM-0.8.0/unix && ../configure --enable-shared --disable-threads --prefix=$(prefix) --with-tcl=$(libdir) --with-tk=$(libdir)  --libdir=$(libdir)
	make -C $(basedir)/tDOM-0.8.0/unix
	make -C $(basedir)/tDOM-0.8.0/unix install
endif

#################################################
blt:
ifeq (yes,yes)
	@echo "BUIDING blt2.4z..."
	@if test -e $(basedir)/blt2.4z/Makefile ; then \
		make -C $(basedir)/blt2.4z distclean; \
	fi
	cd $(basedir)/blt2.4z && ./configure --enable-shared --prefix=$(prefix) --with-tcl=$(libdir) --with-tcllibs=$(libdir) --with-tclincls=$(includedir) --with-tk=$(libdir) --with-tklibs=$(libdir) --with-tkincls=$(includedir) --x-includes=/usr/X11R6/include/X11 --libdir=$(libdir)
	@if test "x" != "x"; then \
		if ! test -e $(basedir)/blt2.4z/src/bltTree.c.orig; then \
			patch -b -p0 < other/blt2.4z-patch-64; \
		fi \
	fi
	make -C $(basedir)/blt2.4z
	make -C $(basedir)/blt2.4z install
endif

#################################################
tkimg:
ifeq (yes,yes)
	@echo "BUIDING tkimg1.3 ...."
	@if test -e $(basedir)/tkimg1.3/Makefile ; then \
		make -C $(basedir)/tkimg1.3 distclean; \
	fi
	# we do not use libdir here, because it messes up 64-bit builds for some reason
	cd $(basedir)/tkimg1.3 && ./configure --prefix=$(prefix) --with-tclconf=$(libdir) --with-tkconf=$(libdir)
	make -C $(basedir)/tkimg1.3
	make -C $(basedir)/tkimg1.3 install
endif

#################################################
htmlwidget:
ifeq (yes,yes)
	@echo "BUIDING htmlwidget..."
	@if test -e $(basedir)/htmlwidget-3a14/Makefile ; then \
		make -C $(basedir)/htmlwidget-3a14 distclean; \
	fi
	cd $(basedir)/htmlwidget-3a14 && ./configure --enable-shared --disable-threads --prefix=$(prefix) --with-tcl=$(libdir) --with-tk=$(libdir)  --libdir=$(libdir)
	make -C $(basedir)/htmlwidget-3a14
	make -C $(basedir)/htmlwidget-3a14 install
endif

#################################################
shape:
ifeq (yes,yes)
	@echo "BUIDING Shape0.4 ......"
	@if test -e $(basedir)/shape0.4/unix/Makefile ; then \
		make -C $(basedir)/shape0.4/unix distclean; \
	fi
	cd $(basedir)/shape0.4/unix && ./configure --disable-threads --prefix=$(prefix) --with-tclconf=$(libdir) --with-tkconf=$(libdir) --libdir=$(libdir)
	make -C $(basedir)/shape0.4/unix
	make -C $(basedir)/shape0.4/unix install
endif

#################################################
expat_version=1.95.8
expat_version=2.0.1

expat:
ifeq (yes,yes)
	@echo "BUIDING expat-$(expat_version) ......."
	@if test -e $(basedir)/expat-$(expat_version)/Makefile ; then \
		make -C $(basedir)/expat-$(expat_version) distclean; \
	fi
	cd $(basedir)/expat-$(expat_version) && ./configure --prefix=$(prefix) --libdir=$(libdir)
	make -C $(basedir)/expat-$(expat_version)
	make -C $(basedir)/expat-$(expat_version) install
endif

#################################################
scew:
ifeq (yes,yes)
	@echo "BUIDING scew-0.4.0 ......."
	@if test -e $(basedir)/scew-0.4.0/Makefile ; then \
		make -C $(basedir)/scew-0.4.0 distclean; \
	fi
	#@if test "x" != "x"; then \
	#	if ! test -e $(basedir)/scew-0.4.0/configure.in.orig; then \
	#		patch -b -p0 < other/scew-0.4.0-patch-64; \
	#		cd $(basedir)/scew-0.4.0 && autoconf -f; \
	#	fi \
	#fi
	cd $(basedir)/scew-0.4.0 && CFLAGS="-I$(prefix)/include -Wall -pipe -O2 -fPIC" CPPFLAGS="-I$(prefix)/include -fPIC" ./configure --prefix=$(prefix) --libdir=$(libdir)
	make -C $(basedir)/scew-0.4.0
	make -C $(basedir)/scew-0.4.0 install
	cp $(basedir)/scew-0.4.0/scew/x*.h $(includedir)/scew/.
endif

#################################################
tls:
ifeq (yes,yes)
	@echo "BUIDING tls1.5..."
	@if test -e $(basedir)/tls1.5/Makefile ; then \
		make -C $(basedir)/tls1.5 distclean; \
	fi
	cd $(basedir)/tls1.5 && ./configure --enable-shared --prefix=$(prefix) --with-tcl=$(libdir) --with-ssl-dir=/usr --libdir=$(libdir)
	make -C $(basedir)/tls1.5
	make -C $(basedir)/tls1.5 install
endif

#################################################
tcllib:
ifeq (yes,yes)
	@echo "BUIDING tcllib-1.9..."
	@if test -e $(basedir)/tcllib-1.9/Makefile ; then \
		make -C $(basedir)/tcllib-1.9 distclean; \
	fi
	cd $(basedir)/tcllib-1.9 && ./configure --enable-shared --prefix=$(prefix) --with-tcl=$(libdir) --with-tcllibs=$(libdir) --with-tclincls=$(includedir) --libdir=$(libdir)
	make -C $(basedir)/tcllib-1.9
	make -C $(basedir)/tcllib-1.9 install
endif

#############################################################################
# Install vtk 4.4 from binary
# cd $(basedir)/vtk.bin; make RAPPTURE=$(prefix)
#		make -C $(basedir)/VTK4.4 clean; \
#############################################################################
vtk:
ifeq (no,yes)
	@echo "BUIDING VTK4.4..."
	@if test -e $(basedir)/VTK4.4/Makefile ; then \
		cd $(basedir)/VTK4.4 && make clean;\
	fi
	@if test -e $(basedir)/VTK4.4/CMakeCache.txt ; then \
		rm $(basedir)/VTK4.4/CMakeCache.txt;\
	fi
	cd $(basedir)/VTK4.4 && cmake ../VTK4.4 -DCMAKE_INSTALL_PREFIX:PATH=$(prefix) -DBUILD_SHARED_LIBS:BOOL=ON -DTCL_TCLSH:FILEPATH=$(prefix)/bin/tclsh -DVTK_WRAP_TCL:BOOL=ON -DCMAKE_BACKWARDS_COMPATIBILITY=2.2 -DTCL_INCLUDE_PATH:PATH=$(includedir) -DTCL_LIBRARY:FILEPATH=$(libdir)/libtcl8.4.so -DTK_INCLUDE_PATH:PATH=$(includedir) -DTK_LIBRARY:FILEPATH=$(libdir)/libtk8.4.so -DVTK_USE_HYBRID:BOOL=ON;
	make -C $(basedir)/VTK4.4
	make -C $(basedir)/VTK4.4 install
endif

#################################################
pymol:
ifeq (no,yes)
	@echo "BUIDING pymol-1.00b19..."
	@if test -e $(basedir)/pymol-1.00b19/Makefile ; then \
		make -C $(basedir)/pymol-1.00b19 distclean; \
	fi
	cd $(basedir)/pymol-1.00b19 && ./configure --prefix=$(prefix) --libdir=$(libdir)
	make -C $(basedir)/pymol-1.00b19
	make -C $(basedir)/pymol-1.00b19 install
	@if ! test -d $(libdir)/pymol/modules ; then \
		mkdir -p $(libdir)/pymol; \
	fi
	cp -rL $(basedir)/pymol-1.00b19/modules $(libdir)/pymol
endif

#################################################
zlib:
ifeq (yes,yes)
	@echo "BUIDING zlib-1.2.3 ......."
	@if test -e $(basedir)/zlib-1.2.3/Makefile ; then \
		make -C $(basedir)/zlib-1.2.3 distclean; \
	fi
	cd $(basedir)/zlib-1.2.3 && CFLAGS="-fPIC" ./configure --shared --prefix=$(prefix) --libdir=$(libdir)
	make -C $(basedir)/zlib-1.2.3
	make -C $(basedir)/zlib-1.2.3 install
	cd $(basedir)/zlib-1.2.3 && CFLAGS="-fPIC" ./configure --prefix=$(prefix) --libdir=$(libdir)
	make -C $(basedir)/zlib-1.2.3
	make -C $(basedir)/zlib-1.2.3 install
endif

#################################################
libb64:
ifeq (yes,yes)
	@echo "BUIDING libb64 ......."
	make -C $(basedir)/libb64-1.1/src distclean;
	make -C $(basedir)/libb64-1.1/src libb64;
	if test ! -d $(includedir)/b64; then \
		mkdir -p $(includedir)/b64; \
	fi; \
	if test ! -d $(libdir); then \
		mkdir -p $(libdir); \
	fi; \
	cp $(basedir)/libb64-1.1/src/libb64.a $(libdir)/.;
	cp $(basedir)/libb64-1.1/include/b64/*.h $(includedir)/b64/.;
	if test -f "$(basedir)/libb64-1.1/src/libb64.so.0.0"; then \
	  cp $(basedir)/libb64-1.1/src/libb64.so.0.0 $(libdir)/.; \
	  cd $(libdir); rm -f libb64.so; ln -s libb64.so.0.0 libb64.so; \
	fi
endif

#################################################
voronoi:
ifeq (yes,yes)
	@echo "BUIDING voronoi ......."
	make -C $(basedir)/voronoi clean;
	make -C $(basedir)/voronoi;
	cp $(basedir)/voronoi/voronoi $(bindir)/.;
endif

#############################################################################
# install-rp:
# 	- check out rappture from repository if not already in $(basedir)
# 	- clean up old compiled libraries
# 	- compile new core and bindings libraries
# 	- install rappture for TCL
# 	- install rappture for Python
# 	- install rappture for Perl
# 	- install rappture for Matlab
# 	- install rappture for Octave
# 	- install rappture apps (driver, rappture, rerun) in $(prefix) dir
#############################################################################

rp_update:
	@if test -d $(RP_SRC); then \
		cd $(RP_SRC); svn update ;\
	else \
		cd $(basedir); \
		svn checkout https://repo.nanohub.org/svn/rappture/trunk rappture; \
	fi

rappture: create_install_dir pkgs rp_update
	@if test -e $(RP_SRC)/Makefile ; then \
		make -C $(RP_SRC) distclean; \
	fi
	cd $(RP_SRC) && ./configure --prefix=$(prefix) --without-matlab  --libdir=$(libdir);
	make -C $(RP_SRC) install build_pkgs;

create_install_dir:
	@if test ! -d $(prefix); then \
		mkdir -p $(prefix); \
	fi;

#############################################################################
clean:
	find $(prefix) -name .svn | xargs rm -rf

cleanall:
#	rm -rf $(prefix)/*
	rm -f output.*

cleanbuild:
	rm -rf $(build_dir)/*

distclean: cleanall cleanbuild
	rm -rf config.status config.log Makefile rappture
