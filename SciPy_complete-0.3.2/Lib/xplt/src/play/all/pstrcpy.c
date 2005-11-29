/*
 * pstrcpy.c -- $Id: pstrcpy.c,v 1.1 2003/03/08 15:26:47 travo Exp $
 * strcpy that p_mallocs its destination
 *
 * Copyright (c) 1998.  See accompanying LEGAL file for details.
 */

#include "config.h"
#include "pstdlib.h"
#include <string.h>

char *
p_strcpy(const char *s)
{
  if (s) {
    char *d = p_malloc(strlen(s)+1);
    strcpy(d, s);
    return d;
  } else {
    return 0;
  }
}
