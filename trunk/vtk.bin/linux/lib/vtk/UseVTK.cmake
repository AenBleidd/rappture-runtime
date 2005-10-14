#
# This module is provided as VTK_USE_FILE by VTKConfig.cmake.  It can
# be INCLUDEd in a project to load the needed compiler and linker
# settings to use VTK.
#

# Load the compiler settings used for VTK.
IF(VTK_BUILD_SETTINGS_FILE)
  INCLUDE(${CMAKE_ROOT}/Modules/CMakeImportBuildSettings.cmake)
  CMAKE_IMPORT_BUILD_SETTINGS(${VTK_BUILD_SETTINGS_FILE})
ENDIF(VTK_BUILD_SETTINGS_FILE)

# Add compiler flags needed to use VTK.
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${VTK_REQUIRED_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${VTK_REQUIRED_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${VTK_REQUIRED_EXE_LINKER_FLAGS}")

# Add include directories needed to use VTK.
INCLUDE_DIRECTORIES(${VTK_INCLUDE_DIRS})

# Add link directories needed to use VTK.
LINK_DIRECTORIES(${VTK_LIBRARY_DIRS})

# Import the VTK_LOAD_CMAKE_EXTENSIONS macro.
INCLUDE(${VTK_LOAD_CMAKE_EXTENSIONS_MACRO})

# Load VTK's CMake extension commands.
VTK_LOAD_CMAKE_EXTENSIONS(${VTK_CMAKE_EXTENSIONS_DIR})
