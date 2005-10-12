/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkStructuredPointsReader.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkStructuredPointsReader.h"

#include "vtkDataArray.h"
#include "vtkErrorCode.h"
#include "vtkFieldData.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkStructuredPoints.h"

vtkCxxRevisionMacro(vtkStructuredPointsReader, "$Revision: 1.56 $");
vtkStandardNewMacro(vtkStructuredPointsReader);

vtkStructuredPointsReader::vtkStructuredPointsReader()
{
  this->SetOutput(vtkStructuredPoints::New());
  // Releasing data for pipeline parallism.
  // Filters will know it is empty. 
  this->Outputs[0]->ReleaseData();
  this->Outputs[0]->Delete();
}

vtkStructuredPointsReader::~vtkStructuredPointsReader()
{
}

//----------------------------------------------------------------------------
void vtkStructuredPointsReader::SetOutput(vtkStructuredPoints *output)
{
  this->vtkSource::SetNthOutput(0, output);
}

//----------------------------------------------------------------------------
vtkStructuredPoints *vtkStructuredPointsReader::GetOutput()
{
  if (this->NumberOfOutputs < 1)
    {
    return NULL;
    }
  
  return (vtkStructuredPoints *)(this->Outputs[0]);
}


//----------------------------------------------------------------------------
// Default method performs Update to get information.  Not all the old
// structured points sources compute information
void vtkStructuredPointsReader::ExecuteInformation()
{
  this->SetErrorCode( vtkErrorCode::NoError );
  vtkStructuredPoints *output = this->GetOutput();
  vtkDataArray *scalars;
  int saveRequestFlag;
  
  // Now here is a problem.
  // Update Extent needs to be set incase the RequestExactExtent flag is on.
  // Bypass to superclasses update.  
  // Well that solution no longer works because the superclass now handles
  // the RequestForExactExtent flag.  Lets try disabling the flag temporarily.
  saveRequestFlag = output->GetRequestExactExtent();
  output->SetRequestExactExtent(0);
  output->vtkDataObject::UpdateData();
  output->SetRequestExactExtent(saveRequestFlag);
  
  scalars = output->GetPointData()->GetScalars();
  if (scalars)
    {
    output->SetScalarType(scalars->GetDataType());
    output->SetNumberOfScalarComponents(scalars->GetNumberOfComponents());
    }

  output->SetWholeExtent(output->GetExtent());
}

void vtkStructuredPointsReader::Execute()
{
  this->SetErrorCode( vtkErrorCode::NoError );
  int numPts=0, numCells=0;
  char line[256];
  int npts, ncells;
  int dimsRead=0, arRead=0, originRead=0;
  int done=0;
  vtkStructuredPoints *output = this->GetOutput();
  
  // ImageSource superclass does not do this.
  output->ReleaseData();

  vtkDebugMacro(<<"Reading vtk structured points file...");

  if (!this->OpenVTKFile() || !this->ReadHeader())
    {
      return;
    }

  // Read structured points specific stuff
  //
  if (!this->ReadString(line))
    {
    vtkErrorMacro(<<"Data file ends prematurely!");
    this->CloseVTKFile ();
    this->SetErrorCode( vtkErrorCode::PrematureEndOfFileError );
    return;
    }

  if ( !strncmp(this->LowerCase(line),"dataset",(unsigned long)7) )
    {
    // Make sure we're reading right type of geometry
    //
    if (!this->ReadString(line))
      {
      vtkErrorMacro(<<"Data file ends prematurely!");
      this->CloseVTKFile ();
      this->SetErrorCode( vtkErrorCode::PrematureEndOfFileError );
      return;
      } 

    if ( strncmp(this->LowerCase(line),"structured_points",17) )
      {
      vtkErrorMacro(<< "Cannot read dataset type: " << line);
      this->CloseVTKFile ();
      this->SetErrorCode( vtkErrorCode::UnrecognizedFileTypeError );
      return;
      }

    // Read keyword and number of points
    //
    numPts = output->GetNumberOfPoints(); // get default
    while (!done)
      {
      if (!this->ReadString(line))
        {
        break;
        }

      if (! strncmp(this->LowerCase(line), "field", 5))
        {
        vtkFieldData* fd = this->ReadFieldData();
        output->SetFieldData(fd);
        fd->Delete(); // ?
        }
      else if ( ! strncmp(line, "dimensions",10) )
        {
        int dim[3];
        if (!(this->Read(dim) && 
              this->Read(dim+1) && 
              this->Read(dim+2)))
          {
          vtkErrorMacro(<<"Error reading dimensions!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }

        numPts = dim[0] * dim[1] * dim[2];
        output->SetDimensions(dim);
        numCells = output->GetNumberOfCells();
        dimsRead = 1;
        }

      else if ( !strncmp(line,"aspect_ratio",12) || !strncmp(line,"spacing",7) )
        {
        double ar[3];
        if (!(this->Read(ar) && 
              this->Read(ar+1) && 
              this->Read(ar+2)))
          {
          vtkErrorMacro(<<"Error reading spacing!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }

        output->SetSpacing(ar);
        arRead = 1;
        }

      else if ( ! strncmp(line,"origin",6) )
        {
        double origin[3];
        if (!(this->Read(origin) && 
              this->Read(origin+1) && 
              this->Read(origin+2)))
          {
          vtkErrorMacro(<<"Error reading origin!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }

        output->SetOrigin(origin);
        originRead = 1;
        }

      else if ( ! strncmp(line, "cell_data", 9) )
        {
        if (!this->Read(&ncells))
          {
          vtkErrorMacro(<<"Cannot read cell data!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }
        
        if ( ncells != numCells )
          {
          vtkErrorMacro(<<"Number of cells don't match data values!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }

        this->ReadCellData(output, ncells);
        break; //out of this loop
        }

      else if ( ! strncmp(line, "point_data", 10) )
        {
        if (!this->Read(&npts))
          {
          vtkErrorMacro(<<"Cannot read point data!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }
        
        if ( npts != numPts )
          {
          vtkErrorMacro(<<"Number of points don't match data values!");
          this->CloseVTKFile ();
          this->SetErrorCode( vtkErrorCode::FileFormatError );
          return;
          }

        this->ReadPointData(output, npts);
        break; //out of this loop
        }

      else
        {
        vtkErrorMacro(<< "Unrecognized keyword: " << line);
        this->CloseVTKFile ();
        this->SetErrorCode( vtkErrorCode::FileFormatError );
        return;
        }
      }

      if ( !dimsRead ) vtkWarningMacro(<<"No dimensions read.");
      if ( !arRead ) vtkWarningMacro(<<"No spacing read.");
      if ( !originRead ) vtkWarningMacro(<<"No origin read.");
    }

  else if ( !strncmp(line,"cell_data",9) )
    {
    vtkWarningMacro(<<"No geometry defined in data file!");
    if (!this->Read(&ncells))
      {
      vtkErrorMacro(<<"Cannot read cell data!");
      this->CloseVTKFile ();
      this->SetErrorCode( vtkErrorCode::FileFormatError );
      return;
      }
    this->ReadCellData(output, numCells);
    }

  else if ( !strncmp(line,"point_data",10) )
    {
    vtkWarningMacro(<<"No geometry defined in data file!");
    if (!this->Read(&npts))
      {
      vtkErrorMacro(<<"Cannot read point data!");
      this->CloseVTKFile ();
      this->SetErrorCode( vtkErrorCode::FileFormatError );
      return;
      }
    this->ReadPointData(output, numPts);
    }

  else 
    {
    vtkErrorMacro(<< "Unrecognized keyword: " << line);
    }
  this->CloseVTKFile ();
}

void vtkStructuredPointsReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
