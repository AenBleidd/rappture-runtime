/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkSignedCharArray.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSignedCharArray - dynamic, self-adjusting array of signed char
// .SECTION Description
// vtkSignedCharArray is an array of values of type signed char.
// It provides methods for insertion and retrieval of values and will
// automatically resize itself to hold new data.

#ifndef __vtkSignedCharArray_h
#define __vtkSignedCharArray_h

// Tell the template header how to give our superclass a DLL interface.
#if !defined(__vtkSignedCharArray_cxx)
# define VTK_DATA_ARRAY_TEMPLATE_TYPE signed char
#endif

#include "vtkDataArray.h"
#include "vtkDataArrayTemplate.h" // Real Superclass

// Fake the superclass for the wrappers.
#define vtkDataArray vtkDataArrayTemplate<signed char>
class VTK_COMMON_EXPORT vtkSignedCharArray : public vtkDataArray
#undef vtkDataArray
{
public:
  static vtkSignedCharArray* New();
  vtkTypeRevisionMacro(vtkSignedCharArray,vtkDataArray);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the data type.
  int GetDataType()
    { return VTK_SIGNED_CHAR; }

  // Description:
  // Copy the tuple value into a user-provided array.
  void GetTupleValue(vtkIdType i, signed char* tuple)
    { this->RealSuperclass::GetTupleValue(i, tuple); }

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTupleValue(vtkIdType i, const signed char* tuple)
    { this->RealSuperclass::SetTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTupleValue(vtkIdType i, const signed char* tuple)
    { this->RealSuperclass::InsertTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple onto the end of the array.
  vtkIdType InsertNextTupleValue(const signed char* tuple)
    { return this->RealSuperclass::InsertNextTupleValue(tuple); }

  // Description:
  // Get the data at a particular index.
  signed char GetValue(vtkIdType id)
    { return this->RealSuperclass::GetValue(id); }

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(vtkIdType id, signed char value)
    { this->RealSuperclass::SetValue(id, value); }

  // Description:
  // Specify the number of values for this object to hold. Does an
  // allocation as well as setting the MaxId ivar. Used in conjunction with
  // SetValue() method for fast insertion.
  void SetNumberOfValues(vtkIdType number)
    { this->RealSuperclass::SetNumberOfValues(number); }

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(vtkIdType id, signed char f)
    { this->RealSuperclass::InsertValue(id, f); }

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(signed char f)
    { return this->RealSuperclass::InsertNextValue(f); }

  // Description:
  // Get the address of a particular data index. Make sure data is allocated
  // for the number of items requested. Set MaxId according to the number of
  // data values requested.
  signed char* WritePointer(vtkIdType id, vtkIdType number)
    { return this->RealSuperclass::WritePointer(id, number); }

  // Description:
  // Get the address of a particular data index. Performs no checks
  // to verify that the memory has been allocated etc.
  signed char* GetPointer(vtkIdType id)
    { return this->RealSuperclass::GetPointer(id); }

  // Description:
  // This method lets the user specify data to be held by the array.  The
  // array argument is a pointer to the data.  size is the size of
  // the array supplied by the user.  Set save to 1 to keep the class
  // from deleting the array when it cleans up or reallocates memory.
  // The class uses the actual array provided; it does not copy the data
  // from the suppled array. 
  void SetArray(signed char* array, vtkIdType size, int save)
    { this->RealSuperclass::SetArray(array, size, save); }
  void SetArray(signed char* array, vtkIdType size, int save, int deleteMethod)
    { this->RealSuperclass::SetArray(array, size, save, deleteMethod); }

protected:
  vtkSignedCharArray(vtkIdType numComp=1);
  ~vtkSignedCharArray();

private:
  //BTX
  typedef vtkDataArrayTemplate<signed char> RealSuperclass;
  //ETX
  vtkSignedCharArray(const vtkSignedCharArray&);  // Not implemented.
  void operator=(const vtkSignedCharArray&);  // Not implemented.
};

#endif
