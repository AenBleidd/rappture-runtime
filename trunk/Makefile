############################################################################
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
# To install on all systems:
# 	make mydate=20060111 installall
#############################################################################
basedir=/opt/rappture-runtime
Rappture=/opt/rappture
RP_SRC=$(basedir)/rappture
#CPP=/usr/bin/cpp
#
#definitions for installation on various systems
#
build_dir=$(basedir)/build
build_date=$(mydate)
INSTALL_DIR_NANOHUB=rappture@login.nanohub.org:/apps/rappture
INSTALL_DIR_HAMLET=cxsong@radon.rcac.purdue.edu:/apps/01/rappture
INSTALL_DIR_LEPUS=/opt/rappture
Tarfile_linux=rappture-linux-i686-$(build_date).tar.gz
Tarfile_mac=rappture-macosx-$(build_date).tar.gz

all: pkgs rappture clean

pkgs: tcl tk itcl tdom blt tkimg shape python pyimg pynum expat scew vtk

rappture: install-rp rplib examples addons

installall: setup install-hamlet  install-nanohub install-web

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
	$(Rappture)/bin/python setup.py install --prefix=$(Rappture) >& $(basedir)/output.pyimg 2>&1

#################################################
pynum:
	echo "BUIDING python Numeric 24.2"
	cd $(basedir)/Numeric-24.2; \
	/bin/sh makeclean.sh; \
	$(Rappture)/bin/python setup.py build >& $(basedir)/output.num 2>&1; \
	$(Rappture)/bin/python setup.py install --prefix=$(Rappture) >> $(basedir)/output.num 2>&1

#################################################
# TODO
scipy:
	echo "BUIDING SciPy 0.3.2"
	cd $(basedir)/SciPy_complete-0.3.2; \
	$(Rappture)/bin/python setup.py build >& $(basedir)/output.sci 2>&1

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
	make >& $(basedir)/output.scew 2>&1; \
	make install >> $(basedir)/output.scew 2>&1

#############################################################################
# Install vtk 4.4 from binary
#############################################################################
vtk:
	cd $(basedir)/vtk.bin; make >& $(basedir)/output.vtk 2>&1

#############################################################################
# install-rp:
# 	- check out rappture from repository if not already in $(basedir)
# 	- install rappture for TCL
# 	- install rappture for Python
# 	- install rappture apps (driver, rappture, rerun) in $(Rappture) dir
#############################################################################

rp_update:	
	if test -d $(RP_SRC); then \
		cd $(RP_SRC); svn update ;\
	else \
		cd $(basedir); \
		svn checkout https://repo.nanohub.org/svn/rappture/trunk rappture; \
	fi

rp_gui: rp_update
	cd $(RP_SRC)/gui; \
	make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-blt=$(basedir)/blt2.4z/src; \
	make all; \
	make install

install-rp: rp_gui
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
	cd $(RP_SRC)/src; \
	make clean >& $(basedir)/output.rp 2>&1; \
	make all >& $(basedir)/output.rp 2>&1; \
	make install >& $(basedir)/output.rp 2>&1

#############################################################################
# build rappture examples
# examples:
# 	- compile rappture examples in rappture/examples
# 	- install rappture examples in $(Rappture)/examples
#############################################################################
examples:
	cd $(RP_SRC)/examples/app-fermi/fortran; make clean; make
	cd $(RP_SRC)/examples/app-fermi/cee; make clean; make
	cd $(RP_SRC)/examples/c-example; make clean; make
	rm -rf $(Rappture)/examples
	cp -r $(RP_SRC)/examples $(Rappture)

#############################################################################
# additional libs, files:
# #
addons:
	if test "`uname`" == "Linux"; then \
		cp -d /usr/lib/libstdc++.so.6* $(Rappture)/lib; \
		cp -d /usr/lib/libtiff.so.4* $(Rappture)/lib; \
		cp -d /usr/lib/gcc/i486-linux-gnu/4.0.3/libstdc++.a $(Rappture)/lib; \
		cp -d /usr/lib/gcc/i486-linux-gnu/4.0.3/libsupc++.a $(Rappture)/lib; \
		cp -d /usr/lib/gcc/i486-linux-gnu/4.0.3/libgcc_eh.a $(Rappture)/lib; \
	fi

staticlibs:
	if test "`uname`" == "Linux"; then \
		cp -d /usr/lib/gcc/i486-linux-gnu/4.0.3/libstdc++.a $(Rappture)/lib; \
	fi

#############################################################################
# installation scripts
#
tarfile:
	if test "$(build_date)" == ""; then \
		#echo `date +%Y%m%d`; \
		#export BDATE=`date +%Y%m%d`; echo $(BDATE); \
		echo -n "input date (yyyymmdd): "; \
		read $(build_date); \
	fi; \
	if test ! -d $(build_dir); then \
		mkdir $(build_dir); \
	fi; \
	cp -rp $(Rappture) $(build_dir)/$(build_date); \
	cd $(build_dir); \
	echo "creating rappture runtime package $(build_date)..."; \
	if test "`uname`" == "Linux"; then \
		tar czf $(Tarfile_linux) $(build_date); \
	else \
		tar czf $(Tarfile_mac) $(build_date); \
	fi; \
	echo done

setup:
	if test ! -d $(build_dir); then \
		mkdir $(build_dir); \
	fi; \
	if test ! -d $(build_dir)/tmp; then \
		mkdir $(build_dir)/tmp; \
	fi; \
	echo "$(build_dir) created\n"; \
	cd $(build_dir); \
	tar xzf /opt/rappture-*-$(build_date).tar.gz; \
	echo "rappture runtime extracted in $(build_dir)"; \
	cp -p rappture/bin/rappture rappture/bin/rerun rappture/examples/demo.bash tmp ;\
	mv rappture $(build_date)

install-hamlet2:
	cd $(build_dir); \
	echo "copying $(Tarfile_linux) to $(INSTALL_DIR_HAMLET)... ";\
	scp -rp $(build_date) $(INSTALL_DIR_HAMLET); \
	echo done

install-hamlet:
	cd /opt; \
	echo "copying $(Tarfile_linux) to $(INSTALL_DIR_HAMLET)... ";\
	scp $(build_date) $(INSTALL_DIR_HAMLET); \
	ssh 

install-nanohub:
	echo "editing rappture/rerun/demo.bash..."
	cd $(build_dir)/$(build_date)/bin; \
	sed -e "s/opt/apps/" < rappture > rappture.nanohub; \
	mv rappture.nanohub rappture; \
#	sed -e "s/opt/apps/" < rerun > rerun.nanohub; \
#	mv rerun.nanohub rerun; \
	cd $(build_dir)/$(build_date)/examples; \
	sed -e "s/opt/apps/" < demo.bash > demo.bash.nanohub; \
	mv demo.bash.nanohub demo.bash; \
	echo done
	cd $(build_dir); \
	echo "copying $(build_date) runtime to $(INSTALL_DIR_NANOHUB)... "; \
	scp -rp $(build_date) $(INSTALL_DIR_NANOHUB); \
	echo done

install-lepus:
	echo "installing on lepus... "; \
	cd $(build_dir); \
	cp -rp $(build_date) $(INSTALL_DIR_LEPUS); \
	cd $(INSTALL_DIR_LEPUS); \
	rm current; \
	ln -s $(build_date) current;
	echo "link current updated"
	echo done

install-web:
	echo "not implemented"

#############################################################################
clean:
	find $(Rappture) -name .svn | xargs rm -rf

cleanall:
	rm -rf $(Rappture)/*
	rm -rf $(build_dir)/*
	rm -f output.*
