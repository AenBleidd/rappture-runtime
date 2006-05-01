ifndef RAPPTURE
RAPPTURE = /opt/rappture
endif

VTK_LIB = $(RAPPTURE)/lib/vtk
VTK_INC = $(RAPPTURE)/include/vtk

# default set to gcc3.3 compiled vtk binaries
installdir := $(shell pwd)/linux

ifeq ($(sysname),Darwin)
	installdir := $(shell pwd)/mac
else
ifeq ($(findstring lepus, $(shell hostname)), lepus)
	installdir := $(shell pwd)/linux.gcc4.0
endif
endif

default: install

install:
	set -x; 
	rm -rf $(VTK_LIB); \
	rm -rf $(VTK_INC); \
	cp $(installdir)/bin/vtk $(RAPPTURE)/bin; \
	cd $(installdir)/lib/vtk; \
	cp libvtk* $(RAPPTURE)/lib; \
	cp -R tcl $(VTK_LIB); \
	cp -R $(installdir)/include/vtk $(RAPPTURE)/include

