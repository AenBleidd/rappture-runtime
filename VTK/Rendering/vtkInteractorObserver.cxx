/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkInteractorObserver.cxx,v $
  Language:  C++
  Date:      $Date: 2003/01/16 19:54:30 $
  Version:   $Revision: 1.21 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkInteractorObserver.h"

#include "vtkCallbackCommand.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

vtkCxxRevisionMacro(vtkInteractorObserver, "$Revision: 1.21 $");

vtkCxxSetObjectMacro(vtkInteractorObserver,CurrentRenderer,vtkRenderer);

vtkInteractorObserver::vtkInteractorObserver()
{
  this->Enabled = 0;

  this->Interactor = NULL;

  this->EventCallbackCommand = vtkCallbackCommand::New();
  this->EventCallbackCommand->SetClientData(this); 

  //subclass has to invoke SetCallback()

  this->KeyPressCallbackCommand = vtkCallbackCommand::New();
  this->KeyPressCallbackCommand->SetClientData(this); 
  this->KeyPressCallbackCommand->SetCallback(vtkInteractorObserver::ProcessEvents);
 
  this->CurrentRenderer = NULL;

  this->Priority = 0.0;

  this->KeyPressActivation = 1;
  this->KeyPressActivationValue = 'i';
}

vtkInteractorObserver::~vtkInteractorObserver()
{
  this->EventCallbackCommand->Delete();
  this->KeyPressCallbackCommand->Delete();
}

// This adds the keypress event observer and the delete event observer
void vtkInteractorObserver::SetInteractor(vtkRenderWindowInteractor* i)
{
  if (i == this->Interactor)
    {
    return;
    }

  // if we already have an Interactor then stop observing it
  if (this->Interactor)
    {
    this->SetEnabled(0); //disable the old interactor
    this->Interactor->RemoveObserver(this->KeyPressCallbackCommand);
    }

  this->Interactor = i;

  // add observers for each of the events handled in ProcessEvents
  if (i)
    {
    i->AddObserver(vtkCommand::CharEvent, 
                   this->KeyPressCallbackCommand, 
                   this->Priority);

    i->AddObserver(vtkCommand::DeleteEvent, 
                   this->KeyPressCallbackCommand, 
                   this->Priority);
    }
  
  this->Modified();
}

void vtkInteractorObserver::ProcessEvents(vtkObject* vtkNotUsed(object), 
                                          unsigned long event,
                                          void* clientdata, 
                                          void* vtkNotUsed(calldata))
{
  vtkInteractorObserver* self 
    = reinterpret_cast<vtkInteractorObserver *>( clientdata );

  //look for char and delete events
  switch(event)
    {
    case vtkCommand::CharEvent:
      self->OnChar();
      break;
    case vtkCommand::DeleteEvent:
      //self->Interactor = NULL; //commented out, can't write to a 
      //self->Enabled = 0;       //deleted object
      break;
    }
}

//----------------------------------------------------------------------------
void vtkInteractorObserver::StartInteraction() 
{
  this->Interactor->GetRenderWindow()->SetDesiredUpdateRate(this->Interactor->GetDesiredUpdateRate());
}

//----------------------------------------------------------------------------
void vtkInteractorObserver::EndInteraction() 
{
  this->Interactor->GetRenderWindow()->SetDesiredUpdateRate(this->Interactor->GetStillUpdateRate());
}

//----------------------------------------------------------------------------
// Description:
// Transform from display to world coordinates.
// WorldPt has to be allocated as 4 vector
void vtkInteractorObserver::ComputeDisplayToWorld(double x, 
                                                  double y,
                                                  double z, 
                                                  double worldPt[4])
{
  if ( !this->CurrentRenderer ) 
    {
    return;
    }
  
  this->CurrentRenderer->SetDisplayPoint(x, y, z);
  this->CurrentRenderer->DisplayToWorld();
  this->CurrentRenderer->GetWorldPoint(worldPt);
  if (worldPt[3])
    {
    worldPt[0] /= worldPt[3];
    worldPt[1] /= worldPt[3];
    worldPt[2] /= worldPt[3];
    worldPt[3] = 1.0;
    }
}

void vtkInteractorObserver::ComputeDisplayToWorld(double x, 
                                                  double y,
                                                  double z, 
                                                  float worldPt[4])
{
  if ( !this->CurrentRenderer ) 
    {
    return;
    }
  
  this->CurrentRenderer->SetDisplayPoint(x, y, z);
  this->CurrentRenderer->DisplayToWorld();
  this->CurrentRenderer->GetWorldPoint(worldPt);
  if (worldPt[3])
    {
    worldPt[0] /= worldPt[3];
    worldPt[1] /= worldPt[3];
    worldPt[2] /= worldPt[3];
    worldPt[3] = 1.0;
    }
}

// Description:
// Transform from world to display coordinates.
// displayPt has to be allocated as 3 vector
void vtkInteractorObserver::ComputeWorldToDisplay(double x, 
                                                  double y,
                                                  double z, 
                                                  double displayPt[3])
{
  if ( !this->CurrentRenderer ) 
    {
    return;
    }
  
  this->CurrentRenderer->SetWorldPoint(x, y, z, 1.0);
  this->CurrentRenderer->WorldToDisplay();
  this->CurrentRenderer->GetDisplayPoint(displayPt);
}

// Description:
// transform from world to display coordinates.
// displayPt has to be allocated as 3 vector
void vtkInteractorObserver::ComputeWorldToDisplay(double x, 
                                                  double y,
                                                  double z, 
                                                  float displayPt[3])
{
  if ( !this->CurrentRenderer ) 
    {
    return;
    }
  
  this->CurrentRenderer->SetWorldPoint(x, y, z, 1.0);
  this->CurrentRenderer->WorldToDisplay();
  this->CurrentRenderer->GetDisplayPoint(displayPt);
}

void vtkInteractorObserver::OnChar()
{
  // catch additional keycodes otherwise
  if ( this->KeyPressActivation )
    {
    if (this->Interactor->GetKeyCode() == this->KeyPressActivationValue )
      {
      if ( !this->Enabled )
        {
        this->On();
        }
      else
        {
        this->Off();
        }
      this->KeyPressCallbackCommand->SetAbortFlag(1);
      }
    }//if activation enabled
}

void vtkInteractorObserver::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  
  os << indent << "Current Renderer: " << this->CurrentRenderer << "\n";
  os << indent << "Enabled: " << this->Enabled << "\n";
  os << indent << "Priority: " << this->Priority << "\n";
  os << indent << "Interactor: " << this->Interactor << "\n";
  os << indent << "Key Press Activation: " 
     << (this->KeyPressActivation ? "On" : "Off") << "\n";
  os << indent << "Key Press Activation Value: " 
     << this->KeyPressActivationValue << "\n";
}


