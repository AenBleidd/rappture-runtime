/*
 * feep.c -- $Id: feep.c,v 1.1 2003/03/08 15:26:51 travo Exp $
 * p_feep for X11
 *
 * Copyright (c) 1998.  See accompanying LEGAL file for details.
 */

#include "config.h"
#include "playx.h"

void
p_feep(p_win *w)
{
  if (w->s->xdpy->dpy) XBell(w->s->xdpy->dpy, 100);
}
