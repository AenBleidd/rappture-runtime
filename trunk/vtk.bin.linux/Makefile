RAPPTURE = /opt/rappture
VTK_DIR = $(RAPPTURE)/lib/vtk
VTK_INC = $(RAPPTURE)/include/vtk

default: install_bin install_lib install_include

install_lib:
	cd lib/vtk; \
	if test -d $(VTK_DIR); then \
		rm -rf $(VTK_DIR); \
	fi; \
	cp libvtk* $(RAPPTURE)/lib; \
	cp -R tcl $(VTK_DIR)

install_bin:
	cp bin/vtk $(RAPPTURE)/bin

install_include:
	cp -R include/vtk $(RAPPTURE)/include
