/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkmyEx1.cxx,v $
  Language:  C++
  Date:      $Date: 2002/01/22 15:27:29 $
  Version:   $Revision: 1.5 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example creates a couple of class instances and print them to
// the standard output. No rendering window is created.
//

//
// First include the required header files for the vtk classes we are using
//
#include "vtkBar.h"
#include "vtkBar2.h"
#include "vtkImageFoo.h"

int main( int argc, char *argv[] )
{

  //
  // Next we create an instance of vtkBar
  //
  cout << "Create vtkBar object and print it." << endl;

  vtkBar *bar = vtkBar::New();
  bar->Print(cout);
  
  //
  // Then we create an instance of vtkBar2
  //
  cout << "Create vtkBar2 object and print it." << endl;
  
  vtkBar2 *bar2 = vtkBar2::New();
  bar2->Print(cout);
  
  //
  // And we create an instance of vtkImageFoo
  //
  cout << "Create vtkImageFoo object and print it." << endl;
  
  vtkImageFoo *imagefoo = vtkImageFoo::New();
  imagefoo->Print(cout);
  
  cout << "Looks good ?" << endl;

  //
  // Free up any objects we created
  //
  bar->Delete();
  bar2->Delete();
  imagefoo->Delete();

  return 0;
}
