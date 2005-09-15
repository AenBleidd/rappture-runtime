/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPPolyDataNormals.cxx,v $
  Language:  C++
  Date:      $Date: 2002/08/30 21:05:53 $
  Version:   $Revision: 1.9 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPPolyDataNormals.h"

#include "vtkObjectFactory.h"
#include "vtkPolyData.h"

vtkCxxRevisionMacro(vtkPPolyDataNormals, "$Revision: 1.9 $");
vtkStandardNewMacro(vtkPPolyDataNormals);

//----------------------------------------------------------------------------
vtkPPolyDataNormals::vtkPPolyDataNormals()
{
  this->PieceInvariant = 1;
}

//----------------------------------------------------------------------------
void vtkPPolyDataNormals::Execute()
{
  vtkPolyData *output = this->GetOutput();

  this->vtkPolyDataNormals::Execute();
  
  if (this->PieceInvariant)
    {
    output->RemoveGhostCells(output->GetUpdateGhostLevel()+1);
    }
                                                                   
}

//--------------------------------------------------------------------------
void vtkPPolyDataNormals::ComputeInputUpdateExtents(vtkDataObject *output)
{
  vtkPolyData *input = this->GetInput();
  int piece = output->GetUpdatePiece();
  int numPieces = output->GetUpdateNumberOfPieces();
  int ghostLevel = output->GetUpdateGhostLevel();

  if (input == NULL)
    {
    return;
    }
  if (this->PieceInvariant)
    {
    input->SetUpdatePiece(piece);
    input->SetUpdateNumberOfPieces(numPieces);
    input->SetUpdateGhostLevel(ghostLevel + 1);
    }
  else
    {
    input->SetUpdatePiece(piece);
    input->SetUpdateNumberOfPieces(numPieces);
    input->SetUpdateGhostLevel(ghostLevel);
    }
}

//----------------------------------------------------------------------------
void vtkPPolyDataNormals::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "PieceInvariant: "
     << this->PieceInvariant << "\n";
}
