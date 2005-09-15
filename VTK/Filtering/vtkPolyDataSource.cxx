/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPolyDataSource.cxx,v $
  Language:  C++
  Date:      $Date: 2002/10/04 20:43:44 $
  Version:   $Revision: 1.7 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPolyDataSource.h"

#include "vtkObjectFactory.h"
#include "vtkPolyData.h"

vtkCxxRevisionMacro(vtkPolyDataSource, "$Revision: 1.7 $");

//----------------------------------------------------------------------------
vtkPolyDataSource::vtkPolyDataSource()
{
  this->vtkSource::SetNthOutput(0, vtkPolyData::New());
  // Releasing data for pipeline parallism.
  // Filters will know it is empty. 
  this->Outputs[0]->ReleaseData();
  this->Outputs[0]->Delete();
  this->ExecutePiece = this->ExecuteNumberOfPieces = 0;
  this->ExecuteGhostLevel = 0;
}

//----------------------------------------------------------------------------
vtkPolyData *vtkPolyDataSource::GetOutput()
{
  if (this->NumberOfOutputs < 1)
    {
    return NULL;
    }
  
  return (vtkPolyData *)(this->Outputs[0]);
}

//----------------------------------------------------------------------------
vtkPolyData *vtkPolyDataSource::GetOutput(int idx)
{
  return (vtkPolyData *) this->vtkSource::GetOutput(idx); 
}

//----------------------------------------------------------------------------
void vtkPolyDataSource::SetOutput(vtkPolyData *output)
{
  this->vtkSource::SetNthOutput(0, output);
}


//----------------------------------------------------------------------------
void vtkPolyDataSource::ComputeInputUpdateExtents(vtkDataObject *data)
{
  int piece, numPieces, ghostLevel;
  vtkPolyData *output = (vtkPolyData *)data;
  int idx;

  output->GetUpdateExtent(piece, numPieces, ghostLevel);
  
  // make sure piece is valid
  if (piece < 0 || piece >= numPieces)
    {
    return;
    }
  
  if (ghostLevel < 0)
    {
    return;
    }
  
  // just copy the Update extent as default behavior.
  for (idx = 0; idx < this->NumberOfInputs; ++idx)
    {
    if (this->Inputs[idx])
      {
      this->Inputs[idx]->SetUpdateExtent(piece, numPieces, ghostLevel);
      }
    }
  
  // Save the piece so execute can use this information.
  this->ExecutePiece = piece;
  this->ExecuteNumberOfPieces = numPieces;
  
  this->ExecuteGhostLevel = ghostLevel;
}

//----------------------------------------------------------------------------
void vtkPolyDataSource::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
