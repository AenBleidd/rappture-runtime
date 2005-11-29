/*
 * pfill.c -- $Id: pfill.c,v 1.1 2003/03/08 15:26:49 travo Exp $
 * p_fill for MS Windows
 *
 * Copyright (c) 1999.  See accompanying LEGAL file for details.
 */

#include "playw.h"

/* ARGSUSED */
void
p_fill(p_win *w, int convexity)
{
  int n = w_pt_count;
  HDC dc = w_getdc(w, 12);
  if (dc) {
    /* SetPolyFillMode(dc, ALTERNATE); */
    Polygon(dc, w_pt_list, n);
  }
}
