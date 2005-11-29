/*
 * cygmain.c -- $Id: cygmain.c,v 1.1 2003/03/08 15:26:49 travo Exp $
 * cygwin (or uwin?) main program stub
 *
 * Copyright (c) 2000.  See accompanying LEGAL file for details.
 */

#include <windows.h>

int WINAPI
WinMain(HINSTANCE me, HINSTANCE prev, LPSTR cmd_line, int show0)
{
  extern int on_launch(int, char **);
  extern int cyg_app(int (*on_launch)(int, char **),
                     HINSTANCE me, LPSTR cmd_line, int show0);
  return cyg_app(on_launch, me, cmd_line, show0);
}
