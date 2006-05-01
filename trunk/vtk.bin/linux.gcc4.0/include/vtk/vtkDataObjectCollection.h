/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkDataObjectCollection.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDataObjectCollection - maintain an unordered list of data objects
// .SECTION Description
// vtkDataObjectCollection is an object that creates and manipulates lists of
// data objects. See also vtkCollection and subclasses.

#ifndef __vtkDataObjectCollection_h
#define __vtkDataObjectCollection_h

#include "vtkCollection.h"

#include "vtkDataObject.h" // Needed for inline methods

class VTK_COMMON_EXPORT vtkDataObjectCollection : public vtkCollection
{
public:
  static vtkDataObjectCollection *New();
  vtkTypeRevisionMacro(vtkDataObjectCollection,vtkCollection);

  // Description:
  // Add a data object to the list.
  void AddItem(vtkDataObject *ds) {
    this->vtkCollection::AddItem((vtkObject *)ds);};
  
  // Description:
  // Get the next data object in the list.
  vtkDataObject *GetNextItem() { 
    return static_cast<vtkDataObject *>(this->GetNextItemAsObject());};

  // Description:
  // Get the ith data object in the list.
  vtkDataObject *GetItem(int i) { 
    return static_cast<vtkDataObject *>(this->GetItemAsObject(i));};
  
protected:
  vtkDataObjectCollection() {};
  ~vtkDataObjectCollection() {};


private:
  // hide the standard AddItem from the user and the compiler.
  void AddItem(vtkObject *o) { this->vtkCollection::AddItem(o); };

private:
  vtkDataObjectCollection(const vtkDataObjectCollection&);  // Not implemented.
  void operator=(const vtkDataObjectCollection&);  // Not implemented.
};


#endif
