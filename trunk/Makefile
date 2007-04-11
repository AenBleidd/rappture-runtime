###########################################################################
# Makefile - build and install all packages required by Rappture runtime
# 
# To build everything, type:
# 	./configure --prefix=/apps/rappture/20060907
# 	make rappture-basic
# 	
# To build individual package, tcl, for example:
# 	make tcl
#
# To install rappture runtime on all systems:
# 	make mydate=20060111 install-all
#
# To install on nanohub:
# 	make mydate=20060111 install-nanohub
#
#############################################################################
basedir=/home/mmc/nanohub/rappture-runtime
Rappture=/apps/rappture/20070410
RP_SRC=$(basedir)/rappture
SHELL=/bin/bash


#definitions for installation on various systems

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

pkgs: tcl tk itcl tdom blt tkimg htmlwidget shape expat scew tls tcllib vtk

rappture: install-rp rplib examples clean build_files pkg_nanohub pkg_hamlet

rappture-basic: create_install_dir pkgs-simple rappture-simple
pkgs-simple: tcl tk itcl tdom blt tkimg htmlwidget shape expat scew tls tcllib vtk zlib libb64

install-all: install-hamlet install-nanohub install-web

#################################################
tcl:
	echo "BUIDING TCL8.4.11...." 
	cd $(basedir)/tcl8.4.11/unix; make clean; make distclean; \
	./configure --enable-shared --disable-threads --with-readline --prefix=$(Rappture) >& $(basedir)/output.tcl; \
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
	make all  >> $(basedir)/output.itk 2>& 1; \
	make install >> $(basedir)/output.itk 2>& 1

#################################################
tdom:
	echo "BUIDING tdom-0.8.0..."
	cd $(basedir)/tDOM-0.8.0/unix; make clean; make distclean; \
	../configure --enable-shared --disable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tk=$(Rappture)/lib >& $(basedir)/output.tdom 2>&1; \
	make >> $(basedir)/output.tdom 2>&1; \
	make install >> $(basedir)/output.tdom 2>&1

#################################################
blt:
	echo "BUIDING blt2.4z..."
	cd $(basedir)/blt2.4z; make clean; make distclean; \
	./configure --enable-shared --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tcllibs=$(Rappture)/lib --with-tclincls=$(Rappture)/include --with-tk=$(Rappture)/lib --with-tklibs=$(Rappture)/lib --with-tkincls=$(Rappture)/include --x-includes=/usr/X11R6/include/X11 >& $(basedir)/output.blt 2>&1; \
	make >> $(basedir)/output.blt 2>&1; \
	make install >> $(basedir)/output.blt 2>&1

#################################################
tkimg:
	echo "BUIDING tkimg1.3 ... ..."
	cd $(basedir)/tkimg1.3; make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.tkimg 2>&1; \
	make >> $(basedir)/output.tkimg 2>&1; \
	make install >> $(basedir)/output.tkimg 2>&1

#################################################
htmlwidget:
	echo "BUIDING htmlwidget..."
	cd $(basedir)/htmlwidget; make clean; make distclean; \
	./configure --enable-shared --disable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tk=$(Rappture)/lib >& $(basedir)/output.htmlwidget 2>&1; \
	make >> $(basedir)/output.htmlwidget 2>&1; \
	make install >> $(basedir)/output.htmlwidget 2>&1

#################################################
shape:
	echo "BUIDING Shape0.4 ......"
	cd $(basedir)/shape0.4/unix; make clean; make distclean; \
	./configure --disable-threads --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.shape 2>&1; \
	make >> $(basedir)/output.shape 2>&1; \
	make install >> $(basedir)/output.shape 2>&1

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

#################################################
tls:
	echo "BUIDING tls1.5..."
	cd $(basedir)/tls1.5; make clean; make distclean; \
	./configure --enable-shared --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-ssl-dir=/usr >& $(basedir)/output.tls 2>&1; \
	make >> $(basedir)/output.tls 2>&1; \
	make install >> $(basedir)/output.tls 2>&1

#################################################
tcllib:
	echo "BUIDING tcllib-1.6.1..."
	cd $(basedir)/tcllib-1.6.1; make clean; make distclean; \
	./configure --enable-shared --prefix=$(Rappture) --with-tcl=$(Rappture)/lib --with-tcllibs=$(Rappture)/lib --with-tclincls=$(Rappture)/include >& $(basedir)/output.tcllib 2>&1; \
	make >> $(basedir)/output.tcllib 2>&1; \
	make install >> $(basedir)/output.tcllib 2>&1

#############################################################################
# Install vtk 4.4 from binary
#############################################################################
vtk:
	cd $(basedir)/vtk.bin; make RAPPTURE=$(Rappture) >& $(basedir)/output.vtk 2>&1

#################################################
zlib:
	echo "BUIDING zlib-1.2.3 ......."
	cd $(basedir)/zlib-1.2.3; make clean; make distclean; \
	./configure --shared --prefix=$(Rappture) >& $(basedir)/output.zlib 2>&1 ; \
	make >> $(basedir)/output.zlib 2>&1; \
	make install >> $(basedir)/output.zlib 2>&1;\
	./configure --prefix=$(Rappture) >& $(basedir)/output.zlib 2>&1 ; \
	make >> $(basedir)/output.zlib 2>&1; \
	make install >> $(basedir)/output.zlib 2>&1

#################################################
libb64:
	echo "BUIDING libb64 ......."
	cd $(basedir)/libb64-1.1; make distclean; \
	make libb64 >> $(basedir)/output.libb64 2>&1; \
	cp src/libb64.a $(Rappture)/lib/.; \
	cp src/libb64.so.0.0 $(Rappture)/lib/.; \
	cp -r include/b64 $(Rappture)/include/.; \
	cd $(Rappture)/lib; ln -s libb64.so.0.0 libb64.so;

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

rappture-simple: rp_update
	set -x; \
	cd $(RP_SRC); \
	make clean; \
	./configure --prefix=$(Rappture) --with-matlab= ; \
	make install build_pkgs;

create_install_dir:
	if test ! -d $(Rappture); then \
		mkdir -p $(Rappture); \
	fi; \

#############################################################################
# build rappture libs - assuming "rappture" dir was checked out from 
# 			https://repo.nanohub.org/svn/rappture/trunk rappture
# install-rp:
# 	- build rappture libs in rappture/src dir
# 	- install rappture libs in $(Rappture) dir 
#############################################################################
rplib:
	set -x;
	make clean;
	cd $(RP_SRC); ./configure --prefix=$(Rappture) --with-matlab=/apps/matlab;
	cd $(RP_SRC); make clean; make install >> $(basedir)/output.rp 2>&1;
	cd -;

#############################################################################
# build rappture examples
# examples:
# 	- compile rappture examples in rappture/examples
# 	- install rappture examples in $(Rappture)/examples
#############################################################################
examples:
	set -x;
	cd $(RP_SRC); make examples; cd -;
	rm -rf $(Rappture)/examples;
	cp -r $(RP_SRC)/examples $(Rappture)

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
	if test ! -d $(build_date); then exit; fi; \
	cp rappture.hamlet $(build_date)/bin/rappture; \
	cp demo.bash.hamlet $(build_date)/examples/demo.bash; \
	echo -n "creating tarball for hamlet ...."; \
	tar czf $(Tarfile_linux).ham.tar.gz $(build_date); \
	echo done

install-hamlet:
	set -x; 
	if test ! -f $(build_dir)/$(Tarfile_linux).ham.tar.gz; then \
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
	if test ! -d $(build_date); then exit; fi; \
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
#	rm -rf $(Rappture)/*
	rm -f output.*

cleanbuild:
	rm -rf $(build_dir)/*

distclean: cleanall cleanbuild
	rm -rf config.status config.log Makefile rappture
