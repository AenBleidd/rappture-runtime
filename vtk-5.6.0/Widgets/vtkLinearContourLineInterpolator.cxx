/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkLinearContourLineInterpolator.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkLinearContourLineInterpolator.h"
#include <vtkObjectFactory.h>

vtkCxxRevisionMacro(vtkLinearContourLineInterpolator, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkLinearContourLineInterpolator);

//----------------------------------------------------------------------
vtkLinearContourLineInterpolator::vtkLinearContourLineInterpolator()
{
}

//----------------------------------------------------------------------
vtkLinearContourLineInterpolator::~vtkLinearContourLineInterpolator()
{
}

//----------------------------------------------------------------------
int vtkLinearContourLineInterpolator::InterpolateLine( vtkRenderer *vtkNotUsed(ren),
                                                       vtkContourRepresentation *vtkNotUsed(rep),
                                                       int vtkNotUsed(idx1), int vtkNotUsed(idx2) )
{
  return 1;
}

//----------------------------------------------------------------------
void vtkLinearContourLineInterpolator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
