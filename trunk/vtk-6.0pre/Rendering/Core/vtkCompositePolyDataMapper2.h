/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCompositePolyDataMapper2.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCompositePolyDataMapper2 - mapper for composite dataset consisting
// of polygonal data.
// .SECTION Description
// vtkCompositePolyDataMapper2 is similar to vtkCompositePolyDataMapper except
// that instead of creating individual mapper for each block in the composite
// dataset, it iterates over the blocks internally.

#ifndef __vtkCompositePolyDataMapper2_h
#define __vtkCompositePolyDataMapper2_h

#include "vtkRenderingCoreModule.h" // For export macro
#include "vtkPainterPolyDataMapper.h"
#include "vtkSmartPointer.h" // for vtkSmartPointer

class vtkCompositeDataDisplayAttributes;

class VTKRENDERINGCORE_EXPORT vtkCompositePolyDataMapper2 : public vtkPainterPolyDataMapper
{
public:
  static vtkCompositePolyDataMapper2* New();
  vtkTypeMacro(vtkCompositePolyDataMapper2, vtkPainterPolyDataMapper);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Returns if the mapper does not expect to have translucent geometry. This
  // may happen when using ScalarMode is set to not map scalars i.e. render the
  // scalar array directly as colors and the scalar array has opacity i.e. alpha
  // component. Note that even if this method returns true, an actor may treat
  // the geometry as translucent since a constant translucency is set on the
  // property, for example.
  // Overridden to use the actual data and ScalarMode to determine if we have
  // opaque geometry.
  virtual bool GetIsOpaque();

  // Description:
  // Set/get the composite data set attributes.
  void SetCompositeDataDisplayAttributes(vtkCompositeDataDisplayAttributes *attributes);
  vtkCompositeDataDisplayAttributes* GetCompositeDataDisplayAttributes();

  // Description:
  // Set/get the visibility for a block given its flat index.
  void SetBlockVisibility(unsigned int index, bool visible);
  bool GetBlockVisibility(unsigned int index) const;
  void RemoveBlockVisibility(unsigned int index);
  void RemoveBlockVisibilites();

//BTX
protected:
  vtkCompositePolyDataMapper2();
  ~vtkCompositePolyDataMapper2();

  // Description:
  // We need to override this method because the standard streaming
  // demand driven pipeline is not what we want - we are expecting
  // hierarchical data as input
  vtkExecutive* CreateDefaultExecutive();

  // Description:
  // Need to define the type of data handled by this mapper.
  virtual int FillInputPortInformation(int port, vtkInformation* info);

  // Description:
  // Need to loop over the hierarchy to compute bounds
  virtual void ComputeBounds();

  // Description:
  // Time stamp for computation of bounds.
  vtkTimeStamp BoundsMTime;

  // Description:
  // Composite data set attributes.
  vtkSmartPointer<vtkCompositeDataDisplayAttributes> CompositeAttributes;

private:
  vtkCompositePolyDataMapper2(const vtkCompositePolyDataMapper2&); // Not implemented.
  void operator=(const vtkCompositePolyDataMapper2&); // Not implemented.
//ETX
};

#endif


