BINARIES = decoder encoder b64dec b64enc
LIBRARIES = libb64.a libb64.so

SOURCES = b64dec.c  b64enc.c  cdecode.c  cencode.c  decoder.cc  encoder.cc

TARGETS = $(LIBRARIES) $(BINARIES)

LINK.o = g++

CFLAGS:= -I../include
CXXFLAGS:= -I../include

vpath %.h ../include/b64

.PHONY : clean

all: $(TARGETS) #strip

b64enc b64dec encoder decoder: libb64.a
libb64.a: cencode.o cdecode.o
	$(AR) $(ARFLAGS) $@ $^

LDLIB_MACOSX = -dynamiclib -o $@.dylib
LDLIB_LINUX = -shared -Wl,-rpath,./ -Wl,-soname,$@.so -o $@.so.0.0
libb64: cencode.o cdecode.o
	if test "`uname`" == "Darwin"; then \
		$(CXX) $(DEGUG) $(LDLIB_MACOSX) $^; \
		$(AR) $(ARFLAGS) $@.a $^; \
		ranlib -s $@.a; \
	else \
		$(CXX) $(DEGUG) $(LDLIB_LINUX) $^; \
		/sbin/ldconfig -n $(LIB_DIR); \
		$(AR) $(ARFLAGS) $@.a $^; \
		ranlib $@.a; \
	fi

strip:
	strip $(BINARIES)

clean:
	rm -f *.exe* *.o $(TARGETS) *.bak *~ *.so *.so.*

distclean: clean
	rm -f depend

depend: $(SOURCES)
	makedepend -f- $(CFLAGS) $(SOURCES) 2> /dev/null 1> depend

-include depend

