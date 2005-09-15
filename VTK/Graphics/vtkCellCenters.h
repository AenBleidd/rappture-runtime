/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkCellCenters.h,v $
  Language:  C++
  Date:      $Date: 2002/01/22 15:29:09 $
  Version:   $Revision: 1.17 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCellCenters - generate points at center of cells
// .SECTION Description
// vtkCellCenters is a filter that takes as input any dataset and 
// generates on output points at the center of the cells in the dataset.
// These points can be used for placing glyphs (vtkGlyph3D) or labeling 
// (vtkLabeledDataMapper). (The center is the parametric center of the
// cell, not necessarily the geometric or bounding box center.) The cell
// attributes will be associated with the points on output.
// 
// .SECTION Caveats
// You can choose to generate just points or points and vertex cells.
// Vertex cells are drawn during rendering; points are not. Use the ivar
// VertexCells to generate cells.

// .SECTION See Also
// vtkGlyph3D vtkLabeledDataMapper

#ifndef __vtkCellCenters_h
#define __vtkCellCenters_h

#include "vtkDataSetToPolyDataFilter.h"

class VTK_GRAPHICS_EXPORT vtkCellCenters : public vtkDataSetToPolyDataFilter
{
public:
  vtkTypeRevisionMacro(vtkCellCenters,vtkDataSetToPolyDataFilter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object with vertex cell generation turned off.
  static vtkCellCenters *New();

  // Description:
  // Enable/disable the generation of vertex cells.
  vtkSetMacro(VertexCells,int);
  vtkGetMacro(VertexCells,int);
  vtkBooleanMacro(VertexCells,int);

protected:
  vtkCellCenters();
  ~vtkCellCenters() {};

  void Execute();

  int VertexCells;
private:
  vtkCellCenters(const vtkCellCenters&);  // Not implemented.
  void operator=(const vtkCellCenters&);  // Not implemented.
};

#endif
