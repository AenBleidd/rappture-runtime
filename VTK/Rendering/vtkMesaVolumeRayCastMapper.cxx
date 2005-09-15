/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMesaVolumeRayCastMapper.cxx,v $
  Language:  C++
  Date:      $Date: 2002/01/22 15:38:46 $
  Version:   $Revision: 1.5 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// Make sure this is first, so any includes of gl.h can be stoped if needed
#define VTK_IMPLEMENT_MESA_CXX

#include "MangleMesaInclude/gl_mangle.h"
#include "MangleMesaInclude/gl.h"

#include <math.h>
#include "vtkMesaVolumeRayCastMapper.h"

// make sure this file is included before the #define takes place
// so we don't get two vtkMesaVolumeRayCastMapper classes defined.
#include "vtkOpenGLVolumeRayCastMapper.h"
#include "vtkMesaVolumeRayCastMapper.h"

// Make sure vtkMesaVolumeRayCastMapper is a copy of 
// vtkOpenGLVolumeRayCastMapper with vtkOpenGLVolumeRayCastMapper 
// replaced with vtkMesaVolumeRayCastMapper
#define vtkOpenGLVolumeRayCastMapper vtkMesaVolumeRayCastMapper
#include "vtkOpenGLVolumeRayCastMapper.cxx"
#undef vtkOpenGLVolumeRayCastMapper

vtkCxxRevisionMacro(vtkMesaVolumeRayCastMapper, "$Revision: 1.5 $");
vtkStandardNewMacro(vtkMesaVolumeRayCastMapper);
