/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkStructuredGridToStructuredGridFilter.cxx,v $
  Language:  C++
  Date:      $Date: 2002/10/04 20:43:44 $
  Version:   $Revision: 1.18 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkStructuredGridToStructuredGridFilter.h"

#include "vtkStructuredGrid.h"

vtkCxxRevisionMacro(vtkStructuredGridToStructuredGridFilter, "$Revision: 1.18 $");

//----------------------------------------------------------------------------
// Specify the input data or filter.
void vtkStructuredGridToStructuredGridFilter::SetInput(vtkStructuredGrid *input)
{
  this->vtkProcessObject::SetNthInput(0, input);
}

//----------------------------------------------------------------------------
// Specify the input data or filter.
vtkStructuredGrid *vtkStructuredGridToStructuredGridFilter::GetInput()
{
  if (this->NumberOfInputs < 1)
    {
    return NULL;
    }
  
  return (vtkStructuredGrid *)(this->Inputs[0]);
}


//----------------------------------------------------------------------------
void vtkStructuredGridToStructuredGridFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
