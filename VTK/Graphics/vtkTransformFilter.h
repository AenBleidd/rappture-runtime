/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkTransformFilter.h,v $
  Language:  C++
  Date:      $Date: 2002/11/19 21:24:02 $
  Version:   $Revision: 1.44 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkTransformFilter - transform points and associated normals and vectors
// .SECTION Description
// vtkTransformFilter is a filter to transform point coordinates, and 
// associated point normals and vectors. Other point data is passed
// through the filter.
//
// An alternative method of transformation is to use vtkActor's methods
// to scale, rotate, and translate objects. The difference between the
// two methods is that vtkActor's transformation simply effects where
// objects are rendered (via the graphics pipeline), whereas
// vtkTransformFilter actually modifies point coordinates in the 
// visualization pipeline. This is necessary for some objects 
// (e.g., vtkProbeFilter) that require point coordinates as input.

// .SECTION See Also
// vtkAbstractTransform vtkTransformPolyDataFilter vtkActor

#ifndef __vtkTransformFilter_h
#define __vtkTransformFilter_h

#include "vtkPointSetToPointSetFilter.h"

class vtkAbstractTransform;

class VTK_GRAPHICS_EXPORT vtkTransformFilter : public vtkPointSetToPointSetFilter
{
public:
  static vtkTransformFilter *New();
  vtkTypeRevisionMacro(vtkTransformFilter,vtkPointSetToPointSetFilter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Return the MTime also considering the transform.
  unsigned long GetMTime();

  // Description:
  // Specify the transform object used to transform points.
  virtual void SetTransform(vtkAbstractTransform*);
  vtkGetObjectMacro(Transform,vtkAbstractTransform);

protected:
  vtkTransformFilter();
  ~vtkTransformFilter();

  void Execute();
  vtkAbstractTransform *Transform;
private:
  vtkTransformFilter(const vtkTransformFilter&);  // Not implemented.
  void operator=(const vtkTransformFilter&);  // Not implemented.
};

#endif
