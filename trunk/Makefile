
prefix			= /home/gah/builds/20090317
exec_prefix		= /home/gah/builds/20090317
datadir			= ${datarootdir}
datarootdir		= ${prefix}/share
bindir			= ${exec_prefix}/bin
libdir			= /home/gah/builds/20090317/lib
includedir		= /home/gah/builds/20090317/include
mandir			= ${datarootdir}/man
srcdir			= .

SHELL			= /bin/sh
RM			= rm -f

INSTALL			= /usr/bin/install -c

TCL_DIR			= tcl8.4.19/unix
TK_DIR			= tk8.4.19/unix
EXPAT_DIR		= 
ZLIB_DIR		= 
CMAKE_DIR		= 

ifneq ($(ZLIB_DIR),)
   subdirs += $(ZLIB_DIR)
endif
ifneq ($(EXPAT_DIR),)
   subdirs += $(EXPAT_DIR)
endif
ifneq ($(TCL_DIR),)
   subdirs += $(TCL_DIR)
endif
ifneq ($(TK_DIR),)
   subdirs += $(TK_DIR)
endif
ifneq ($(CMAKE_DIR),)
   subdirs += $(CMAKE_DIR)
endif

all: 
	for i in $(subdirs); do \
	   $(MAKE) -C $$i all || exit 1 ; \
	done

install: 
	for i in $(subdirs); do \
	   $(MAKE) -C $$i install || exit 1 ; \
	done

clean: 
	for i in $(subdirs); do \
	   $(MAKE) -C $$i clean || exit 1 ; \
	done

distclean: 
	for i in $(subdirs); do \
	   $(MAKE) -C $$i distclean || exit 1 ; \
	done


