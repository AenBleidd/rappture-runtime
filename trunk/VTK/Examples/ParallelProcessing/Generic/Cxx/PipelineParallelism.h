/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: PipelineParallelism.h,v $
  Language:  C++
  Date:      $Date: 2002/01/22 15:27:34 $
  Version:   $Revision: 1.2 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkMultiProcessController.h"

void pipe1(vtkMultiProcessController* controller, void* arg);
void pipe2(vtkMultiProcessController* controller, void* arg);
