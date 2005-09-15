/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkVoidArray.h,v $
  Language:  C++
  Date:      $Date: 2002/11/12 18:32:04 $
  Version:   $Revision: 1.52 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkVoidArray - dynamic, self-adjusting array of void* pointers
// .SECTION Description
// vtkVoidArray is an array of pointers to void. It provides methods
// for insertion and retrieval of these pointers values, and will 
// automatically resize itself to hold new data.

#ifndef __vtkVoidArray_h
#define __vtkVoidArray_h

#include "vtkDataArray.h"

class VTK_COMMON_EXPORT vtkVoidArray : public vtkDataArray
{
public:
  static vtkVoidArray *New();

  vtkTypeRevisionMacro(vtkVoidArray,vtkDataArray);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Allocate memory for this array. Delete old storage only if necessary.
  // Note that ext is no longer used.
  int Allocate(const vtkIdType sz, const vtkIdType ext=1000);

  // Description:
  // Release storage and reset array to initial state.
  void Initialize();

  // Description:
  // Get the data type.
  int GetDataType() {return VTK_VOID;};
  
  // Description:
  // Return the size of the data type.
  int GetDataTypeSize() { return sizeof(void*); }
  
  // Description:
  // Set the number of n-tuples in the array.
  void SetNumberOfTuples(const vtkIdType number);

  // Description:
  // Get a pointer to a tuple at the ith location.
  float *GetTuple(const vtkIdType i);

  // Description:
  // Copy the tuple value into a user-provided array.
  void GetTuple(const vtkIdType i, float * tuple);
  void GetTuple(const vtkIdType i, double * tuple);

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTuple(const vtkIdType i, const float * tuple);
  void SetTuple(const vtkIdType i, const double * tuple);

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTuple(const vtkIdType i, const float * tuple);
  void InsertTuple(const vtkIdType i, const double * tuple);

  // Description:
  // Insert (memory allocation performed) the tuple onto the end of the array.
  vtkIdType InsertNextTuple(const float * tuple);
  vtkIdType InsertNextTuple(const double * tuple);

  // Description:
  // Resize object to just fit data requirement. Reclaims extra memory.
  void Squeeze() {this->ResizeAndExtend (this->MaxId+1);};

  // Description:
  // Resize the array while conserving the data.
  virtual void Resize(vtkIdType numTuples);

  // Description:
  // Get the data at a particular index.
  void* GetValue(const vtkIdType id) {return this->Array[id];};

  // Description:
  // Specify the number of values for this object to hold. Does an
  // allocation as well as setting the MaxId ivar. Used in conjunction with
  // SetValue() method for fast insertion.
  void SetNumberOfValues(const vtkIdType number);

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(const vtkIdType id, void *value);

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(const vtkIdType id, void* p);

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(void* v);

  // Description:
  // Get the address of a particular data index. Performs no checks
  // to verify that the memory has been allocated etc.
  void** GetPointer(const vtkIdType id) {return this->Array + id;}
  void *GetVoidPointer(const vtkIdType id) {return this->GetPointer(id);};

  // Description:
  // Get the address of a particular data index. Make sure data is allocated
  // for the number of items requested. Set MaxId according to the number of
  // data values requested.
  void** WritePointer(const vtkIdType id, const vtkIdType number);
  
  // Description:
  // Deep copy of another void array.
  void DeepCopy(vtkDataArray *da);
  

protected:
  vtkVoidArray();
  ~vtkVoidArray();

  void** Array;  // pointer to data
  void** ResizeAndExtend(const vtkIdType sz);  // function to resize data

  int TupleSize; //used for data conversion
  float *Tuple;
private:
  vtkVoidArray(const vtkVoidArray&);  // Not implemented.
  void operator=(const vtkVoidArray&);  // Not implemented.
};


inline void vtkVoidArray::SetNumberOfValues(const vtkIdType number) 
{
  this->Allocate(number);
  this->MaxId = number - 1;
}

inline void vtkVoidArray::SetValue(const vtkIdType id, void *value) 
{
  this->Array[id] = value;
}

inline void** vtkVoidArray::WritePointer(const vtkIdType id,
                                         const vtkIdType number) 
{
  vtkIdType newSize=id+number;
  if ( newSize > this->Size )
    {
    this->ResizeAndExtend(newSize);
    }
  if ( (--newSize) > this->MaxId )
    {
    this->MaxId = newSize;
    }
  return this->Array + id;
}

inline void vtkVoidArray::InsertValue(const vtkIdType id, void* p)
{
  if ( id >= this->Size )
    {
    this->ResizeAndExtend(id+1);
    }
  this->Array[id] = p;
  if ( id > this->MaxId )
    {
    this->MaxId = id;
    }
}

inline vtkIdType vtkVoidArray::InsertNextValue(void* p)
{
  this->InsertValue (++this->MaxId,p);
  return this->MaxId;
}


#endif
