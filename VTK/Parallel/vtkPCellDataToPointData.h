/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPCellDataToPointData.h,v $
  Language:  C++
  Date:      $Date: 2002/03/12 18:22:33 $
  Version:   $Revision: 1.1 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPCellDataToPointData - Compute point arrays from cell arrays.
// .SECTION Description
// Like it super class, this filter averages the cell data around
// a point to get new point data.  This subclass requests a layer of
// ghost cells to make the results invariant to pieces.  There is a 
// "PieceInvariant" flag that lets the user change the behavior
// of the filter to that of its superclass.

#ifndef __vtkPCellDataToPointData_h
#define __vtkPCellDataToPointData_h

#include "vtkCellDataToPointData.h"

class VTK_PARALLEL_EXPORT vtkPCellDataToPointData : public vtkCellDataToPointData
{
public:
  vtkTypeRevisionMacro(vtkPCellDataToPointData,vtkCellDataToPointData);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  static vtkPCellDataToPointData *New();

  // Description:
  // To get piece invariance, this filter has to request an 
  // extra ghost level.  By default piece invariance is on.
  vtkSetMacro(PieceInvariant, int);
  vtkGetMacro(PieceInvariant, int);
  vtkBooleanMacro(PieceInvariant, int);

protected:
  vtkPCellDataToPointData();
  ~vtkPCellDataToPointData() {};

  // Usual data generation method
  virtual void Execute();
  void ComputeInputUpdateExtents(vtkDataObject *output);

  int PieceInvariant;
private:
  vtkPCellDataToPointData(const vtkPCellDataToPointData&);  // Not implemented.
  void operator=(const vtkPCellDataToPointData&);  // Not implemented.
};

#endif
