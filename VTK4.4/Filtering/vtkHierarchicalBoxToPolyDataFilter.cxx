/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkHierarchicalBoxToPolyDataFilter.cxx,v $
  Language:  C++
  Date:      $Date: 2003/12/11 15:47:37 $
  Version:   $Revision: 1.1 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkHierarchicalBoxToPolyDataFilter.h"

#include "vtkHierarchicalBoxDataSet.h"

vtkCxxRevisionMacro(vtkHierarchicalBoxToPolyDataFilter, 
                    "$Revision: 1.1 $");

//----------------------------------------------------------------------------
// Specify the input data or filter.
void vtkHierarchicalBoxToPolyDataFilter::SetInput(
  vtkHierarchicalBoxDataSet *input)
{
  this->vtkProcessObject::SetNthInput(0, input);
}

//----------------------------------------------------------------------------
// Specify the input data or filter.
vtkHierarchicalBoxDataSet *vtkHierarchicalBoxToPolyDataFilter::GetInput()
{
  if (this->NumberOfInputs < 1)
    {
    return NULL;
    }
  
  return (vtkHierarchicalBoxDataSet *)(this->Inputs[0]);
}

//----------------------------------------------------------------------------
void vtkHierarchicalBoxToPolyDataFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
