/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkContourValues.h,v $
  Language:  C++
  Date:      $Date: 2002/12/26 18:24:21 $
  Version:   $Revision: 1.22 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkContourValues - helper object to manage setting and generating contour values
// .SECTION Description
// vtkContourValues is a general class to manage the creation, generation,
// and retrieval of contour values. This class serves as a helper class for
// contouring classes, or those classes operating on lists of contour values.

// .SECTION See Also
// vtkContourFilter

#ifndef __vtkContourValues_h
#define __vtkContourValues_h

#include "vtkObject.h"

class vtkFloatArray;

class VTK_COMMON_EXPORT vtkContourValues : public vtkObject
{
public:
  // Description:
  // Construct object with a single contour value at 0.0.
  static vtkContourValues *New();

  vtkTypeRevisionMacro(vtkContourValues,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the ith contour value.
  void SetValue(int i, float value);

  // Description:
  // Get the ith contour value. The return value will be clamped if the
  // index i is out of range.
  float GetValue(int i);

  // Description:
  // Return a pointer to a list of contour values. The contents of the
  // list will be garbage if the number of contours <= 0.
  float *GetValues();

  // Description:
  // Fill a supplied list with contour values. Make sure you've
  // allocated memory of size GetNumberOfContours().
  void GetValues(float *contourValues);

  // Description:
  // Set the number of contours to place into the list. You only really
  // need to use this method to reduce list size. The method SetValue()
  // will automatically increase list size as needed.
  void SetNumberOfContours(const int number);

  // Description:
  // Return the number of contours in the
  int GetNumberOfContours();

  // Description:
  // Generate numContours equally spaced contour values between specified
  // range. Contour values will include min/max range values.
  void GenerateValues(int numContours, float range[2]);

  // Description:
  // Generate numContours equally spaced contour values between specified
  // range. Contour values will include min/max range values.
  void GenerateValues(int numContours, float rangeStart, float rangeEnd);


protected:
  vtkContourValues();
  ~vtkContourValues();

  vtkFloatArray *Contours;

private:
  vtkContourValues(const vtkContourValues&);  // Not implemented.
  void operator=(const vtkContourValues&);  // Not implemented.
};

#endif
