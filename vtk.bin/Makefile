RAPPTURE = /opt/rappture
VTK_LIB = $(RAPPTURE)/lib/vtk
VTK_INC = $(RAPPTURE)/include/vtk

#sysname := `uname`
#hname := `./subname.sh`

installdir := $(shell pwd)/linux.gcc3.3

#ifeq ($(sysname),Darwin)
#	installdir := `pwd`/mac
#endif
#
#ifeq ('$(hname)', 'shadow')
#	installdir := `pwd`/linux.gcc3.3
#endif

default: install

try:
	echo hname $(hname)
	echo sysname $(sysname)
	echo installdir $(installdir)

install:
	set -x
	rm -rf $(VTK_LIB)
	rm -rf $(VTK_INC)
	cp $(installdir)/bin/vtk $(RAPPTURE)/bin
	cd $(installdir)/lib/vtk; \
	cp libvtk* $(RAPPTURE)/lib; \
	cp -R tcl $(VTK_LIB)
	cp -R $(installdir)/include/vtk $(RAPPTURE)/include

