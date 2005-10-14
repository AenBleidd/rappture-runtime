RAPPTURE = /opt/rappture
VTK_DIR = $(RAPPTURE)/lib/vtk
VTK_INC = $(RAPPTURE)/include/vtk
bin_dir_mac = `pwd`/mac
bin_dir_linux = `pwd`/linux
from_dir = $(bin_dir_linux)

default: setdir install_bin install_lib install_include

setdir:
	if test "`uname`" == "Darwin"; then \
		from_dir = $(bin_dir_mac); \
	fi;
	echo "Installing vtk binaries from $(from_dir)..."

install_bin:
	cp $(from_dir)/bin/vtk $(RAPPTURE)/bin

install_lib:
	rm -rf $(VTK_DIR); \
	cd $(from_dir)/lib/vtk; \
	cp libvtk* $(RAPPTURE)/lib; \
	cp -R tcl $(VTK_DIR)

install_include:
	rm -rf $(VTK_INC); \
	cp -R $(from_dir)/include/vtk $(RAPPTURE)/include
