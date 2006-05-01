###########################################################################
# Makefile - build and install all packages required by Rappture runtime
# 
# To build everything, type:
# 	make all
# 	
# To build individual package, tcl, for example:
# 	make tcl
#
# Modify the first two lines below this block of comments.
#
# - change $basedir to point to your directory that contains this Makefile.
#   	The default is /opt/rappture-runtime.
#
# To install rappture runtime on all systems:
# 	make mydate=20060111 install-all
#
# To install on nanohub:
# 	make mydate=20060111 install-nanohub
#
#############################################################################
basedir=/home/cxsong/rappture-runtime
Rappture=$(basedir)/tmp
RP_SRC=$(basedir)/rappture
#CPP=/usr/bin/cpp
#
#definitions for installation on various systems
#
build_dir=$(basedir)/build

ifndef mydate
build_date := $(shell date +%Y%m%d)
else
build_date = $(mydate)
endif

PYTHON = $(Rappture)/bin/python

HAMLET=cxsong@radon.rcac.purdue.edu
NANOHUB=rappture@login.nanohub.org
HAMLET_DIR=/apps/01/rappture
NANOHUB_DIR=/apps/rappture
INSTALL_DIR_HAMLET=$(HAMLET):$(HAMLET_DIR)
INSTALL_DIR_NANOHUB=$(NANOHUB):$(NANOHUB_DIR)
INSTALL_DIR_WEB=www-data@developer.nanohub.org:/var/www/downloads/rappture
Tarfile_linux=rappture-linux-i686-$(build_date)
Tarfile_mac=rappture-macosx-$(build_date)

all: pkgs ws rappture

pkgs: tcl tk itcl tdom blt tkimg shape python pyimg pynum expat scew vtk

ws: pyxml fpconst pysoap clientcookie

rappture: install-rp rplib examples clean build_files pkg_nanohub pkg_hamlet

install-all: install-hamlet  install-nanohub install-web

#################################################
tcl:
	echo "BUIDING TCL8.4.11...." 
	cd $(basedir)/tcl8.4.11/unix; make clean; make distclean; \
	./configure --enable-shared --disable-threads --prefix=$(Rappture) >& $(basedir)/output.tcl; \
	make >> $(basedir)/output.tcl 2>&1; \
	make install >> $(basedir)/output.tcl 2>&1;
	cd $(Rappture)/bin; rm -f tclsh; ln -s tclsh8.4 tclsh;
	if test "`uname`" == "Linux"; then \
		cd $(Rappture)/lib; rm -f libtcl8.4.so.0; ln -s libtcl8.4.so libtcl8.4.so.0; \
	fi

#################################################
tk:
	echo "BUIDING Tk8.4.11...." 
	cd $(basedir)/tk8.4.11/unix; make clean; make distclean; \
	./configure --enable-shared --disable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib >& $(basedir)/output.tk 2>&1; \
	make >> $(basedir)/output.tk 2>& 1; \
	make install >> $(basedir)/output.tk 2>& 1; 
	cd $(Rappture)/bin; rm -f wish; ln -s wish8.4 wish;
	if test "`uname`" == "Linux"; then \
		cd $(Rappture)/lib; rm -f libtk8.4.so.0; ln -s libtk8.4.so libtk8.4.so.0; \
	fi

#################################################
itcl:
	echo "BUIDING itcl3.2.1...." 
	cd $(basedir)/itcl3.2.1; make clean; make distclean; \
	./configure --enable-shared --disable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tk=$(Rappture)/lib >& $(basedir)/output.itk 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.itcl.mac itcl/Makefile; \
		cp $(basedir)/Mac/Makefile.itk.mac itk/Makefile; \
		cp $(basedir)/Mac/pkgIndex.tcl.itcl.itk itk/pkgIndex.tcl; \
		cp $(basedir)/Mac/pkgIndex.tcl.itcl.itcl itcl/pkgIndex.tcl; \
	fi; \
	make all  >> $(basedir)/output.itk 2>& 1; \
	make install >> $(basedir)/output.itk 2>& 1

#################################################
tdom:
	echo "BUIDING tdom-0.8.0..."
	cd $(basedir)/tDOM-0.8.0/unix; make clean; make distclean; \
	../configure --enable-shared --disable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tk=$(Rappture)/lib >& $(basedir)/output.tdom 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.tdom.mac Makefile; \
	fi; \
	make >> $(basedir)/output.tdom 2>&1; \
	make install >> $(basedir)/output.tdom 2>&1

#################################################
blt:
	echo "BUIDING blt2.4z..."
	cd $(basedir)/blt2.4z; make clean; make distclean; \
	./configure --enable-shared --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tcllibs=$(Rappture)/lib --with-tclincls=$(Rappture)/include --with-tk=$(Rappture)/lib --with-tklibs=$(Rappture)/lib --with-tkincls=$(Rappture)/include --x-includes=/usr/X11R6/include/X11 >& $(basedir)/output.blt 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.blt.mac Makefile; \
		cp $(basedir)/Mac/Makefile.blt.src.mac src/Makefile; \
		cp $(basedir)/Mac/Makefile.blt.src.shared.mac src/shared/Makefile;\
	fi; \
	make >> $(basedir)/output.blt 2>&1; \
	make install >> $(basedir)/output.blt 2>&1

#################################################
tkimg:
	echo "BUIDING tkimg1.3 ... ..."
	cd $(basedir)/tkimg1.3; make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.tkimg 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.tkimg.libz.tcl.mac libz/tcl/Makefile ; \
		cp $(basedir)/Mac/Makefile.tkimg.libpng.tcl.mac libpng/tcl/Makefile; \
		cp $(basedir)/Mac/Makefile.tkimg.libjpeg.tcl.mac libjpeg/tcl/Makefile; \
		cp $(basedir)/Mac/Makefile.tkimg.libtiff.tcl.mac libtiff/tcl/Makefile; \
		cp $(basedir)/Mac/Makefile.tkimg.jpeg.mac jpeg/Makefile; \
		cp $(basedir)/Mac/Makefile.tkimg.tiff.mac tiff/Makefile; \
		cp $(basedir)/Mac/Makefile.tkimg.base.mac base/Makefile; \
	fi;\
	make >> $(basedir)/output.tkimg 2>&1; \
	make install >> $(basedir)/output.tkimg 2>&1

#################################################
shape:
	echo "BUIDING Shape0.4 ... ..."
	cd $(basedir)/shape0.4/unix; make clean; make distclean; \
	./configure --disable-threads --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.shape 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.shape04.mac Makefile; \
	fi; \
	make >> $(basedir)/output.shape 2>&1; \
	make install >> $(basedir)/output.shape 2>&1

shape-old:
	echo "BUIDING Shape0.4 ... ..."
	cd $(basedir)/shape0.4/unix; make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.shape 2>&1; \
	if test "`uname`" == "Darwin"; then \
		cp $(basedir)/Mac/Makefile.shape04.mac Makefile; \
	else \
		cp $(basedir)/other/Makefile.shape04 Makefile; \
	fi; \
	make >> $(basedir)/output.shape 2>&1; \
	make install >> $(basedir)/output.shape 2>&1

#################################################
python:
	echo "BUIDING python2.4.1..."
	cd $(basedir)/Python-2.4.1; make clean; make distclean; \
	if test "`uname`" == "Linux"; then \
		export LDFLAGS="-Wl,-rpath $(Rappture)/lib"; \
		./configure --enable-shared --prefix=$(Rappture) >& $(basedir)/output.py 2>&1; \
	else \
		./configure --enable-shared --disable-threads --prefix=$(Rappture) >& $(basedir)/output.py 2>&1 ; \
		cp $(basedir)/Mac/Makefile.py.mac Makefile ; \
	fi; \
	make >> $(basedir)/output.py 2>&1; \
	make install >> $(basedir)/output.py 2>&1; 
#	if test "`uname`" == "Darwin"; then \
#	cp libpython2.4.a $(Rappture)/lib; \
#	cp $(basedir)/Mac/libpython2.4.dylib $(Rappture)/lib; \
#	fi

#################################################
pyimg:
	echo "BUIDING python Imaging"
	cd $(basedir)/Imaging-1.1.5; \
	rm -rf build; \
	$(PYTHON) setup.py install --prefix=$(Rappture) >& $(basedir)/output.pyimg 2>&1

#################################################
pynum:
	echo "BUIDING python Numeric 24.2"
	cd $(basedir)/Numeric-24.2; \
	/bin/sh makeclean.sh; \
	$(PYTHON) setup.py build >& $(basedir)/output.num 2>&1; \
	$(PYTHON) setup.py install --prefix=$(Rappture) >> $(basedir)/output.num 2>&1

#################################################
# TODO
scipy:
	echo "BUIDING SciPy 0.3.2"
	cd $(basedir)/SciPy_complete-0.3.2; \
	$(PYTHON) setup.py build >& $(basedir)/output.sci 2>&1

#################################################
expat:
	echo "BUIDING expat-1.95.8 ......."
	cd $(basedir)/expat-1.95.8; make clean; make distclean; \
	./configure --prefix=$(Rappture) >& $(basedir)/output.ex 2>&1 ; \
	make >> $(basedir)/output.ex 2>&1; \
	make install >> $(basedir)/output.ex 2>&1

#################################################
scew:
	echo "BUIDING scew-0.4.0 ......."
	cd $(basedir)/scew-0.4.0/scew; \
	cp $(basedir)/other/Makefile.scew Makefile; \
	make clean; \
	make LIB_HOME=$(Rappture)/lib INCL_HOME=$(Rappture)/include >& $(basedir)/output.scew 2>&1; \
	make LIB_HOME=$(Rappture)/lib INCL_HOME=$(Rappture)/include install >> $(basedir)/output.scew 2>&1

#############################################################################
# Install vtk 4.4 from binary
#############################################################################
vtk:
	cd $(basedir)/vtk.bin; make RAPPTURE=$(Rappture) >& $(basedir)/output.vtk 2>&1

#############################################################################
# web service related packages
#
pyxml:
	cd $(basedir)/PyXML-0.8.4; \
	$(PYTHON) setup.py build; \
	$(PYTHON) setup.py install

fpconst:
	cd $(basedir)/fpconst-0.7.2; \
	$(PYTHON) setup.py install

pysoap:
	cd $(basedir)/SOAPpy-0.12.0; \
	$(PYTHON) setup.py install

clientcookie:
	cd $(basedir)/ClientCookie-1.3.0; \
	$(PYTHON) setup.py build; \
	$(PYTHON) setup.py install

#############################################################################
# install-rp:
# 	- check out rappture from repository if not already in $(basedir)
# 	- install rappture for TCL
# 	- install rappture for Python
# 	- install rappture apps (driver, rappture, rerun) in $(Rappture) dir
#############################################################################

rp_update:	
	set -x; \
	if test -d $(RP_SRC); then \
		cd $(RP_SRC); svn update ;\
	else \
		cd $(basedir); \
		svn checkout https://repo.nanohub.org/svn/rappture/trunk rappture; \
	fi

rp_gui: rp_update
	set -x; \
	echo "path is $(PATH)"; \
	cd $(RP_SRC)/gui; \
	make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-blt=$(basedir)/blt2.4z/src; \
	make all >& $(basedir)/output.gui 2>&1; \
	make install >> $(basedir)/output.gui 2>&1

install-rp: rp_gui
	set -x
	cd $(RP_SRC)/tcl; $(Rappture)/bin/tclsh install.tcl
	cd $(RP_SRC)/python; $(Rappture)/bin/python setup.py install
	cp $(RP_SRC)/gui/apps/* $(Rappture)/bin 
	rm -rf $(Rappture)/include/cee $(Rappture)/include/core $(Rappture)/include/fortran
	cp -r $(RP_SRC)/include/cee $(Rappture)/include
	cp -r $(RP_SRC)/include/core $(Rappture)/include
	cp -r $(RP_SRC)/include/fortran $(Rappture)/include

#############################################################################
# build rappture libs - assuming "rappture" dir was checked out from 
# 			https://repo.nanohub.org/svn/rappture/trunk rappture
# install-rp:
# 	- build rappture libs in rappture/src dir
# 	- install rappture libs in $(Rappture) dir 
#############################################################################
rplib:
	set -x; \
	cd $(RP_SRC)/src; \
	make clean >& $(basedir)/output.rp 2>&1; \
	make RP_INSTALL_BASE=$(Rappture) all >> $(basedir)/output.rp 2>&1; \
	make RP_INSTALL_BASE=$(Rappture) install >> $(basedir)/output.rp 2>&1

#############################################################################
# build rappture examples
# examples:
# 	- compile rappture examples in rappture/examples
# 	- install rappture examples in $(Rappture)/examples
#############################################################################
examples:
	set -x;
	cd $(RP_SRC)/examples/app-fermi/fortran; make clean; make RAPPTURE_DIR=$(Rappture) >> $(basedir)/output.rp 2>& 1
	cd $(RP_SRC)/examples/app-fermi/cee; make clean; make RP_BASE=$(Rappture) >> $(basedir)/output.rp 2>& 1
	cd $(RP_SRC)/examples/c-example; make clean; make RP_BASE=$(Rappture) >> $(basedir)/output.rp 2>& 1
	rm -rf $(Rappture)/examples
	cp -r $(RP_SRC)/examples $(Rappture)

#############################################################################
# additional libs, files:
# #
addons:
	if test "`uname`" == "Linux"; then \
		cp -d /usr/lib/libstdc++.so.5* $(Rappture)/lib; \
		cp -d /usr/lib/libtiff.so.4* $(Rappture)/lib; \
		cp -d /usr/lib/gcc-lib/i486-linux/3.3.5/libstdc++.a $(Rappture)/lib; \
		cp -d /usr/lib/gcc-lib/i486-linux/3.3.5/libsupc++.a $(Rappture)/lib; \
		cp -d /usr/lib/gcc-lib/i486-linux/3.3.5/libgcc_eh.a $(Rappture)/lib; \
	fi

#############################################################################
# installation scripts
# Temporary: copy matlab binary from hamlet build (due to inconsistency of 
# c compilers between what's used by matlab and what's installed on lepus.
# Should be fixed eventually.
#############################################################################
#
# copy binaries to build dir and prepare files for various distributions
#
build_files:
	set -x;
	if test ! -d $(build_dir); then \
		mkdir $(build_dir); \
	fi; \
	echo "removing existing directory: build_dir/rappture"; \
	if test -d $(build_dir)/rappture; then \
		rm -rf $(build_dir)/rappture; \
	fi; \
	mkdir $(build_dir)/rappture; \
	if test -d $(build_dir)/$(build_date); then \
		rm -rf $(build_dir)/$(build_date); \
	fi; \
	echo "copying $(Rappture) to $(build_dir) ..."; \
	cd $(Rappture); \
	cp -rp bin include lib man examples $(build_dir)/rappture; \
	cd $(build_dir); \
	cp -rp rappture $(build_date); \
	if test "`uname`" == "Linux"; then \
		cp -p rappture/bin/rappture rappture.orig; \
		cp -p rappture/examples/demo.bash demo.bash.orig; \
		sed 's/opt\/rappture/apps\/rappture\/$(build_date)/' < ./rappture.orig > rappture.nanohub; \
		sed 's/opt\/rappture/apps\/rappture\/$(build_date)/' < ./demo.bash.orig > demo.bash.nanohub; \
		sed 's/opt\/rappture/apps\/01\/rappture\/$(build_date)/' < ./rappture.orig > rappture.hamlet; \
		sed 's/opt\/rappture/apps\/01\/rappture\/$(build_date)/' < ./demo.bash.orig > demo.bash.hamlet; \
		tar czf $(Tarfile_linux).tar.gz ./rappture; \
	else \
		tar czf $(Tarfile_mac).tar.gz ./rappture; \
	fi; \
	echo done

#
# Make a tarball for hamlet and push it out to hamlet (via radon)
#
pkg_hamlet:
	set -x;
	cd $(build_dir); \
	if ! test -d $(build_date); then exit; fi; \
	cp rappture.hamlet $(build_date)/bin/rappture; \
	cp demo.bash.hamlet $(build_date)/examples/demo.bash; \
	echo -n "creating tarball for hamlet ...."; \
	tar czf $(Tarfile_linux).ham.tar.gz $(build_date); \
	echo done

install-hamlet:
	set -x; 
	if ! test -f $(build_dir)/$(Tarfile_linux).hamlet.tar.gz; then \
		$(MAKE) pkg_hamlet; \
	fi; \
	cd $(build_dir); \
	scp $(Tarfile_linux).ham.tar.gz $(INSTALL_DIR_HAMLET)/tars; \
	ssh $(HAMLET) 'cd $(HAMLET_DIR); tar xzf tars/$(Tarfile_linux).ham.tar.gz'; \
	ssh $(HAMLET) rm $(HAMLET_DIR)/dev; \
	ssh $(HAMLET) ln -s $(HAMLET_DIR)/$(build_date) $(HAMLET_DIR)/dev; \
	ssh $(HAMLET) ls -l $(HAMLET_DIR); \
	echo done

pkg_nanohub:
	set -x; \
	cd $(build_dir); \
	if ! test -d $(build_date); then exit; fi; \
	cp rappture.nanohub $(build_date)/bin/rappture; \
	cp demo.bash.nanohub $(build_date)/examples/demo.bash; \
	tar czf $(Tarfile_linux).nanohub.tar.gz $(build_date); \

install-nanohub: 
	set -x;
	if test ! -f $(build_dir)/$(Tarfile_linux).nanohub.tar.gz; then \
		$(MAKE) pkg_nanohub; \
	fi; \
	cd $(build_dir); \
	scp $(Tarfile_linux).nanohub.tar.gz $(INSTALL_DIR_NANOHUB)/tars; \
	ssh $(NANOHUB) 'cd $(NANOHUB_DIR); tar xzf tars/$(Tarfile_linux).nanohub.tar.gz'; \
	ssh $(NANOHUB) rm $(NANOHUB_DIR)/dev; \
	ssh $(NANOHUB) ln -s $(NANOHUB_DIR)/$(build_date) $(NANOHUB_DIR)/dev; \
	ssh $(NANOHUB) ls -l $(NANOHUB_DIR); \

#
# Make a tarball and push to web server
#
install-web: get-mac-build
	set -x; \
	cd $(build_dir); \
	if test -f $(Tarfile_linux).tar.gz; then \
		scp $(Tarfile_linux).tar.gz $(INSTALL_DIR_WEB); \
	fi; \
	if test -f $(Tarfile_mac).tar.gz; then \
		scp $(Tarfile_mac).tar.gz $(INSTALL_DIR_WEB); \
	fi; \
	echo done

get-mac-build:
	set -x; \
	cd $(build_dir); \
	scp cxsong@mmc.rcac.purdue.edu:/opt/rappture-runtime/build/$(Tarfile_mac).tar.gz .

#
# cron job to run daily
#
cronjob:
	cd $(basedir); \
	$(MAKE) cleanall; \
	svn update .; \
	$(MAKE) all
#############################################################################
clean:
	find $(Rappture) -name .svn | xargs rm -rf

cleanall:
	rm -rf $(Rappture)/*
	rm -f output.*

cleanbuild:
	rm -rf $(build_dir)/*
