RAPPTURE = /opt/rappture
VTK_DIR = $(RAPPTURE)/lib/vtk
VTK_INC = $(RAPPTURE)/include/vtk
bindir_mac = `pwd`/mac
bindir_linux = `pwd`/linux

default: install_bin install_lib install_include

install_bin:
	if test "`uname`" == "Darwin"; then \
		echo "copying vtk from $(bindir_mac)/bin/vtk to $(RAPPTURE)/bin"; \
		cp $(bindir_mac)/bin/vtk $(RAPPTURE)/bin; \
	else \
		echo "copying vtk from $(bindir_linux)/bin/vtk to $(RAPPTURE)/bin"; \
		cp $(bindir_linux)/bin/vtk $(RAPPTURE)/bin; \
	fi

install_lib:
	rm -rf $(VTK_DIR)
	if test "`uname`" == "Darwin"; then \
		echo "copying libs from $(bindir_mac)/lib/vtk to $(RAPPTURE)/lib"; \
		cd $(bindir_mac)/lib/vtk; cp libvtk* $(RAPPTURE)/lib; cp -R tcl $(VTK_DIR); \
	else \
		echo "copying libs from $(bindir_linux)/lib/vtk to $(RAPPTURE)/lib"; \
		cd $(bindir_linux)/lib/vtk; cp libvtk* $(RAPPTURE)/lib; cp -R tcl $(VTK_DIR); \
	fi

install_include:
	rm -rf $(VTK_INC)
	if test "`uname`" == "Darwin"; then \
		echo "copying inc from $(bindir_mac)/include/vtk to $(RAPPTURE)/include"; \
		cp -R $(bindir_mac)/include/vtk $(RAPPTURE)/include; \
	else \
		echo "copying inc from $(bindir_linux)/include/vtk to $(RAPPTURE)/include"; \
		cp -R $(bindir_linux)/include/vtk $(RAPPTURE)/include; \
	fi
