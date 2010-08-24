/*=========================================================================

Program:   Visualization Toolkit
Module:    $RCSfile: vtkCocoaTkUtilities.h,v $

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCocoaTkUtilities - Internal Tk Routines for Cocoa
//
// .SECTION Description
// vtkCocoaTkUtilities provide access to the Tk internals for Cocoa
// implementations of Tk.  These internals must be implemented in a .mm
// file, since Cocoa is Objective C, but the header file itself is 
// pure C++ so that it can be included by other VTK classes.
//
// .SECTION See Also
// vtkCocoaGLView

// .SECTION Warning
// This header must be in C++ only because it is included by .cxx files.
// That means no Objective-C may be used. That's why some instance variables 
// are void* instead of what they really should be.

#ifndef __vtkvtkCocoaTkUtilities_h
#define __vtkvtkCocoaTkUtilities_h

#include "vtkObject.h"

struct Tk_Window_;

class VTK_RENDERING_EXPORT vtkCocoaTkUtilities : public vtkObject
{
public:
  static vtkCocoaTkUtilities *New();
  vtkTypeRevisionMacro(vtkCocoaTkUtilities,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Return the NSView for a Tk_Window.  It is returned as a void pointer
  // so that users of this function don't need to compile as Objective C.
  static void* GetDrawableView(Tk_Window_ *window);

protected:
  vtkCocoaTkUtilities() {};
  ~vtkCocoaTkUtilities() {};
  
private:
  vtkCocoaTkUtilities(const vtkCocoaTkUtilities&);  // Not implemented.
  void operator=(const vtkCocoaTkUtilities&);  // Not implemented.
};

#endif
