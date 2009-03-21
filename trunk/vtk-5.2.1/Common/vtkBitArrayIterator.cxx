/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkBitArrayIterator.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkBitArrayIterator.h"

#include "vtkBitArray.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkBitArrayIterator);
vtkCxxRevisionMacro(vtkBitArrayIterator, "$Revision: 1.2 $");
vtkCxxSetObjectMacro(vtkBitArrayIterator, Array, vtkBitArray);
//-----------------------------------------------------------------------------
vtkBitArrayIterator::vtkBitArrayIterator()
{
  this->Array = 0;
  this->Tuple = 0;
  this->TupleSize = 0;
}

//-----------------------------------------------------------------------------
vtkBitArrayIterator::~vtkBitArrayIterator()
{
  this->SetArray(0);
  if (this->Tuple)
    {
    delete [] this->Tuple;
    }
}

//-----------------------------------------------------------------------------
void vtkBitArrayIterator::Initialize(vtkAbstractArray* a)
{
  vtkBitArray* b = vtkBitArray::SafeDownCast(a);
  if (!b && a)
    {
    vtkErrorMacro("vtkBitArrayIterator can iterate only over vtkBitArray.");
    return;
    }
  this->SetArray(b);
}

//-----------------------------------------------------------------------------
vtkAbstractArray* vtkBitArrayIterator::GetArray()
{
  return this->Array;
}

//-----------------------------------------------------------------------------
int* vtkBitArrayIterator::GetTuple(vtkIdType id) 
{
  if (!this->Array)
    {
    return 0;
    }
  
  vtkIdType numComps = this->Array->GetNumberOfComponents();
  if (this->TupleSize < numComps)
    {
    this->TupleSize = numComps;
    delete [] this->Tuple;
    this->Tuple = new int [this->TupleSize];
    }
  int loc = id * numComps;
  for (int j = 0; j < numComps; j++)
    {
    this->Tuple[j] = this->Array->GetValue(loc + j);
    }
  return this->Tuple;
}

//-----------------------------------------------------------------------------
int vtkBitArrayIterator::GetValue(vtkIdType id)
{
  if (this->Array)
    {
    return this->Array->GetValue(id);
    }
  vtkErrorMacro("Array Iterator not initialized.");
  return 0;
}
  
//-----------------------------------------------------------------------------
void vtkBitArrayIterator::SetValue(vtkIdType id, int value)
{
  if (this->Array)
    {
    this->Array->SetValue(id, value);
    }
}

//-----------------------------------------------------------------------------
vtkIdType vtkBitArrayIterator::GetNumberOfTuples()
{
  if (this->Array)
    {
    return this->Array->GetNumberOfTuples();
    }
  return 0;
}
//-----------------------------------------------------------------------------
vtkIdType vtkBitArrayIterator::GetNumberOfValues()
{
  if (this->Array)
    {
    return this->Array->GetNumberOfTuples() * this->Array->GetNumberOfComponents();
    }
  return 0;
}
//-----------------------------------------------------------------------------
int vtkBitArrayIterator::GetNumberOfComponents()
{
  if (this->Array)
    {
    return this->Array->GetNumberOfComponents();
    }
  return 0;
}

//-----------------------------------------------------------------------------
int vtkBitArrayIterator::GetDataType()
{
  if (this->Array)
    {
    return this->Array->GetDataType();
    }
  return 0;
}
//-----------------------------------------------------------------------------
int vtkBitArrayIterator::GetDataTypeSize()
{
  if (this->Array)
    {
    return this->Array->GetDataTypeSize();
    }
  return 0;
}

//-----------------------------------------------------------------------------
void vtkBitArrayIterator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
