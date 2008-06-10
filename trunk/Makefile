BASE_DIR	= $(HOME)
DATE		= $(shell date +%Y%m%d)
build_dir	= $(BASE_DIR)/builds/$(DATE)
config_flags	= --without-pymol --without-vtk --with-matlab=no

all: mkdirs stage1 stage2 stage3

mkdirs:
	mkdir -p $(build_dir)

install: install_stage1 install_stage2 install_stage2

stage1: config_stage1 build_stage1 install_stage1
stage2: config_stage2 build_stage2 install_stage2
stage3: config_stage3 build_stage3 install_stage3

config_stage1:
	STAGE=stage1 ./configure --prefix=$(build_dir) $(config_flags)
config_stage2:
	STAGE=stage2 ./configure --prefix=$(build_dir) $(config_flags)
config_stage3:
	STAGE=stage3 ./configure --prefix=$(build_dir) $(config_flags)
build_stage1:
	$(MAKE) -f build/Makefile-stage1 all
build_stage2:
	$(MAKE) -f build/Makefile-stage2 all
build_stage3:
	$(MAKE) -f build/Makefile-stage3 all

install_stage1:
	$(MAKE) -f build/Makefile-stage1 install
install_stage2:
	$(MAKE) -f build/Makefile-stage2 install
install_stage3:
	$(MAKE) -f build/Makefile-stage3 install

clean:
	-$(MAKE) -f build/Makefile-stage1 clean
	-$(MAKE) -f build/Makefile-stage2 clean
	-$(MAKE) -f build/Makefile-stage3 clean

distclean:
	-$(MAKE) -f build/Makefile-stage1 distclean
	-$(MAKE) -f build/Makefile-stage2 distclean
	-$(MAKE) -f build/Makefile-stage3 distclean

package:
