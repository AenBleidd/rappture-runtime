/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkConfigure.h.in,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkConfigure_h
#define __vtkConfigure_h

/* This header is configured by VTK's build process.  */

/*--------------------------------------------------------------------------*/
/* Platform Features                                                        */

/* Byte order.  */
#define VTK_WORDS_BIGENDIAN

/* Threading system.  */
#define VTK_USE_PTHREADS
/* #undef VTK_USE_SPROC */
/* #undef VTK_HP_PTHREADS */
/* #undef VTK_USE_WIN32_THREADS */

/* Size of fundamental data types.  */
#define VTK_SIZEOF_CHAR   1
#define VTK_SIZEOF_DOUBLE 8
#define VTK_SIZEOF_FLOAT  4
#define VTK_SIZEOF_INT    4
#define VTK_SIZEOF_LONG   4
#define VTK_SIZEOF_SHORT  2

/* Define size of "long long" only if the type exists.  */
#define VTK_SIZEOF_LONG_LONG 8

/* Whether type "char" is signed (it may be signed or unsigned).  */
#define VTK_TYPE_CHAR_IS_SIGNED 1

/* Compiler features.  */
/* #undef VTK_NO_EXPLICIT_TEMPLATE_INSTANTIATION */
/* #undef VTK_NO_ANSI_STRING_STREAM */
/* #undef VTK_NO_STD_NAMESPACE */
#define VTK_COMPILER_HAS_BOOL
#define VTK_STREAM_EOF_SEVERITY 0

/*--------------------------------------------------------------------------*/
/* VTK Platform Configuration                                               */

/* Whether we are building shared libraries.  */
#define VTK_BUILD_SHARED_LIBS

/* Whether vtkIdType is a 64-bit integer type (or a 32-bit integer type).  */
/* #undef VTK_USE_64BIT_IDS */

/* Whether we are using ANSI C++ streams (or old-style streams).  */
#define VTK_USE_ANSI_STDLIB

/* Whether VTK was built to support Carbon or Cocoa on the Mac.  */
/* #undef VTK_USE_CARBON */
/* #undef VTK_USE_COCOA */

/*--------------------------------------------------------------------------*/
/* VTK Versioning                                                           */

/* Version number.  */
#define VTK_MAJOR_VERSION 4
#define VTK_MINOR_VERSION 4
#define VTK_BUILD_VERSION 2
#define VTK_VERSION "4.4.2"

/* C++ compiler used.  */
#define VTK_CXX_COMPILER "c++"

/*--------------------------------------------------------------------------*/
/* Setup VTK based on platform features and configuration.                  */

/* Setup vtkstd, a portable namespace for std.  */
#ifndef VTK_NO_STD_NAMESPACE
# define vtkstd std
#else
# define vtkstd
#endif

/* Define a "vtkstd_bool" type.  This should be used as the
   return type of comparison operators to keep STL happy on all
   platforms.  It should not be used elsewhere.  */
#ifdef VTK_COMPILER_HAS_BOOL
typedef bool vtkstd_bool;
#else
typedef int vtkstd_bool;
#endif

#endif
