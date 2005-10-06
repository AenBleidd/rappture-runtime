#############################################################################
# Makefile - build and install all packages required by Rappture runtime
# 
# To build everything, type:
# 	make all
# 	
# To build individual package, tcl, for example:
# 	make tcl
#
# To build all non-rappture packages, type:
# 	make pkgs
#
# To build/install rappture
# 	make rappture
#
# Modify the first two lines below this block of comments.
#
# - change $basedir to point to your directory that contains this Makefile.
#   	The default is /opt/rappture-runtime.
#
# - change $Rappture to point to where you want rappture binaries to be. 
# 	The default is /opt/rappture.
#
#############################################################################
basedir=/opt/rappture-runtime
Rappture=/opt/rappture
RP_SRC=$(basedir)/rappture


all: tcl tk itcl tdom blt shape python expat scew install-rp rplib examples

pkgs: tcl tk itcl tdom blt shape python expat scew

rappture: install-rp rplib

#################################################
tcl:
	echo "BUIDING TCL8.4.11...." 
	cd $(basedir)/tcl8.4.11/unix; make clean; make distclean; \
	./configure --enable-shared --enable-threads --prefix=$(Rappture) >& $(basedir)/output.tcl; \
	make >> $(basedir)/output.tcl 2>&1; \
	make install >> $(basedir)/output.tcl 2>&1; \
	ln -s $(Rappture)/bin/tclsh8.4 $(Rappture)/bin/tclsh
	ln -s $(Rappture)/lib/libtcl8.4.so $(Rappture)/lib/libtcl8.4.so.0

#################################################
tk:
	echo "BUIDING Tk8.4.11...." 
	cd $(basedir)/tk8.4.11/unix; make clean; make distclean; \
	./configure --enable-shared --enable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib >& $(basedir)/output.tk 2>&1; \
	make >> $(basedir)/output.tk 2>& 1; \
	make install >> $(basedir)/output.tk 2>& 1; \
	ln -s $(Rappture)/bin/wish8.4 $(Rappture)/bin/wish
	ln -s $(Rappture)/lib/libtk8.4.so $(Rappture)/lib/libtk8.4.so.0

#################################################
itcl:
	echo "BUIDING itcl3.2.1...." 
	cd $(basedir)/itcl3.2.1; make clean; make distclean; \
	./configure --enable-shared --enable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib >& $(basedir)/output.itk 2>&1; \
	make all  >> $(basedir)/output.itk 2>& 1; \
	make install >> $(basedir)/output.itk 2>& 1;

#################################################
tdom:
	echo "BUIDING tdom-0.8.0..."
	cd $(basedir)/tDOM-0.8.0/unix; make clean; make distclean; \
	../configure --enable-shared --enable-threads --prefix=$(Rappture) --with-tcl=$(Rappture)/lib >& $(basedir)/output.tdom 2>&1; \
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
shape:
	echo "BUIDING Shape0.4 ... ..."
	cd $(basedir)/shape0.4/unix; make clean; make distclean; \
	./configure --prefix=$(Rappture) --with-tclconf=$(Rappture)/lib --with-tkconf=$(Rappture)/lib >& $(basedir)/output.shape 2>&1; \
	/bin/cp $(basedir)/other/Makefile.shape04 Makefile; \
	make >> $(basedir)/output.shape 2>&1; \
	make install >> $(basedir)/output.shape 2>&1

#################################################
python:
	echo "BUIDING python2.4.1..."
	cd $(basedir)/Python-2.4.1; make clean; make distclean; \
	./configure --enable-shared --enable-threads --prefix=$(Rappture) >& $(basedir)/output.py 2>&1 ; \
	make >> $(basedir)/output.py 2>&1; \
	make install >> $(basedir)/output.py 2>&1

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
	cp $(basedir)/other/Makefile.shared Makefile; \
	make clean; \
	make >& $(basedir)/output.scew 2>&1; \
	make install >> $(basedir)/output.scew 2>&1

#############################################################################
# install-rp:
# 	- check out rappture from repository if not already in $(basedir)
# 	- install rappture for TCL
# 	- install rappture for Python
# 	- install rappture apps (driver, rappture, rerun) in $(Rappture) dir
#############################################################################
install-rp:
	if test -d $(RP_SRC); then \
		: ;\
	else \
		cd $(basedir); \
		svn checkout https://repo.nanohub.org/svn/rappture/trunk rappture; \
	fi; \
	$(Rappture)/bin/tclsh $(RP_SRC)/tcl/install.tcl ; \
	cd $(RP_SRC)/python; \
	$(Rappture)/bin/python setup.py install ; \
	cp $(RP_SRC)/gui/apps/* $(Rappture)/bin ;\
	cp -r $(RP_SRC)/include/cee $(Rappture)/include ;\
	cp -r $(RP_SRC)/include/core $(Rappture)/include ;\
	cp -r $(RP_SRC)/include/fortran $(Rappture)/include; \
	find $(Rappture)/include -name .svn -exec rm -rf "{}" \;


#############################################################################
# build rappture libs - assuming "rappture" dir was checked out from 
# 			https://repo.nanohub.org/svn/rappture/trunk rappture
# install-rp:
# 	- build rappture libs in rappture/src dir
# 	- install rappture libs in $(Rappture) dir 
#############################################################################
rplib: install-rp
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
	cd $(RP_SRC)/examples/app-fermi/fortran; make clean; make; \
	cd $(RP_SRC)/examples/c-example; make clean; make; \
	cd $(RP_SRC)/examples/fermi_fortran; make clean; make; \
	cp -r $(RP_SRC)/examples $(Rappture)
#	find $(Rappture)/examples -name .svn -exec rm -rf "{}" \;


#############################################################################
clean:
	rm -f output.*
