/*
 * mfcmain.cpp -- $Id: mfcmain.cpp,v 1.1 2003/03/08 15:26:49 travo Exp $
 * MFC main program stub
 *
 * Copyright (c) 2000.  See accompanying LEGAL file for details.
 */

extern "C" {
  extern int on_launch(int argc, char *argv[]);
}
#include "mfcapp.h"

mfc_boss the_boss(on_launch);
