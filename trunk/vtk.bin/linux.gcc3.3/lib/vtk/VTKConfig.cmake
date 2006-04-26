#-----------------------------------------------------------------------------
#
# VTKConfig.cmake - VTK CMake configuration file for external projects.
#
# This file is configured by VTK and used by the UseVTK.cmake module
# to load VTK's settings for an external project.

# The VTK include file directories.
SET(VTK_INCLUDE_DIRS "/home/cxsong/rappture-runtime/VTK4.4/build/include/vtk;/usr/include;/opt/rappture/include;/opt/rappture/include")

# The VTK library directories.
SET(VTK_LIBRARY_DIRS "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk")

# The C and C++ flags added by VTK to the cmake-configured flags.
SET(VTK_REQUIRED_C_FLAGS " -I/usr/X11R6/include")
SET(VTK_REQUIRED_CXX_FLAGS " -Wno-deprecated -I/usr/X11R6/include")
SET(VTK_REQUIRED_EXE_LINKER_FLAGS "")

# The VTK version number
SET(VTK_MAJOR_VERSION "4")
SET(VTK_MINOR_VERSION "4")
SET(VTK_BUILD_VERSION "2")

# The location of the UseVTK.cmake file.
SET(VTK_USE_FILE "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/UseVTK.cmake")

# The build settings file.
SET(VTK_BUILD_SETTINGS_FILE "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/VTKBuildSettings.cmake")

# The directory containing class list files for each kit.
SET(VTK_KITS_DIR "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk")

# The wrapping hints file.
SET(VTK_WRAP_HINTS "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/hints")

# CMake extension module directory and macro file.
SET(VTK_LOAD_CMAKE_EXTENSIONS_MACRO "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/CMake/vtkLoadCMakeExtensions.cmake")
SET(VTK_CMAKE_EXTENSIONS_DIR "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/CMake")

# The list of available kits.
SET(VTK_KITS "COMMON;FILTERING;IO;GRAPHICS;IMAGING;RENDERING;HYBRID;PARALLEL")

# The list of available languages.
SET(VTK_LANGUAGES "TCL")

# VTK Configuration options.
SET(VTK_BUILD_SHARED_LIBS "ON")
SET(VTK_DEBUG_LEAKS "OFF")
SET(VTK_DISABLE_TK_INIT "")
SET(VTK_HAVE_VG500 "")
SET(VTK_HAVE_VP1000 "")
SET(VTK_USE_MANGLED_MESA "OFF")
SET(VTK_MPIRUN_EXE "")
SET(VTK_MPI_MAX_NUMPROCS "")
SET(VTK_MPI_POSTFLAGS "")
SET(VTK_MPI_PREFLAGS "")
SET(VTK_OPENGL_HAS_OSMESA "OFF")
SET(VTK_USE_64BIT_IDS "OFF")
SET(VTK_USE_ANSI_STDLIB "ON")
SET(VTK_USE_CARBON "OFF")
SET(VTK_USE_COCOA "OFF")
SET(VTK_USE_HYBRID "ON")
SET(VTK_USE_MATROX_IMAGING "OFF")
SET(VTK_USE_MPI "")
SET(VTK_USE_PARALLEL "ON")
SET(VTK_USE_PATENTED "OFF")
SET(VTK_USE_RENDERING "ON")
SET(VTK_USE_VIDEO_FOR_WINDOWS "OFF")
SET(VTK_USE_VOLUMEPRO "OFF")
SET(VTK_USE_GL2PS "OFF")
SET(VTK_USE_X "ON")
SET(VTK_WRAP_JAVA "OFF")
SET(VTK_WRAP_PYTHON "OFF")
SET(VTK_WRAP_TCL "ON")
SET(TCL_TK_STATIC "OFF")
SET(TK_RESOURCE_FILE "")

# The VTK executable locations.
SET(VTK_TCL_HOME "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/tcl")
SET(VTK_JAVA_JAR "")
SET(VTK_PARSE_JAVA_EXE "")
SET(VTK_WRAP_JAVA_EXE "")
SET(VTK_WRAP_PYTHON_EXE "")
SET(VTK_WRAP_TCL_EXE "/home/cxsong/rappture-runtime/VTK4.4/build/bin/vtkWrapTcl")
SET(VTK_DOXYGEN_HOME "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/doxygen")
SET(VTK_TK_INTERNAL_DIR "")

# The VTK test script locations.
SET(VTK_HEADER_TESTING_PY "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/testing/HeaderTesting.py")
SET(VTK_FIND_STRING_TCL "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/testing/FindString.tcl")
SET(VTK_PRINT_SELF_CHECK_TCL "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/testing/PrintSelfCheck.tcl")
SET(VTK_RT_IMAGE_TEST_TCL "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/testing/rtImageTest.tcl")
SET(VTK_PRT_IMAGE_TEST_TCL "/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/testing/prtImageTest.tcl")

# The names of utility libraries used by VTK.
SET(VTK_PNG_LIBRARIES "vtkpng")
SET(VTK_ZLIB_LIBRARIES "vtkzlib")
SET(VTK_JPEG_LIBRARIES "vtkjpeg")
SET(VTK_TIFF_LIBRARIES "vtktiff")
SET(VTK_EXPAT_LIBRARIES "vtkexpat")

# The VTK library dependencies.
IF(NOT VTK_NO_LIBRARY_DEPENDS)
  INCLUDE("/home/cxsong/rappture-runtime/VTK4.4/build/lib/vtk/VTKLibraryDepends.cmake")
ENDIF(NOT VTK_NO_LIBRARY_DEPENDS)
