/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkIVWriter.h,v $
  Language:  C++
  Date:      $Date: 2002/08/13 17:14:28 $
  Version:   $Revision: 1.21 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkIVWriter - export polydata into OpenInventor 2.0 format.
// .SECTION Description
// vtkIVWriter is a concrete subclass of vtkWriter that writes OpenInventor 2.0
// files.
//
// .SECTION See Also
// vtkPolyDataWriter


#ifndef __vtkIVWriter_h
#define __vtkIVWriter_h

#include "vtkPolyDataWriter.h"

class VTK_IO_EXPORT vtkIVWriter : public vtkPolyDataWriter
{
public:
  static vtkIVWriter *New();
  vtkTypeRevisionMacro(vtkIVWriter,vtkPolyDataWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkIVWriter() {};
  ~vtkIVWriter() {};

  void WriteData();
  void WritePolyData(vtkPolyData *polyData, FILE *fp);
private:
  vtkIVWriter(const vtkIVWriter&);  // Not implemented.
  void operator=(const vtkIVWriter&);  // Not implemented.
};

#endif

