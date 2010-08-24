/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestGenericVertexAttributesGLSLAlphaBlending.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME Test of vtkGLSLShaderDeviceAdapter2 with XML shader style 2 and
// alpha blending.
// .SECTION Description
// this program tests the shader support in vtkRendering.


#include "vtkActor.h"
#include "vtkBrownianPoints.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"

#include "vtkgl.h"

// Make sure to have a valid OpenGL context current on the calling thread
// before calling it.
bool MesaHasVTKBug8135()
{
  // GL_VENDOR cannot be used because it can be "Brian Paul" or "Mesa project"
  // GL_RENDERER cannot be used because it can be "Software Rasterizer" or
  // "Mesa X11"
  // GL_VERSION is more robust. It has things like "2.0 Mesa 7.0.4" or
  // "2.1 Mesa 7.2" or "2.1 Mesa 7.3-devel"
  
  bool result=false;
  const char *gl_version=
    reinterpret_cast<const char *>(glGetString(GL_VERSION));
  const char *mesa_version=strstr(gl_version,"Mesa");
  
  if(mesa_version!=0)
    {
    int mesa_major=0;
    int mesa_minor=0;
    if(sscanf(mesa_version,"Mesa %d.%d",&mesa_major, &mesa_minor)>=2)
      {
      result=mesa_major<7 || (mesa_major==7 && mesa_minor<3);
      }
    }
  return result;
}

int TestGenericVertexAttributesGLSLAlphaBlending(int argc, char *argv[])
{
  char shaders1[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \
  <Material name=\"GenericAttributes1\"> \
    <Shader scope=\"Vertex\" name=\"VertexShader\" location=\"Inline\"\
      language=\"GLSL\" entry=\"main\" style=\"2\"> attribute vec3 genAttrVector; \
      varying vec4 color; \
      void propFuncVS(void) \
      { \
        gl_Position = gl_ModelViewProjectionMatrix *gl_Vertex; \
        color = vec4(normalize(genAttrVector), 0.3); \
      } \
    </Shader> \
    <Shader scope=\"Fragment\" name=\"FragmentShader\" location=\"Inline\" \
      language=\"GLSL\" entry=\"main\" style=\"2\"> \
      varying vec4 color; \
      void propFuncFS() \
      { \
        gl_FragColor = color; \
      } \
    </Shader> \
  </Material>";
  
  vtkSphereSource * sphere = vtkSphereSource::New();
  sphere->SetRadius(5);
  sphere->SetPhiResolution(20);
  sphere->SetThetaResolution(20);

  vtkBrownianPoints * randomVector = vtkBrownianPoints::New();
  randomVector->SetMinimumSpeed(0);
  randomVector->SetMaximumSpeed(1);
  randomVector->SetInputConnection(sphere->GetOutputPort());

  vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(randomVector->GetOutputPort());

  vtkActor *actor = vtkActor::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->LoadMaterialFromString(shaders1);
  actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
  actor->GetProperty()->GetShading();
  actor->GetProperty()->ShadingOn();
  actor->GetProperty()->SetOpacity(0.99); // to force alpha blending.
  mapper->MapDataArrayToVertexAttribute("genAttrVector", "BrownianVectors", 0, -1);

  vtkRenderer *renderer = vtkRenderer::New();
  renderer->SetBackground(0.5, 0.5, 0.5);

  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
  interactor->SetRenderWindow(renWin);

  renWin->SetSize(400,400);
  renWin->Render();
  
  int retVal;
  if(MesaHasVTKBug8135())
    {
    // Mesa will crash if version<7.3
    cout<<"This version of Mesa would crash. Skip the test."<<endl;
    retVal=vtkRegressionTester::PASSED;
    }
  else
    {
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renWin->Render();
  
    interactor->Initialize();
    renWin->Render();

    retVal = vtkRegressionTestImageThreshold(renWin,18);
    if( retVal == vtkRegressionTester::DO_INTERACTOR)
      {
      interactor->Start();
      }
    }

  sphere->Delete();
  randomVector->Delete();
  mapper->Delete();
  actor->Delete();
  renderer->Delete();
  renWin->Delete();
  interactor->Delete();

  return !retVal;
}
