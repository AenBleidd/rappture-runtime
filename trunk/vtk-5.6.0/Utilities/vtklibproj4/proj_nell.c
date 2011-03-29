/*
** libproj -- library of cartographic projections
**
** Copyright (c) 2003, 2006   Gerald I. Evenden
*/
static const char
LIBPROJ_ID[] = "$Id: proj_nell.c,v 1.1 2008-11-07 16:41:15 jeff Exp $";
/*
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define PROJ_LIB__
#include  <lib_proj.h>
PROJ_HEAD(nell, "Nell") "\n\tPCyl., Sph.";
#define MAX_ITER  10
#define LOOP_TOL  1e-7
FORWARD(s_forward); /* spheroid */
  double k, V;
  int i;
  (void) P; /* avoid warning */

  k = 2. * sin(lp.phi);
  V = lp.phi * lp.phi;
  lp.phi *= 1.00371 + V * (-0.0935382 + V * -0.011412);
  for (i = MAX_ITER; i ; --i) {
    lp.phi -= V = (lp.phi + sin(lp.phi) - k) /
      (1. + cos(lp.phi));
    if (fabs(V) < LOOP_TOL)
      break;
  }
  xy.x = 0.5 * lp.lam * (1. + cos(lp.phi));
  xy.y = lp.phi;
  return (xy);
}
INVERSE(s_inverse); /* spheroid */
  (void) P; /* avoid warning */

  lp.lam = 2. * xy.x / (1. + cos(xy.y));
  lp.phi = proj_asin(0.5 * (xy.y + sin(xy.y)));
  return (lp);
}
FREEUP; if (P) free(P); }
ENTRY0(nell) P->es = 0; P->inv = s_inverse; P->fwd = s_forward; ENDENTRY(P)
/*
** $Log: proj_nell.c,v $
** Revision 1.1  2008-11-07 16:41:15  jeff
** ENH: Adding a 2D geoview. Adding the geographic projection library libproj4
** to Utilities. Updating the architecture of the geospatial views. All
** multi-resolution sources are now subclasses of vtkGeoSource. Each source
** has its own worker thread for fetching refined images or geometry.
** On the 3D side, vtkGeoGlobeSource is an appropriate source for vtkGeoTerrain,
** and vtkGeoAlignedImageSource is an appropriate source for
** vtkGeoAlignedImageRepresentation. On the 2D side, vtkGeoProjectionSource is an
** appropriate source for vtkGeoTerrain2D, and the image source is the same.
**
** Revision 3.1  2006/01/11 01:38:18  gie
** Initial
**
*/