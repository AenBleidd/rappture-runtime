/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkToolkits.h.in,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkToolkits_h
#define __vtkToolkits_h

/* This header is configured by VTK's build process.  */

/*--------------------------------------------------------------------------*/
/* Selected VTK Toolkits                                                    */

#define VTK_USE_HYBRID
#define VTK_USE_PARALLEL
/* #undef VTK_USE_PATENTED */
#define VTK_USE_RENDERING
/* #undef VTK_USE_VOLUMEPRO */
/* #undef VTK_HAVE_VG500 */
/* #undef VTK_HAVE_VP1000 */
/* #undef VTK_USE_GL2PS */

/*--------------------------------------------------------------------------*/
/* Rendering Configuration                                                  */

#define VTK_USE_X
/* #undef VTK_USE_MANGLED_MESA */
#define VTK_USE_OPENGL_LIBRARY
/* #undef VTK_OPENGL_HAS_OSMESA */

/*--------------------------------------------------------------------------*/
/* Other Configuration Options                                              */

/* Whether we are building MPI support.  */
/* #undef VTK_USE_MPI */

/* Whether Tk widgets are NOT initialized when vtkRendering loads.  */
/* #undef VTK_DISABLE_TK_INIT */

/* Whether we are linking to Tcl/Tk statically.  */
/* #undef VTK_TCL_TK_STATIC */

/* Debug leaks support.  */
/* #undef VTK_DEBUG_LEAKS */

/*--------------------------------------------------------------------------*/
/* Setup VTK based on platform features and configuration.                  */

/* OGLR */
#if ((defined(VTK_USE_OPENGL_LIBRARY) && !defined(_WIN32)) || \
     (defined(VTK_USE_X) && defined(_WIN32)) || \
     (defined(VTK_USE_MANGLED_MESA) && !defined(_WIN32))) && \
     !(defined (VTK_USE_CARBON) || defined(VTK_USE_COCOA))
# define VTK_USE_OGLR
#endif

/* Configure internal Tk headers.  */
#ifdef VTK_USE_CARBON
# define USE_NON_CONST
# define MAC_OSX_TK
#endif

#endif
