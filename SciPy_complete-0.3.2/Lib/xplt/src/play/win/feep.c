/*
 * feep.c -- $Id: feep.c,v 1.1 2003/03/08 15:26:49 travo Exp $
 * p_feep for MS Windows
 *
 * Copyright (c) 1999.  See accompanying LEGAL file for details.
 */

#include "playw.h"

/* ARGSUSED */
void
p_feep(p_win *w)
{
  MessageBeep(MB_OK);
}
