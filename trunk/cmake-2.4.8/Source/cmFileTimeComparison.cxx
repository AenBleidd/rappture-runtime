/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile: cmFileTimeComparison.cxx,v $
  Language:  C++
  Date:      $Date: 2006/05/11 02:15:09 $
  Version:   $Revision: 1.5.2.1 $

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmFileTimeComparison.h"

// Use a hash table to avoid duplicate file time checks from disk.
#if defined(CMAKE_BUILD_WITH_CMAKE)
# include <cmsys/hash_map.hxx>
#endif

// Use a platform-specific API to get file times efficiently.
#if !defined(_WIN32) || defined(__CYGWIN__)
#  define cmFileTimeComparison_Type struct stat
#  include <ctype.h>
#  include <sys/stat.h>
#else
#  define cmFileTimeComparison_Type FILETIME
#  include <windows.h>
#endif

//----------------------------------------------------------------------------
class cmFileTimeComparisonInternal
{
public:
  // Internal comparison method.
  inline bool FileTimeCompare(const char* f1, const char* f2, int* result);

private:
#if defined(CMAKE_BUILD_WITH_CMAKE)
  // Use a hash table to efficiently map from file name to modification time.
  class HashString
    {
  public:
    size_t operator()(const cmStdString& s) const
      {
      return h(s.c_str());
      }
    cmsys::hash<const char*> h;
    };
  typedef cmsys::hash_map<cmStdString,
                          cmFileTimeComparison_Type, HashString> FileStatsMap;
  FileStatsMap Files;
#endif

  // Internal methods to lookup and compare modification times.
  inline bool Stat(const char* fname, cmFileTimeComparison_Type* st);
  inline int Compare(cmFileTimeComparison_Type* st1,
                     cmFileTimeComparison_Type* st2);
};

//----------------------------------------------------------------------------
bool cmFileTimeComparisonInternal::Stat(const char* fname,
                                        cmFileTimeComparison_Type* st)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  // Use the stored time if available.
  cmFileTimeComparisonInternal::FileStatsMap::iterator fit =
    this->Files.find(fname);
  if ( fit != this->Files.end() )
    {
    *st = fit->second;
    return true;
    }
#endif

#if !defined(_WIN32) || defined(__CYGWIN__)
  // POSIX version.  Use the stat function.
  int res = ::stat(fname, st);
  if ( res != 0 )
    {
    return false;
    }
#else
  // Windows version.  Get the modification time from extended file
  // attributes.
  WIN32_FILE_ATTRIBUTE_DATA fdata;
  if(!GetFileAttributesEx(fname, GetFileExInfoStandard, &fdata))
    {
    return false;
    }

  // Copy the file time to the output location.
  *st = fdata.ftLastWriteTime;
#endif

#if defined(CMAKE_BUILD_WITH_CMAKE)
  // Store the time for future use.
  this->Files[fname] = *st;
#endif

  return true;
}

//----------------------------------------------------------------------------
cmFileTimeComparison::cmFileTimeComparison()
{
  this->Internals = new cmFileTimeComparisonInternal;
}

//----------------------------------------------------------------------------
cmFileTimeComparison::~cmFileTimeComparison()
{
  delete this->Internals;
}

//----------------------------------------------------------------------------
bool cmFileTimeComparison::FileTimeCompare(const char* f1, 
                                           const char* f2, int* result)
{
  return this->Internals->FileTimeCompare(f1, f2, result);
}

//----------------------------------------------------------------------------
int cmFileTimeComparisonInternal::Compare(cmFileTimeComparison_Type* s1, 
                                          cmFileTimeComparison_Type* s2)
{
#if !defined(_WIN32) || defined(__CYGWIN__)
# if cmsys_STAT_HAS_ST_MTIM
  // Compare using nanosecond resolution.
  if(s1->st_mtim.tv_sec < s2->st_mtim.tv_sec)
    {
    return -1;
    }
  else if(s1->st_mtim.tv_sec > s2->st_mtim.tv_sec)
    {
    return 1;
    }
  else if(s1->st_mtim.tv_nsec < s2->st_mtim.tv_nsec)
    {
    return -1;
    }
  else if(s1->st_mtim.tv_nsec > s2->st_mtim.tv_nsec)
    {
    return 1;
    }
# else
  // Compare using 1 second resolution.
  if(s1->st_mtime < s2->st_mtime)
    {
    return -1;
    }
  else if(s1->st_mtime > s2->st_mtime)
    {
    return 1;
    }
# endif
  // Files have the same time.
  return 0;
#else
  // Compare using system-provided function.
  return (int)CompareFileTime(s1, s2);
#endif
}

//----------------------------------------------------------------------------
bool cmFileTimeComparisonInternal::FileTimeCompare(const char* f1,
                                                   const char* f2,
                                                   int* result)
{
  // Get the modification time for each file.
  cmFileTimeComparison_Type s1;
  cmFileTimeComparison_Type s2;
  if(this->Stat(f1, &s1) &&
     this->Stat(f2, &s2))
    {
    // Compare the two modification times.
    *result = this->Compare(&s1, &s2);
    return true;
    }
  else
    {
    // No comparison available.  Default to the same time.
    *result = 0;
    return false;
    }
}
