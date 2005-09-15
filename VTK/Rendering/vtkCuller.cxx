/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkCuller.cxx,v $
  Language:  C++
  Date:      $Date: 2002/08/22 18:39:30 $
  Version:   $Revision: 1.3 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkCuller.h"

vtkCxxRevisionMacro(vtkCuller, "$Revision: 1.3 $");

vtkCuller::vtkCuller()
{
}

vtkCuller::~vtkCuller()
{
}

//----------------------------------------------------------------------------
void vtkCuller::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
