/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile: cmAddExecutableCommand.h,v $
  Language:  C++
  Date:      $Date: 2006/10/13 14:52:02 $
  Version:   $Revision: 1.14.2.1 $

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef cmExecutablesCommand_h
#define cmExecutablesCommand_h

#include "cmCommand.h"

/** \class cmExecutablesCommand
 * \brief Defines a list of executables to build.
 *
 * cmExecutablesCommand defines a list of executable (i.e., test)
 * programs to create.
 */
class cmAddExecutableCommand : public cmCommand
{
public:
  /**
   * This is a virtual constructor for the command.
   */
  virtual cmCommand* Clone()
    {
    return new cmAddExecutableCommand;
    }

  /**
   * This is called when the command is first encountered in
   * the CMakeLists.txt file.
   */
  virtual bool InitialPass(std::vector<std::string> const& args);

  /**
   * The name of the command as specified in CMakeList.txt.
   */
  virtual const char* GetName() { return "ADD_EXECUTABLE";}

  /**
   * Succinct documentation.
   */
  virtual const char* GetTerseDocumentation()
    {
    return
      "Add an executable to the project using the specified source files.";
    }

  /**
   * More documentation.
   */
  virtual const char* GetFullDocumentation()
    {
    return
      "  ADD_EXECUTABLE(exename [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL]\n"
      "                 source1 source2 ... sourceN)\n"
      "This command adds an executable target to the current directory.  "
      "The executable will be built from the list of source files "
      "specified.\n"
      "After specifying the executable name, WIN32 and/or MACOSX_BUNDLE can "
      "be specified. WIN32 indicates that the executable (when compiled on "
      "windows) is a windows app (using WinMain) not a console app "
      "(using main). The variable CMAKE_MFC_FLAG be used if the windows app "
      "uses MFC. This variable can be set to the following values:\n"
      " 0: Use Standard Windows Libraries\n"
      " 1: Use MFC in a Static Library \n"
      " 2: Use MFC in a Shared DLL \n"
      "MACOSX_BUNDLE indicates that when build on Mac OSX, executable should "
      "be in the bundle form. The MACOSX_BUNDLE also allows several "
      "variables to be specified:\n"
      "  MACOSX_BUNDLE_INFO_STRING\n"
      "  MACOSX_BUNDLE_ICON_FILE\n"
      "  MACOSX_BUNDLE_GUI_IDENTIFIER\n"
      "  MACOSX_BUNDLE_LONG_VERSION_STRING\n"
      "  MACOSX_BUNDLE_BUNDLE_NAME\n"
      "  MACOSX_BUNDLE_SHORT_VERSION_STRING\n"
      "  MACOSX_BUNDLE_BUNDLE_VERSION\n"
      "  MACOSX_BUNDLE_COPYRIGHT\n"
      "If EXCLUDE_FROM_ALL is given the target will not be built by default. "
      "It will be built only if the user explicitly builds the target or "
      "another target that requires the target depends on it."
      ;
    }

  cmTypeMacro(cmAddExecutableCommand, cmCommand);
};


#endif
