/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMapper2D.cxx,v $
  Language:  C++
  Date:      $Date: 2002/07/03 15:59:39 $
  Version:   $Revision: 1.17 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkMapper2D.h"
#include "vtkViewport.h"
#include "vtkActor2D.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkMapper2D, "$Revision: 1.17 $");

void vtkMapper2D::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

