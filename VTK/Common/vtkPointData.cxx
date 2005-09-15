/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPointData.cxx,v $
  Language:  C++
  Date:      $Date: 2002/01/22 15:25:57 $
  Version:   $Revision: 1.66 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPointData.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkPointData, "$Revision: 1.66 $");
vtkStandardNewMacro(vtkPointData);

void vtkPointData::NullPoint (vtkIdType ptId)
{
  vtkFieldData::Iterator it(this);
  vtkDataArray* da;
  for(da=it.Begin(); !it.End(); da=it.Next())
    {
    if (da)
      {
      int length = da->GetNumberOfComponents();
      float* tuple = new float[length];
      for(int j=0; j<length; j++)
        {
        tuple[j] = 0;
        }
      da->InsertTuple(ptId, tuple);
      delete[] tuple;
      }
    }
}

void vtkPointData::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
