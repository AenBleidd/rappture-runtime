/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImageTwoInputFilter.cxx,v $
  Language:  C++
  Date:      $Date: 2002/10/04 20:43:43 $
  Version:   $Revision: 1.24 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkImageTwoInputFilter.h"

#include "vtkImageData.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkImageTwoInputFilter, "$Revision: 1.24 $");

//----------------------------------------------------------------------------
vtkImageTwoInputFilter::vtkImageTwoInputFilter()
{
  this->NumberOfRequiredInputs = 2;
  this->SetNumberOfInputs(2);
  this->Inputs[0] = NULL;
  this->Inputs[1] = NULL;
}

//----------------------------------------------------------------------------
// Set the Input1 of this filter. If a ScalarType has not been set,
// then the ScalarType of the input is used.
void vtkImageTwoInputFilter::SetInput1(vtkImageData *input)
{
  this->vtkImageMultipleInputFilter::SetNthInput(0,input);
}



//----------------------------------------------------------------------------
// Set the Input2 of this filter. If a ScalarType has not been set,
// then the ScalarType of the input is used.
void vtkImageTwoInputFilter::SetInput2(vtkImageData *input)
{
  this->vtkImageMultipleInputFilter::SetNthInput(1,input);
}

//----------------------------------------------------------------------------
void vtkImageTwoInputFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
