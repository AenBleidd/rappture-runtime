/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMultiBlockDataSetInternal.h,v $
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

#ifndef __vtkMultiBlockDataSetInternal_h
#define __vtkMultiBlockDataSetInternal_h

#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

#include <vtkstd/vector>

class vtkMultiBlockDataSetInternal
{
public:
  vtkstd::vector< vtkSmartPointer<vtkDataObject> > DataSets;
};

#endif
