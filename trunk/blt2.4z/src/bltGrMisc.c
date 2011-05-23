
/*
 * bltGrMisc.c --
 *
 *	This module implements miscellaneous routines for the BLT
 *	graph widget.
 *
 * Copyright 1993-1998 Lucent Technologies, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and warranty
 * disclaimer appear in supporting documentation, and that the names
 * of Lucent Technologies any of their entities not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * Lucent Technologies disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability and
 * fitness.  In no event shall Lucent Technologies be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether in
 * an action of contract, negligence or other tortuous action, arising
 * out of or in connection with the use or performance of this
 * software.  
 */

#include "bltGraph.h"
#include <X11/Xutil.h>

#if defined(__STDC__)
#include <stdarg.h>
#else
#include <varargs.h>
#endif


static Tk_OptionParseProc StringToPoint;
static Tk_OptionPrintProc PointToString;
static Tk_OptionParseProc StringToColorPair;
static Tk_OptionPrintProc ColorPairToString;
Tk_CustomOption bltPointOption =
{
    StringToPoint, PointToString, (ClientData)0
};
Tk_CustomOption bltColorPairOption =
{
    StringToColorPair, ColorPairToString, (ClientData)0
};

/* ----------------------------------------------------------------------
 * Custom option parse and print procedures
 * ----------------------------------------------------------------------
 */

/*
 *----------------------------------------------------------------------
 *
 * Blt_GetXY --
 *
 *	Converts a string in the form "@x,y" into an XPoint structure
 *	of the x and y coordinates.
 *
 * Results:
 *	A standard Tcl result. If the string represents a valid position
 *	*pointPtr* will contain the converted x and y coordinates and
 *	TCL_OK is returned.  Otherwise,	TCL_ERROR is returned and
 *	interp->result will contain an error message.
 *
 *----------------------------------------------------------------------
 */
int
Blt_GetXY(interp, tkwin, string, xPtr, yPtr)
    Tcl_Interp *interp;
    Tk_Window tkwin;
    char *string;
    int *xPtr, *yPtr;
{
    char *comma;
    int result;
    int x, y;

    if ((string == NULL) || (*string == '\0')) {
	*xPtr = *yPtr = -SHRT_MAX;
	return TCL_OK;
    }
    if (*string != '@') {
	goto badFormat;
    }
    comma = strchr(string + 1, ',');
    if (comma == NULL) {
	goto badFormat;
    }
    *comma = '\0';
    result = ((Tk_GetPixels(interp, tkwin, string + 1, &x) == TCL_OK) &&
	(Tk_GetPixels(interp, tkwin, comma + 1, &y) == TCL_OK));
    *comma = ',';
    if (!result) {
	Tcl_AppendResult(interp, ": can't parse position \"", string, "\"",
	    (char *)NULL);
	return TCL_ERROR;
    }
    *xPtr = x, *yPtr = y;
    return TCL_OK;

  badFormat:
    Tcl_AppendResult(interp, "bad position \"", string, 
	     "\": should be \"@x,y\"", (char *)NULL);
    return TCL_ERROR;
}

/*
 *----------------------------------------------------------------------
 *
 * StringToPoint --
 *
 *	Convert the string representation of a legend XY position into
 *	window coordinates.  The form of the string must be "@x,y" or
 *	none.
 *
 * Results:
 *	A standard Tcl result.  The symbol type is written into the
 *	widget record.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
StringToPoint(clientData, interp, tkwin, string, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Interpreter to send results back to */
    Tk_Window tkwin;		/* Not used. */
    char *string;		/* New legend position string */
    char *widgRec;		/* Widget record */
    int offset;			/* offset to XPoint structure */
{
    XPoint *pointPtr = (XPoint *)(widgRec + offset);
    int x, y;

    if (Blt_GetXY(interp, tkwin, string, &x, &y) != TCL_OK) {
	return TCL_ERROR;
    }
    pointPtr->x = x, pointPtr->y = y;
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * PointToString --
 *
 *	Convert the window coordinates into a string.
 *
 * Results:
 *	The string representing the coordinate position is returned.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static char *
PointToString(clientData, tkwin, widgRec, offset, freeProcPtr)
    ClientData clientData;	/* Not used. */
    Tk_Window tkwin;		/* Not used. */
    char *widgRec;		/* Widget record */
    int offset;			/* offset of XPoint in record */
    Tcl_FreeProc **freeProcPtr;	/* Memory deallocation scheme to use */
{
    char *result;
    XPoint *pointPtr = (XPoint *)(widgRec + offset);

    result = "";
    if ((pointPtr->x != -SHRT_MAX) && (pointPtr->y != -SHRT_MAX)) {
	char string[200];

	sprintf(string, "@%d,%d", pointPtr->x, pointPtr->y);
	result = Blt_Strdup(string);
	assert(result);
	*freeProcPtr = (Tcl_FreeProc *)Blt_Free;
    }
    return result;
}

/*LINTLIBRARY*/
static int
GetColorPair(interp, tkwin, fgStr, bgStr, pairPtr, allowDefault)
    Tcl_Interp *interp;
    Tk_Window tkwin;
    char *fgStr, *bgStr;
    ColorPair *pairPtr;
    int allowDefault;
{
    unsigned int length;
    XColor *fgColor, *bgColor;

    length = strlen(fgStr);
    if (fgStr[0] == '\0') {
	fgColor = NULL;
    } else if ((allowDefault) && (fgStr[0] == 'd') &&
	(strncmp(fgStr, "defcolor", length) == 0)) {
	fgColor = COLOR_DEFAULT;
    } else {
	fgColor = Tk_GetColor(interp, tkwin, Tk_GetUid(fgStr));
	if (fgColor == NULL) {
	    return TCL_ERROR;
	}
    }
    length = strlen(bgStr);
    if (bgStr[0] == '\0') {
	bgColor = NULL;
    } else if ((allowDefault) && (bgStr[0] == 'd') &&
	(strncmp(bgStr, "defcolor", length) == 0)) {
	bgColor = COLOR_DEFAULT;
    } else {
	bgColor = Tk_GetColor(interp, tkwin, Tk_GetUid(bgStr));
	if (bgColor == NULL) {
	    return TCL_ERROR;
	}
    }
    pairPtr->fgColor = fgColor;
    pairPtr->bgColor = bgColor;
    return TCL_OK;
}

void
Blt_FreeColorPair(pairPtr)
    ColorPair *pairPtr;
{
    if ((pairPtr->bgColor != NULL) && (pairPtr->bgColor != COLOR_DEFAULT)) {
	Tk_FreeColor(pairPtr->bgColor);
    }
    if ((pairPtr->fgColor != NULL) && (pairPtr->fgColor != COLOR_DEFAULT)) {
	Tk_FreeColor(pairPtr->fgColor);
    }
    pairPtr->bgColor = pairPtr->fgColor = NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * StringToColorPair --
 *
 *	Convert the color names into pair of XColor pointers.
 *
 * Results:
 *	A standard Tcl result.  The color pointer is written into the
 *	widget record.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
StringToColorPair(clientData, interp, tkwin, string, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Interpreter to send results back to */
    Tk_Window tkwin;		/* Not used. */
    char *string;		/* String representing color */
    char *widgRec;		/* Widget record */
    int offset;			/* Offset of color field in record */
{
    ColorPair *pairPtr = (ColorPair *)(widgRec + offset);
    ColorPair sample;
    int allowDefault = (int)clientData;

    sample.fgColor = sample.bgColor = NULL;
    if ((string != NULL) && (*string != '\0')) {
	int nColors;
	char **colors;
	int result;

	if (Tcl_SplitList(interp, string, &nColors, &colors) != TCL_OK) {
	    return TCL_ERROR;
	}
	switch (nColors) {
	case 0:
	    result = TCL_OK;
	    break;
	case 1:
	    result = GetColorPair(interp, tkwin, colors[0], "", &sample,
		allowDefault);
	    break;
	case 2:
	    result = GetColorPair(interp, tkwin, colors[0], colors[1],
		&sample, allowDefault);
	    break;
	default:
	    result = TCL_ERROR;
	    Tcl_AppendResult(interp, "too many names in colors list",
		(char *)NULL);
	}
	Blt_Free(colors);
	if (result != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    Blt_FreeColorPair(pairPtr);
    *pairPtr = sample;
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * NameOfColor --
 *
 *	Convert the color option value into a string.
 *
 * Results:
 *	The static string representing the color option is returned.
 *
 *----------------------------------------------------------------------
 */
static char *
NameOfColor(colorPtr)
    XColor *colorPtr;
{
    if (colorPtr == NULL) {
	return "";
    } else if (colorPtr == COLOR_DEFAULT) {
	return "defcolor";
    } else {
	return Tk_NameOfColor(colorPtr);
    }
}

/*
 *----------------------------------------------------------------------
 *
 * ColorPairToString --
 *
 *	Convert the color pairs into color names.
 *
 * Results:
 *	The string representing the symbol color is returned.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static char *
ColorPairToString(clientData, tkwin, widgRec, offset, freeProcPtr)
    ClientData clientData;	/* Not used. */
    Tk_Window tkwin;		/* Not used. */
    char *widgRec;		/* Element information record */
    int offset;			/* Offset of symbol type field in record */
    Tcl_FreeProc **freeProcPtr;	/* Not used. */
{
    ColorPair *pairPtr = (ColorPair *)(widgRec + offset);
    Tcl_DString dString;
    char *result;

    Tcl_DStringInit(&dString);
    Tcl_DStringAppendElement(&dString, NameOfColor(pairPtr->fgColor));
    Tcl_DStringAppendElement(&dString, NameOfColor(pairPtr->bgColor));
    result = Tcl_DStringValue(&dString);
    if (result == dString.staticSpace) {
	result = Blt_Strdup(result);
    }
    *freeProcPtr = (Tcl_FreeProc *)Blt_Free;
    return result;
}

int
Blt_PointInSegments(samplePtr, segments, nSegments, halo)
    Point2D *samplePtr;
    Segment2D *segments;
    int nSegments;
    double halo;
{
    register Segment2D *segPtr, *endPtr;
    double left, right, top, bottom;
    Point2D p, t;
    double dist, minDist;

    minDist = DBL_MAX;
    for (segPtr = segments, endPtr = segments + nSegments; segPtr < endPtr; 
	 segPtr++) {
	t = Blt_GetProjection((int)samplePtr->x, (int)samplePtr->y, 
		      &segPtr->p, &segPtr->q);
	if (segPtr->p.x > segPtr->q.x) {
	    right = segPtr->p.x, left = segPtr->q.x;
	} else {
	    right = segPtr->q.x, left = segPtr->p.x;
	}
	if (segPtr->p.y > segPtr->q.y) {
	    bottom = segPtr->p.y, top = segPtr->q.y;
	} else {
	    bottom = segPtr->q.y, top = segPtr->p.y;
	}
	p.x = BOUND(t.x, left, right);
	p.y = BOUND(t.y, top, bottom);
	dist = hypot(p.x - samplePtr->x, p.y - samplePtr->y);
	if (dist < minDist) {
	    minDist = dist;
	}
    }
    return (minDist < halo);
}

int
Blt_PointInPolygon(samplePtr, points, nPoints)
    Point2D *samplePtr;
    Point2D *points;
    int nPoints;
{
    double b;
    register Point2D *p, *q, *endPtr;
    register int count;

    count = 0;
    for (p = points, q = p + 1, endPtr = p + nPoints; q < endPtr; p++, q++) {
	if (((p->y <= samplePtr->y) && (samplePtr->y < q->y)) || 
	    ((q->y <= samplePtr->y) && (samplePtr->y < p->y))) {
	    b = (q->x - p->x) * (samplePtr->y - p->y) / (q->y - p->y) + p->x;
	    if (samplePtr->x < b) {
		count++;	/* Count the number of intersections. */
	    }
	}
    }
    return (count & 0x01);
}

int
Blt_RegionInPolygon(extsPtr, points, nPoints, enclosed)
    Extents2D *extsPtr;
    Point2D *points;
    int nPoints;
    int enclosed;
{
    register Point2D *pointPtr, *endPtr;

    if (enclosed) {
	/*  
	 * All points of the polygon must be inside the rectangle.
	 */
	for (pointPtr = points, endPtr = points + nPoints; pointPtr < endPtr; 
	     pointPtr++) {
	    if ((pointPtr->x < extsPtr->left) ||
		(pointPtr->x > extsPtr->right) ||
		(pointPtr->y < extsPtr->top) ||
		(pointPtr->y > extsPtr->bottom)) {
		return FALSE;	/* One point is exterior. */
	    }
	}
	return TRUE;
    } else {
	Point2D p, q;

	/*
	 * If any segment of the polygon clips the bounding region, the
	 * polygon overlaps the rectangle.
	 */
	points[nPoints] = points[0];
	for (pointPtr = points, endPtr = points + nPoints; pointPtr < endPtr; 
	     pointPtr++) {
	    p = *pointPtr;
	    q = *(pointPtr + 1);
	    if (Blt_LineRectClip(extsPtr, &p, &q)) {
		return TRUE;
	    }
	}
	/* 
	 * Otherwise the polygon and rectangle are either disjoint
	 * or enclosed.  Check if one corner of the rectangle is
	 * inside the polygon.  
	 */
	p.x = extsPtr->left;
	p.y = extsPtr->top;
	return Blt_PointInPolygon(&p, points, nPoints);
    }
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_GraphExtents --
 *
 *	Generates a bounding box representing the plotting area of
 *	the graph. This data structure is used to clip the points and
 *	line segments of the line element.
 *
 *	The clip region is the plotting area plus such arbitrary extra
 *	space.  The reason we clip with a bounding box larger than the
 *	plot area is so that symbols will be drawn even if their center
 *	point isn't in the plotting area.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The bounding box is filled with the dimensions of the plotting
 *	area.
 *
 *----------------------------------------------------------------------
 */
void
Blt_GraphExtents(graphPtr, extsPtr)
    Graph *graphPtr;
    Extents2D *extsPtr;
{
    extsPtr->left = (double)(graphPtr->hOffset - graphPtr->padX.side1);
    extsPtr->top = (double)(graphPtr->vOffset - graphPtr->padY.side1);
    extsPtr->right = (double)(graphPtr->hOffset + graphPtr->hRange + 
	graphPtr->padX.side2);
    extsPtr->bottom = (double)(graphPtr->vOffset + graphPtr->vRange + 
	graphPtr->padY.side2);
}

static int 
ClipTest (double ds, double dr, double *t1, double *t2)
{
  double t;

  if (ds < 0.0) {
      t = dr / ds;
      if (t > *t2) {
	  return FALSE;
      } 
      if (t > *t1) {
	  *t1 = t;
      }
  } else if (ds > 0.0) {
      t = dr / ds;
      if (t < *t1) {
	  return FALSE;
      } 
      if (t < *t2) {
	  *t2 = t;
      }
  } else {
      /* d = 0, so line is parallel to this clipping edge */
      if (dr < 0.0) { /* Line is outside clipping edge */
	  return FALSE;
      }
  }
  return TRUE;
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_LineRectClip --
 *
 *	Clips the given line segment to a rectangular region.  The
 *	coordinates of the clipped line segment are returned.  The
 *	original coordinates are overwritten.
 *
 *	Reference:  Liang-Barsky Line Clipping Algorithm.
 *
 * Results:
 *	Returns if line segment is visible within the region. The
 *	coordinates of the original line segment are overwritten
 *	by the clipped coordinates.
 *
 *---------------------------------------------------------------------- 
 */
int 
Blt_LineRectClip(extsPtr, p, q)
    Extents2D *extsPtr;		/* Rectangular region to clip. */
    Point2D *p, *q;		/* (in/out) Coordinates of original
				 * and clipped line segment. */
{
    double t1, t2;
    double dx, dy;

    t1 = 0.0;
    t2 = 1.0;
    dx = q->x - p->x;
    if ((ClipTest (-dx, p->x - extsPtr->left, &t1, &t2)) &&
	(ClipTest (dx, extsPtr->right - p->x, &t1, &t2))) {
	dy = q->y - p->y;
	if ((ClipTest (-dy, p->y - extsPtr->top, &t1, &t2)) && 
	    (ClipTest (dy, extsPtr->bottom - p->y, &t1, &t2))) {
	    if (t2 < 1.0) {
		q->x = p->x + t2 * dx;
		q->y = p->y + t2 * dy;
	    }
	    if (t1 > 0.0) {
		p->x += t1 * dx;
		p->y += t1 * dy;
	    }
	    return TRUE;
	}
    }
    return FALSE;
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_PolyRectClip --
 *
 *	Clips the given polygon to a rectangular region.  The resulting
 *	polygon is returned. Note that the resulting polyon may be 
 *	complex, connected by zero width/height segments.  The drawing 
 *	routine (such as XFillPolygon) will not draw a connecting
 *	segment.
 *
 *	Reference:  Liang-Barsky Polygon Clipping Algorithm 
 *
 * Results:
 *	Returns the number of points in the clipped polygon. The
 *	points of the clipped polygon are stored in *outputPts*.
 *
 *---------------------------------------------------------------------- 
 */
#define EPSILON  FLT_EPSILON
#define AddVertex(vx, vy)	    r->x=(vx), r->y=(vy), r++, count++ 
#define LastVertex(vx, vy)	    r->x=(vx), r->y=(vy), count++ 

int 
Blt_PolyRectClip(extsPtr, points, nPoints, clipPts)
    Extents2D *extsPtr;
    Point2D *points;
    int nPoints;
    Point2D *clipPts;
{
    Point2D *endPtr;
    double dx, dy;
    double tin1, tin2;
    double tinx, tiny;
    double xin, yin, xout, yout;
    int count;
    register Point2D *p;	/* First vertex of input polygon edge. */
    register Point2D *q;	/* Last vertex of input polygon edge. */
    register Point2D *r;

    r = clipPts;
    count = 0;			/* Counts # of vertices in output polygon. */

    points[nPoints] = points[0];

    for (p = points, q = p + 1, endPtr = p + nPoints; p < endPtr; p++, q++) {
	dx = q->x - p->x;	/* X-direction */
	dy = q->y - p->y;	/* Y-direction */

	if (FABS(dx) < EPSILON) { 
	    dx = (p->x > extsPtr->left) ? -EPSILON : EPSILON ;
	}
	if (FABS(dy) < EPSILON) { 
	    dy = (p->y > extsPtr->top) ? -EPSILON : EPSILON ;
	}

	if (dx > 0.0) {		/* Left */
	    xin = extsPtr->left;
	    xout = extsPtr->right + 1.0;
	} else {		/* Right */
	    xin = extsPtr->right + 1.0;
	    xout = extsPtr->left;
	}
	if (dy > 0.0) {		/* Top */
	    yin = extsPtr->top;
	    yout = extsPtr->bottom + 1.0;
	} else {		/* Bottom */
	    yin = extsPtr->bottom + 1.0;
	    yout = extsPtr->top;
	}
	
	tinx = (xin - p->x) / dx;
	tiny = (yin - p->y) / dy;
	
	if (tinx < tiny) {	/* Hits x first */
	    tin1 = tinx;
	    tin2 = tiny;
	} else {		/* Hits y first */
	    tin1 = tiny;
	    tin2 = tinx;
	}
	
	if (tin1 <= 1.0) {
	    if (tin1 > 0.0) {
		AddVertex(xin, yin);
            }
	    if (tin2 <= 1.0) {
		double toutx, touty, tout1;

		toutx = (xout - p->x) / dx;
		touty = (yout - p->y) / dy;
		tout1 = MIN(toutx, touty);
		
		if ((tin2 > 0.0) || (tout1 > 0.0)) {
		    if (tin2 <= tout1) {
			if (tin2 > 0.0) {
			    if (tinx > tiny) {
				AddVertex(xin, p->y + tinx * dy);
			    } else {
				AddVertex(p->x + tiny * dx, yin);
			    }
			}
			if (tout1 < 1.0) {
			    if (toutx < touty) {
				AddVertex(xout, p->y + toutx * dy);
			    } else {
				AddVertex(p->x + touty * dx, yout);
			    }
			} else {
			    AddVertex(q->x, q->y);
			}
		    } else {
			if (tinx > tiny) {
			    AddVertex(xin, yout);
			} else {
			    AddVertex(xout, yin);
			}
		    }
		}
            }
	}
    }
    if (count > 0) {
	LastVertex(clipPts[0].x, clipPts[0].y);
    }
    return count;
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_GetProjection --
 *
 *	Computes the projection of a point on a line.  The line (given
 *	by two points), is assumed the be infinite.
 *
 *	Compute the slope (angle) of the line and rotate it 90 degrees.
 *	Using the slope-intercept method (we know the second line from
 *	the sample test point and the computed slope), then find the
 *	intersection of both lines. This will be the projection of the
 *	sample point on the first line.
 *
 * Results:
 *	Returns the coordinates of the projection on the line.
 *
 *----------------------------------------------------------------------
 */
Point2D
Blt_GetProjection(x, y, p, q)
    int x, y;			/* Screen coordinates of the sample point. */
    Point2D *p, *q;		/* Line segment to project point onto */
{
    double dx, dy;
    Point2D t;

    dx = p->x - q->x;
    dy = p->y - q->y;

    /* Test for horizontal and vertical lines */
    if (FABS(dx) < DBL_EPSILON) {
	t.x = p->x, t.y = (double)y;
    } else if (FABS(dy) < DBL_EPSILON) {
	t.x = (double)x, t.y = p->y;
    } else {
	double m1, m2;		/* Slope of both lines */
	double b1, b2;		/* y-intercepts */
	double midX, midY;	/* Midpoint of line segment. */
	double ax, ay, bx, by;

	/* Compute the slop and intercept of the line segment. */
	m1 = (dy / dx);
	b1 = p->y - (p->x * m1);

	/* 
	 * Compute the slope and intercept of a second line segment:
	 * one that intersects through sample X-Y coordinate with a
	 * slope perpendicular to original line. 
	 */

	/* Find midpoint of original segment. */
	midX = (p->x + q->x) * 0.5;
	midY = (p->y + q->y) * 0.5;

	/* Rotate the line 90 degrees */
	ax = midX - (0.5 * dy);
	ay = midY - (0.5 * -dx);
	bx = midX + (0.5 * dy);
	by = midY + (0.5 * -dx);

	m2 = (ay - by) / (ax - bx);
	b2 = y - (x * m2);

	/*
	 * Given the equations of two lines which contain the same point,
	 *
	 *    y = m1 * x + b1
	 *    y = m2 * x + b2
	 *
	 * solve for the intersection.
	 *
	 *    x = (b2 - b1) / (m1 - m2)
	 *    y = m1 * x + b1
	 *
	 */

	t.x = (b2 - b1) / (m1 - m2);
	t.y = m1 * t.x + b1;
    }
    return t;
}

typedef struct {
    double hue, sat, val;
} HSV;

#define SetColor(c,r,g,b) ((c)->red = (int)((r) * 65535.0), \
			   (c)->green = (int)((g) * 65535.0), \
			   (c)->blue = (int)((b) * 65535.0))

void
Blt_XColorToHSV(colorPtr, hsvPtr)
    XColor *colorPtr;
    HSV *hsvPtr;
{
    unsigned short max, min;
    double range;
    unsigned short *colorValues;

    /* Find the minimum and maximum RGB intensities */
    colorValues = (unsigned short *)&colorPtr->red;
    max = MAX3(colorValues[0], colorValues[1], colorValues[2]);
    min = MIN3(colorValues[0], colorValues[1], colorValues[2]);

    hsvPtr->val = (double)max / 65535.0;
    hsvPtr->hue = hsvPtr->sat = 0.0;

    range = (double)(max - min);
    if (max != min) {
	hsvPtr->sat = range / (double)max;
    }
    if (hsvPtr->sat > 0.0) {
	double red, green, blue;

	/* Normalize the RGB values */
	red = (double)(max - colorPtr->red) / range;
	green = (double)(max - colorPtr->green) / range;
	blue = (double)(max - colorPtr->blue) / range;

	if (colorPtr->red == max) {
	    hsvPtr->hue = (blue - green);
	} else if (colorPtr->green == max) {
	    hsvPtr->hue = 2 + (red - blue);
	} else if (colorPtr->blue == max) {
	    hsvPtr->hue = 4 + (green - red);
	}
	hsvPtr->hue *= 60.0;
    } else {
	hsvPtr->sat = 0.5;
    }
    if (hsvPtr->hue < 0.0) {
	hsvPtr->hue += 360.0;
    }
}

void
Blt_HSVToXColor(hsvPtr, colorPtr)
    HSV *hsvPtr;
    XColor *colorPtr;
{
    double hue, p, q, t;
    double frac;
    int quadrant;

    if (hsvPtr->val < 0.0) {
	hsvPtr->val = 0.0;
    } else if (hsvPtr->val > 1.0) {
	hsvPtr->val = 1.0;
    }
    if (hsvPtr->sat == 0.0) {
	SetColor(colorPtr, hsvPtr->val, hsvPtr->val, hsvPtr->val);
	return;
    }
    hue = FMOD(hsvPtr->hue, 360.0) / 60.0;
    quadrant = (int)floor(hue);
    frac = hsvPtr->hue - quadrant;
    p = hsvPtr->val * (1 - (hsvPtr->sat));
    q = hsvPtr->val * (1 - (hsvPtr->sat * frac));
    t = hsvPtr->val * (1 - (hsvPtr->sat * (1 - frac)));

    switch (quadrant) {
    case 0:
	SetColor(colorPtr, hsvPtr->val, t, p);
	break;
    case 1:
	SetColor(colorPtr, q, hsvPtr->val, p);
	break;
    case 2:
	SetColor(colorPtr, p, hsvPtr->val, t);
	break;
    case 3:
	SetColor(colorPtr, p, q, hsvPtr->val);
	break;
    case 4:
	SetColor(colorPtr, t, p, hsvPtr->val);
	break;
    case 5:
	SetColor(colorPtr, hsvPtr->val, p, q);
	break;
    }
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_AdjustViewport --
 *
 *	Adjusts the offsets of the viewport according to the scroll mode.
 *	This is to accommodate both "listbox" and "canvas" style scrolling.
 *
 *	"canvas"	The viewport scrolls within the range of world
 *			coordinates.  This way the viewport always displays
 *			a full page of the world.  If the world is smaller
 *			than the viewport, then (bizarrely) the world and
 *			viewport are inverted so that the world moves up
 *			and down within the viewport.
 *
 *	"listbox"	The viewport can scroll beyond the range of world
 *			coordinates.  Every entry can be displayed at the
 *			top of the viewport.  This also means that the
 *			scrollbar thumb weirdly shrinks as the last entry
 *			is scrolled upward.
 *
 * Results:
 *	The corrected offset is returned.
 *
 *----------------------------------------------------------------------
 */
int
Blt_AdjustViewport(offset, worldSize, windowSize, scrollUnits, scrollMode)
    int offset, worldSize, windowSize;
    int scrollUnits;
    int scrollMode;
{
    switch (scrollMode) {
    case BLT_SCROLL_MODE_CANVAS:

	/*
	 * Canvas-style scrolling allows the world to be scrolled
	 * within the window.
	 */

	if (worldSize < windowSize) {
	    if ((worldSize - offset) > windowSize) {
		offset = worldSize - windowSize;
	    }
	    if (offset > 0) {
		offset = 0;
	    }
	} else {
	    if ((offset + windowSize) > worldSize) {
		offset = worldSize - windowSize;
	    }
	    if (offset < 0) {
		offset = 0;
	    }
	}
	break;

    case BLT_SCROLL_MODE_LISTBOX:
	if (offset < 0) {
	    offset = 0;
	}
	if (offset >= worldSize) {
	    offset = worldSize - scrollUnits;
	}
	break;

    case BLT_SCROLL_MODE_HIERBOX:

	/*
	 * Hierbox-style scrolling allows the world to be scrolled
	 * within the window.
	 */
	if ((offset + windowSize) > worldSize) {
	    offset = worldSize - windowSize;
	}
	if (offset < 0) {
	    offset = 0;
	}
	break;
    }
    return offset;
}

int
Blt_GetScrollInfo(interp, argc, argv, offsetPtr, worldSize, windowSize,
    scrollUnits, scrollMode)
    Tcl_Interp *interp;
    int argc;
    char **argv;
    int *offsetPtr;
    int worldSize, windowSize;
    int scrollUnits;
    int scrollMode;
{
    char c;
    unsigned int length;
    int offset;
    int count;
    double fract;

    offset = *offsetPtr;
    c = argv[0][0];
    length = strlen(argv[0]);
    if ((c == 's') && (strncmp(argv[0], "scroll", length) == 0)) {
	if (argc != 3) {
	    return TCL_ERROR;
	}
	/* scroll number unit/page */
	if (Tcl_GetInt(interp, argv[1], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	c = argv[2][0];
	length = strlen(argv[2]);
	if ((c == 'u') && (strncmp(argv[2], "units", length) == 0)) {
	    fract = (double)count *scrollUnits;
	} else if ((c == 'p') && (strncmp(argv[2], "pages", length) == 0)) {
	    /* A page is 90% of the view-able window. */
	    fract = (double)count *windowSize * 0.9;
	} else {
	    Tcl_AppendResult(interp, "unknown \"scroll\" units \"", argv[2],
		"\"", (char *)NULL);
	    return TCL_ERROR;
	}
	offset += (int)fract;
    } else if ((c == 'm') && (strncmp(argv[0], "moveto", length) == 0)) {
	if (argc != 2) {
	    return TCL_ERROR;
	}
	/* moveto fraction */
	if (Tcl_GetDouble(interp, argv[1], &fract) != TCL_OK) {
	    return TCL_ERROR;
	}
	offset = (int)(worldSize * fract);
    } else {
	/* Treat like "scroll units" */
	if (Tcl_GetInt(interp, argv[0], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	fract = (double)count *scrollUnits;
	offset += (int)fract;
    }
    *offsetPtr = Blt_AdjustViewport(offset, worldSize, windowSize, scrollUnits,
	scrollMode);
    return TCL_OK;
}

#if (TCL_MAJOR_VERSION >= 8)
int
Blt_GetScrollInfoFromObj(interp, objc, objv, offsetPtr, worldSize, windowSize,
    scrollUnits, scrollMode)
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
    int *offsetPtr;
    int worldSize, windowSize;
    int scrollUnits;
    int scrollMode;
{
    char c;
    unsigned int length;
    int offset;
    int count;
    double fract;
    char *string;

    offset = *offsetPtr;

    string = Tcl_GetString(objv[0]);
    c = string[0];
    length = strlen(string);
    if ((c == 's') && (strncmp(string, "scroll", length) == 0)) {
	if (objc != 3) {
	    return TCL_ERROR;
	}
	/* scroll number unit/page */
	if (Tcl_GetIntFromObj(interp, objv[1], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	string = Tcl_GetString(objv[2]);
	c = string[0];
	length = strlen(string);
	if ((c == 'u') && (strncmp(string, "units", length) == 0)) {
	    fract = (double)count *scrollUnits;
	} else if ((c == 'p') && (strncmp(string, "pages", length) == 0)) {
	    /* A page is 90% of the view-able window. */
	    fract = (double)count *windowSize * 0.9;
	} else {
	    Tcl_AppendResult(interp, "unknown \"scroll\" units \"", 
		     Tcl_GetString(objv[2]), "\"", (char *)NULL);
	    return TCL_ERROR;
	}
	offset += (int)fract;
    } else if ((c == 'm') && (strncmp(string, "moveto", length) == 0)) {
	if (objc != 2) {
	    return TCL_ERROR;
	}
	/* moveto fraction */
	if (Tcl_GetDoubleFromObj(interp, objv[1], &fract) != TCL_OK) {
	    return TCL_ERROR;
	}
	offset = (int)(worldSize * fract);
    } else {
	/* Treat like "scroll units" */
	if (Tcl_GetIntFromObj(interp, objv[0], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	fract = (double)count *scrollUnits;
	offset += (int)fract;
    }
    *offsetPtr = Blt_AdjustViewport(offset, worldSize, windowSize, scrollUnits,
	scrollMode);
    return TCL_OK;
}
#endif /* TCL_MAJOR_VERSION >= 8 */

/*
 * ----------------------------------------------------------------------
 *
 * Blt_UpdateScrollbar --
 *
 * 	Invoke a Tcl command to the scrollbar, defining the new
 *	position and length of the scroll. See the Tk documentation
 *	for further information on the scrollbar.  It is assumed the
 *	scrollbar command prefix is valid.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Scrollbar is commanded to change position and/or size.
 *
 * ----------------------------------------------------------------------
 */
void
Blt_UpdateScrollbar(interp, scrollCmd, firstFract, lastFract)
    Tcl_Interp *interp;
    char *scrollCmd;		/* scrollbar command */
    double firstFract, lastFract;
{
    char string[200];
    Tcl_DString dString;

    Tcl_DStringInit(&dString);
    Tcl_DStringAppend(&dString, scrollCmd, -1);
    sprintf(string, " %f %f", firstFract, lastFract);
    Tcl_DStringAppend(&dString, string, -1);
    if (Tcl_GlobalEval(interp, Tcl_DStringValue(&dString)) != TCL_OK) {
	Tcl_BackgroundError(interp);
    }
    Tcl_DStringFree(&dString);
}

/* -------------- */
/*
 *----------------------------------------------------------------------
 *
 * Blt_GetPrivateGCFromDrawable --
 *
 *      Like Tk_GetGC, but doesn't share the GC with any other widget.
 *	This is needed because the certain GC parameters (like dashes)
 *	can not be set via XCreateGC, therefore there is no way for
 *	Tk's hashing mechanism to recognize that two such GCs differ.
 *
 * Results:
 *      A new GC is returned.
 *
 *----------------------------------------------------------------------
 */
GC
Blt_GetPrivateGCFromDrawable(display, drawable, gcMask, valuePtr)
    Display *display;
    Drawable drawable;
    unsigned long gcMask;
    XGCValues *valuePtr;
{
    GC newGC;

#ifdef WIN32
    newGC = Blt_EmulateXCreateGC(display, drawable, gcMask, valuePtr);
#else
    newGC = XCreateGC(display, drawable, gcMask, valuePtr);
#endif
    return newGC;
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_GetPrivateGC --
 *
 *      Like Tk_GetGC, but doesn't share the GC with any other widget.
 *	This is needed because the certain GC parameters (like dashes)
 *	can not be set via XCreateGC, therefore there is no way for
 *	Tk's hashing mechanism to recognize that two such GCs differ.
 *
 * Results:
 *      A new GC is returned.
 *
 *----------------------------------------------------------------------
 */
GC
Blt_GetPrivateGC(tkwin, gcMask, valuePtr)
    Tk_Window tkwin;
    unsigned long gcMask;
    XGCValues *valuePtr;
{
    GC gc;
    Pixmap pixmap;
    Drawable drawable;
    Display *display;

    pixmap = None;
    drawable = Tk_WindowId(tkwin);
    display = Tk_Display(tkwin);

    if (drawable == None) {
	Drawable root;
	int depth;

	root = RootWindow(display, Tk_ScreenNumber(tkwin));
	depth = Tk_Depth(tkwin);

	if (depth == DefaultDepth(display, Tk_ScreenNumber(tkwin))) {
	    drawable = root;
	} else {
	    pixmap = Tk_GetPixmap(display, root, 1, 1, depth);
	    drawable = pixmap;
	}
    }
    gc = Blt_GetPrivateGCFromDrawable(display, drawable, gcMask, valuePtr);
    if (pixmap != None) {
	Tk_FreePixmap(display, pixmap);
    }
    return gc;
}

void
Blt_FreePrivateGC(display, gc)
    Display *display;
    GC gc;
{
    Tk_FreeXId(display, (XID) XGContextFromGC(gc));
    XFreeGC(display, gc);
}

#ifndef WIN32
void
Blt_SetDashes(display, gc, dashesPtr)
    Display *display;
    GC gc;
    Blt_Dashes *dashesPtr;
{
    XSetDashes(display, gc, dashesPtr->offset, 
       (CONST char *)dashesPtr->values, strlen((char *)dashesPtr->values));
}
#endif


static double
FindSplit(points, i, j, split) 
    Point2D points[];
    int i, j;			/* Indices specifying the range of points. */
    int *split;			/* (out) Index of next split. */
{    double maxDist;
    
    maxDist = -1.0;
    if ((i + 1) < j) {
	register int k;
	double a, b, c;	
	double sqDist;

	/* 
	 * 
	 * sqDist P(k) =  |  1  P(i).x  P(i).y  |
	 *		  |  1  P(j).x  P(j).y  |
	 *                |  1  P(k).x  P(k).y  |
	 *              ---------------------------
 	 *       (P(i).x - P(j).x)^2 + (P(i).y - P(j).y)^2
	 */

	a = points[i].y - points[j].y;
	b = points[j].x - points[i].x;
	c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
	for (k = (i + 1); k < j; k++) {
	    sqDist = (points[k].x * a) + (points[k].y * b) + c;
	    if (sqDist < 0.0) {
		sqDist = -sqDist;	
	    }
	    if (sqDist > maxDist) {
		maxDist = sqDist;	/* Track the maximum. */
		*split = k;
	    }
	}
	/* Correction for segment length---should be redone if can == 0 */
	maxDist *= maxDist / (a * a + b * b);
    } 
    return maxDist;
}


/* Douglas-Peucker line simplification algorithm */
int
Blt_SimplifyLine(inputPts, low, high, tolerance, indices) 
   Point2D inputPts[];
   int low, high;
   double tolerance;
   int indices[];
{
#define StackPush(a)	s++, stack[s] = (a)
#define StackPop(a)	(a) = stack[s], s--
#define StackEmpty()	(s < 0)
#define StackTop()	stack[s]
    int *stack;
    int split = -1; 
    double sqDist, sqTolerance;
    int s = -1;			/* Points to top stack item. */
    int count;

    stack = Blt_Malloc(sizeof(int) * (high - low + 1));
    StackPush(high);
    count = 0;
    indices[count++] = 0;
    sqTolerance = tolerance * tolerance;
    while (!StackEmpty()) {
	sqDist = FindSplit(inputPts, low, StackTop(), &split);
	if (sqDist > sqTolerance) {
	    StackPush(split);
	} else {
	    indices[count++] = StackTop();
	    StackPop(low);
	}
    } 
    Blt_Free(stack);
    return count;
}

void
Blt_Draw2DSegments(display, drawable, gc, segPtr, nSegments)
    Display *display;
    Drawable drawable;
    GC gc;
    register Segment2D *segPtr;
    int nSegments;
{
    XSegment *xSegPtr, *xSegArr;
    Segment2D *endPtr;

    xSegArr = Blt_Malloc(nSegments * sizeof(XSegment));
    if (xSegArr == NULL) {
	return;
    }
    xSegPtr = xSegArr;
    for (endPtr = segPtr + nSegments; segPtr < endPtr; segPtr++) {
	xSegPtr->x1 = (short int)segPtr->p.x;
	xSegPtr->y1 = (short int)segPtr->p.y;
	xSegPtr->x2 = (short int)segPtr->q.x;
	xSegPtr->y2 = (short int)segPtr->q.y;
	xSegPtr++;
    }
    XDrawSegments(display, drawable, gc, xSegArr, nSegments);
    Blt_Free(xSegArr);
}

void
Blt_DrawArrow(display, drawable, gc, x, y, arrowHeight, orientation)
    Display *display;
    Drawable drawable;
    GC gc;
    int x, y;
    int arrowHeight;
    int orientation;
{
    XPoint arrow[5];
    int a, b;
    
    a = arrowHeight / 2 + 1;
    b = arrowHeight;
    switch (orientation) {
    case ARROW_UP:
	/*
	 *            0
	 *            +
	 *           / \
	 *          /   \
	 *         /     \  a
	 *        /       \
	 *   x,y /         \
	 *      +-----------+
	 *     1      b      2
	 */
	arrow[0].x = x;
	arrow[0].y = y - a;
	arrow[1].x = arrow[0].x - b;
	arrow[1].y = arrow[0].y + b;
	arrow[2].x = arrow[0].x + b;
	arrow[2].y = arrow[0].y + b;
	arrow[3].x = arrow[0].x;
	arrow[3].y = arrow[0].y;
	break;

    case ARROW_DOWN:
	/*
	 *     1      b      2
	 *      +-----------+
	 *       \         /
	 *        \  x,y  /
	 *         \     /  a
	 *          \   /
	 *           \ /
	 *            +
	 *            0
	 */
	arrow[0].x = x;
	arrow[0].y = y + a;
	arrow[1].x = arrow[0].x - b;
	arrow[1].y = arrow[0].y - b;
	arrow[2].x = arrow[0].x + b;
	arrow[2].y = arrow[0].y - b;
	arrow[3].x = arrow[0].x;
	arrow[3].y = arrow[0].y;
	break;

    case ARROW_RIGHT:
	/*
	 *       2
	 *	 +
	 *       |\
	 *       | \
	 *       |  \ 
	 *       |   \
	 *       |    \
	 *       | x,y + 0
	 *       |    /
	 *	 |   /
	 *       |  /
	 *       | /
	 *       |/
	 *       +
	 *       1
	 */
	arrow[0].x = x + a;
	arrow[0].y = y;
	arrow[1].x = arrow[0].x - b;
	arrow[1].y = arrow[0].y + b;
	arrow[2].x = arrow[0].x - b;
	arrow[2].y = arrow[0].y - b;
	arrow[3].x = arrow[0].x;
	arrow[3].y = arrow[0].y;
	break;

    case ARROW_LEFT:
	/*
	 *              2
	 *	       	+
	 *             /|
	 *            /	|
	 *           /	|
	 *          /	|
	 *         /  	|
	 *       0+ x,y |
	 *         \  	|
	 *	    \	|
	 *           \	|
	 *            \ |
	 *             \|
	 *       	+
	 *             	1
	 */
	arrow[0].x = x - a;
	arrow[0].y = y;
	arrow[1].x = arrow[0].x + b;
	arrow[1].y = arrow[0].y + b;
	arrow[2].x = arrow[0].x + b;
	arrow[2].y = arrow[0].y - b;
	arrow[3].x = arrow[0].x;
	arrow[3].y = arrow[0].y;
	break;

    }
    XFillPolygon(display, drawable, gc, arrow, 4, Convex, CoordModeOrigin);
    XDrawLines(display, drawable, gc, arrow, 4, CoordModeOrigin);
}

int 
Blt_MaxRequestSize(Display *display, unsigned int elemSize) 
{
    long size;

#ifdef HAVE_XEXTENDEDMAXREQUESTSIZE
    size = XExtendedMaxRequestSize(display);
    if (size == 0) {
	size = XMaxRequestSize(display);
    }
#else
    size = XMaxRequestSize(display);
#endif
    size -= 4;
    return ((size * 4) / elemSize);
}

#undef Blt_Fill3DRectangle
void
Blt_Fill3DRectangle(tkwin, drawable, border, x, y, width,
	height, borderWidth, relief)
    Tk_Window tkwin;		/* Window for which border was allocated. */
    Drawable drawable;		/* X window or pixmap in which to draw. */
    Tk_3DBorder border;		/* Token for border to draw. */
    int x, y, width, height;	/* Outside area of rectangular region. */
    int borderWidth;		/* Desired width for border, in
				 * pixels. Border will be *inside* region. */
    int relief;			/* Indicates 3D effect: TK_RELIEF_FLAT,
				 * TK_RELIEF_RAISED, or TK_RELIEF_SUNKEN. */
{
#ifndef notdef
    if ((borderWidth > 1) && (width > 2) && (height > 2) &&
	((relief == TK_RELIEF_SUNKEN) || (relief == TK_RELIEF_RAISED))) {
	GC lightGC, darkGC;
	int x2, y2;

	x2 = x + width - 1;
	y2 = y + height - 1;
#define TK_3D_LIGHT2_GC TK_3D_DARK_GC+1
#define TK_3D_DARK2_GC TK_3D_DARK_GC+2
	if (relief == TK_RELIEF_RAISED) {
	    lightGC = Tk_3DBorderGC(tkwin, border, TK_3D_FLAT_GC);
#ifdef WIN32
	    darkGC = Tk_3DBorderGC(tkwin, border, TK_3D_DARK_GC);
#else
	    darkGC = DefaultGC(Tk_Display(tkwin), Tk_ScreenNumber(tkwin));
#endif
	} else {
#ifdef WIN32
	    lightGC = Tk_3DBorderGC(tkwin, border, TK_3D_LIGHT_GC);
#else
	    lightGC = DefaultGC(Tk_Display(tkwin), Tk_ScreenNumber(tkwin));
#endif
	    darkGC = Tk_3DBorderGC(tkwin, border, TK_3D_FLAT_GC);
	}
	XDrawLine(Tk_Display(tkwin), drawable, lightGC, x, y, x2, y);
	XDrawLine(Tk_Display(tkwin), drawable, darkGC, x2, y2, x2, y);
	XDrawLine(Tk_Display(tkwin), drawable, darkGC, x2, y2, x, y2);
	XDrawLine(Tk_Display(tkwin), drawable, lightGC, x, y, x, y2);
	x++, y++, width -= 2, height -= 2, borderWidth--;
    }
#endif
    Tk_Fill3DRectangle(tkwin, drawable, border, x, y, width, height, 
	borderWidth, relief);
}


#undef Blt_Draw3DRectangle
void
Blt_Draw3DRectangle(tkwin, drawable, border, x, y, width,
	height, borderWidth, relief)
    Tk_Window tkwin;		/* Window for which border was allocated. */
    Drawable drawable;		/* X window or pixmap in which to draw. */
    Tk_3DBorder border;		/* Token for border to draw. */
    int x, y, width, height;	/* Outside area of rectangular region. */
    int borderWidth;		/* Desired width for border, in
				 * pixels. Border will be *inside* region. */
    int relief;			/* Indicates 3D effect: TK_RELIEF_FLAT,
				 * TK_RELIEF_RAISED, or TK_RELIEF_SUNKEN. */
{
#ifndef notdef
    if ((borderWidth > 1) && (width > 2) && (height > 2) &&
	((relief == TK_RELIEF_SUNKEN) || (relief == TK_RELIEF_RAISED))) {
	GC lightGC, darkGC;
	int x2, y2;

	x2 = x + width - 1;
	y2 = y + height - 1;
	if (relief == TK_RELIEF_RAISED) {
	    lightGC = Tk_3DBorderGC(tkwin, border, TK_3D_FLAT_GC);
#ifdef WIN32
	    darkGC = Tk_3DBorderGC(tkwin, border, TK_3D_DARK_GC);
#else
	    darkGC = DefaultGC(Tk_Display(tkwin), Tk_ScreenNumber(tkwin));
#endif
	} else {
#ifdef WIN32
	    lightGC = Tk_3DBorderGC(tkwin, border, TK_3D_LIGHT_GC);
#else
	    lightGC = DefaultGC(Tk_Display(tkwin), Tk_ScreenNumber(tkwin));
#endif
	    darkGC = Tk_3DBorderGC(tkwin, border, TK_3D_FLAT_GC);
	}
	XDrawLine(Tk_Display(tkwin), drawable, darkGC, x2, y2, x2, y);
	XDrawLine(Tk_Display(tkwin), drawable, lightGC, x, y, x2, y);
	XDrawLine(Tk_Display(tkwin), drawable, darkGC, x2, y2, x, y2);
	XDrawLine(Tk_Display(tkwin), drawable, lightGC, x, y, x, y2);
	x++, y++, width -= 2, height -= 2, borderWidth--;
    }
#endif
    Tk_Draw3DRectangle(tkwin, drawable, border, x, y, width, height, 
	borderWidth, relief);
}

#ifdef notdef
typedef struct {
    Screen *screen;
    Visual *visual;
    Colormap colormap;
    Tk_Uid nameUid;
} BorderKey;

typedef struct {
    Screen *screen;		/* Screen on which the border will be used. */
    Visual *visual;		/* Visual for all windows and pixmaps using
				 * the border. */
    int depth;			/* Number of bits per pixel of drawables where
				 * the border will be used. */
    Colormap colormap;		/* Colormap out of which pixels are
				 * allocated. */
    int refCount;		/* Number of active uses of this color
				 * (each active use corresponds to a
				 * call to Blt_Get3DBorder).  If this
				 * count is 0, then this structure is
				 * no longer valid and it isn't
				 * present in borderTable: it is being
				 * kept around only because there are
				 * objects referring to it.  The
				 * structure is freed when refCount is
				 * 0. */

    XColor *bgColorPtr;		/* Color of face. */
    XColor *shadows[4];

    Pixmap darkStipple;		/* Stipple pattern to use for drawing
				 * shadows areas.  Used for displays with
				 * <= 64 colors or where colormap has filled
				 * up. */
    Pixmap lightStipple;	/* Stipple pattern to use for drawing
				 * shadows areas.  Used for displays with
				 * <= 64 colors or where colormap has filled
				 * up. */
    GC bgGC;			/* Used (if necessary) to draw areas in
				 * the background color. */
    GC lightGC, darkGC;
    Tcl_HashEntry *hashPtr;	/* Entry in borderTable (needed in
				 * order to delete structure). */

    struct Blt_3DBorderStruct *nextPtr;
} Border, *Blt_3DBorder;
    

void
Blt_Draw3DRectangle(tkwin, drawable, border, x, y, width,
	height, borderWidth, relief)
    Tk_Window tkwin;		/* Window for which border was allocated. */
    Drawable drawable;		/* X window or pixmap in which to draw. */
    Blt_3DBorder *borderPtr;	/* Border to draw. */
    int x, y, width, height;	/* Outside area of rectangular region. */
    int borderWidth;		/* Desired width for border, in
				 * pixels. Border will be *inside* region. */
    int relief;			/* Indicates 3D effect: TK_RELIEF_FLAT,
				 * TK_RELIEF_RAISED, or TK_RELIEF_SUNKEN. */
{
    if ((width > (2 * borderWidth)) && (height > (2 * borderWidth))) {
	int x2, y2;
	int i;

	x2 = x + width - 1;
	y2 = y + height - 1;

	XSetForeground(borderPtr->lightGC, borderPtr->shadows[0]);
	XSetForeground(borderPtr->darkGC, borderPtr->shadows[3]);
	XDrawLine(Tk_Display(tkwin), drawable, borderPtr->lightGC, 
		  x, y, x2, y);
	XDrawLine(Tk_Display(tkwin), drawable, borderPtr->lightGC, 
		  x, y, x, y2);
	XDrawLine(Tk_Display(tkwin), drawable, borderPtr->darkGC, 
		  x2, y, x2, y2);
	XDrawLine(Tk_Display(tkwin), drawable, borderPtr->darkGC, 
		  x2, y2, x, y2);
	XSetForeground(borderPtr->lightGC, borderPtr->shadows[1]);
	XSetForeground(borderPtr->darkGC, borderPtr->shadows[2]);
	for (i = 1; i < (borderWidth - 1); i++) {

	    /*
	     *  +---------
	     *  |+-------
	     *  ||+-----
	     *  |||
	     *  |||
	     *  ||
	     *  |
	     */
	    x++, y++, x2--, y2--;
	    XDrawLine(Tk_Display(tkwin), drawable, borderPtr->lightGC, 
		x, y, x2, y);
	    XDrawLine(Tk_Display(tkwin), drawable, borderPtr->lightGC, 
		x, y, x, y2);
	    XDrawLine(Tk_Display(tkwin), drawable, borderPtr->darkGC, 
		x2, y, x2, y2);
	    XDrawLine(Tk_Display(tkwin), drawable, borderPtr->darkGC, 
		x2, y2, x, y2);
	}
    }
}

void
Blt_Fill3DRectangle(tkwin, drawable, border, x, y, width, height, borderWidth, 
	relief)
    Tk_Window tkwin;		/* Window for which border was allocated. */
    Drawable drawable;		/* X window or pixmap in which to draw. */
    Tk_3DBorder border;		/* Token for border to draw. */
    int x, y, width, height;	/* Outside area of rectangular region. */
    int borderWidth;		/* Desired width for border, in
				 * pixels. Border will be *inside* region. */
    int relief;			/* Indicates 3D effect: TK_RELIEF_FLAT,
				 * TK_RELIEF_RAISED, or TK_RELIEF_SUNKEN. */
{
    Blt_3DBorder *borderPtr;

    XFillRectangle(Tk_Display(tkwin), drawable, borderPtr->bgGC, x, y, width,
	   height);
    if ((borderWidth > 0) && (relief != BLT_RELIEF_FLAT)) {
	Blt_Draw3DRectangle(tkwin, drawable, borderPtr, x, y, width, height, 
	    borderWidth, relief);
    }
}


void 
FreeBorder(display, borderPtr)
    Display *display;
    Border *borderPtr;
{
    int i;

    if (borderPtr->bgColorPtr != NULL) {
	Tk_FreeColor(display, borderPtr->bgColorPtr);
    }
    for (i = 0; i < 4; i++) {
	Tk_FreeColor(display, borderPtr->shadows[i]);
    }
    if (borderPtr->tile != NULL) {
	Blt_FreeTile(tile);
    }
    if (borderPtr->darkGC != NULL) {
	Blt_FreePrivateGC(display, borderPtr->darkGC);
    }
    if (borderPtr->lightGC != NULL) {
	Blt_FreePrivateGC(tkwin, borderPtr->lightGC);
    }
    if (borderPtr->bgGC != NULL) {
	Blt_FreePrivateGC(tkwin, borderPtr->bgGC);
    }
    Blt_Free(borderPtr);
}

void
Blt_Free3DBorder(display, border)
    Display *display;
    Blt_3DBorder border;
{
    Border *borderPtr = (Border *)border;

    borderPtr->refCount--;
    if (borderPtr->refCount >= 0) {
	/* Search for the border in the bucket. Start at the head. */
	headPtr = Blt_GetHashValue(borderPtr->hashPtr);
	lastPtr = NULL;
	while ((headPtr != borderPtr) && (headPtr != NULL)) {
	    lastPtr = headPtr;
	    headPtr = headPtr->next;
	}
	if (headPtr == NULL) {
	    return;		/* This can't happen. It means that 
				 * we could not find the border. */
	}
	if (lastPtr != NULL) {
	    lastPtr->next = borderPtr->next;
	} else {
	    Tcl_DeleteHashEntry(borderPtr->hashPtr);
	}
	FreeBorder(display, borderPtr);
    }
}

Blt_3DBorder *
Blt_Get3DBorder(interp, tkwin, borderName)
    Tcl_Interp *interp;
    Tk_Window tkwin;
    char *borderName;
{
    Blt_3DBorder *borderPtr, *lastBorderPtr;
    Blt_HashEntry *hPtr;
    Blt_Tile tile;
    XColor *bgColorPtr;
    char **argv;
    char *colorName;
    int argc;
    int isNew;

    lastBorderPtr = NULL;
    hPtr = Tcl_CreateHashEntry(&dataPtr->borderTable, borderName, &isNew);
    if (!isNew) {
	borderPtr = lastBorderPtr = Blt_GetHashValue(hPtr);
	while (borderPtr != NULL) {
	    if ((Tk_Screen(tkwin) == borderPtr->screen) && 
		(Tk_Colormap(tkwin) == borderPtr->colormap)) {
		borderPtr->refCount++;
		return borderPtr;
	    }
	    borderPtr = borderPtr->nextPtr;
	}
    }
    /* Create a new border. */
    argv = NULL;
    bgColorPtr = NULL;
    tile = NULL;

    if (Tcl_SplitList(interp, borderName, &argc, &argv) != TCL_OK) {
	goto error;
    }
    colorName = borderName;
    if ((argc == 2) && (Blt_GetTile(interp, tkwin, argv[0], &tile) == TCL_OK)) {
	colorName = argv[1];
    }
    bgColorPtr = Tk_GetColor(interp, tkwin, colorName);
    if (bgColorPtr == NULL) {
	goto error;
    }

    /* Create a new border */
    borderPtr = Blt_Calloc(1, sizeof(Blt_3DBorder));
    assert(borderPtr);
    borderPtr->screen = Tk_Screen(tkwin);
    borderPtr->visual = Tk_Visual(tkwin);
    borderPtr->depth = Tk_Depth(tkwin);
    borderPtr->colormap = Tk_Colormap(tkwin);
    borderPtr->refCount = 1;
    borderPtr->bgColorPtr = bgColorPtr;
    borderPtr->tile = tile;
    borderPtr->darkGC = Blt_GetPrivateGC(tkwin, 0, NULL);
    borderPtr->lightGC = Blt_GetPrivateGC(tkwin, 0, NULL);
    borderPtr->hashPtr = lastBorderPtr->hashPtr;
    lastBorderPtr->nextPtr = lastBorderPtr;
    {
	HSV hsv;
	XColor color;
	double sat, sat0, diff, step, hstep;
	int count;
	
	/* Convert the face (background) color to HSV */
	Blt_XColorToHSV(borderPtr->bgColorPtr, &hsv);
	
	/* Using the color as the baseline intensity, pick a set of
	 * colors around the intensity. */
#define UFLOOR(x,u)		(floor((x)*(u))/(u))
	diff = hsv.sat - UFLOOR(hsv.sat, 0.2);
	sat = 0.1 + (diff - 0.1);
	sat0 = hsv.sat;
	count = 0;
	for (sat = 0.1 + (diff - 0.1); sat <= 1.0; sat += 0.2) {
	    if (FABS(sat0 - sat) >= 0.1) {
		hsv.sat = sat;
		Blt_HSVToXColor(&hsv, &color);
		borderPtr->shadows[count] = Tk_GetColorByValue(tkwin, &color);
		count++;
	    }
	}
    }
    Blt_SetHashValue(hPtr, borderPtr);
    if (argv != NULL) {
	Blt_Free(argv);
    }
    return TCL_OK;

 error:
    if (argv != NULL) {
	Blt_Free(argv);
    }
    if (tile != NULL) {
	Blt_FreeTile(tile);
    }
    if (bgColorPtr != NULL) {
	Tk_FreeColor(bgColorPtr);
    }
    if (isNew) {
	Blt_DeleteHashEntry(&borderTable, hPtr);
    }
    return NULL;
}

#endif

typedef struct {
    Blt_HashTable arcballTable;	/* Hash table of trees keyed by address. */
    Tcl_Interp *interp;
} ArcBallCmdInterpData;

#define ARCBALL_THREAD_KEY "BLT Arcball Command Data"
/* #define DEG2RAD	(M_PI / 180.0) */
#define DEG2RAD		0.017453292519943295
#define RAD2DEG		57.29577951308232

typedef struct {
    double x, y, z;
} Vector3d;

typedef struct {
    double x, y, z, w;
} Quaternion;

typedef struct {
    double x, y, z;
} EulerAngles;

typedef double HMatrix[3][3];

typedef struct {
    Tcl_Interp *interp;
    Blt_HashTable *tablePtr;
    Blt_HashEntry *hashPtr;
    ArcBallCmdInterpData *dataPtr;
    Tcl_Command cmdToken;
    Vector3d click, drag;		
    Quaternion q;
    double xScale, yScale;  
} ArcBall;

/*
 * Arcball sphere constants:
 * Diameter is       2.0
 * Radius is         1.0
 * Radius squared is 1.0
 */

static int
GetQuaternion(Tcl_Interp *interp, const char *string, Quaternion *q)
{
    double x, y, z, w;
    char **elems;
    int n;
    
    if (Tcl_SplitList(interp, string, &n, &elems) != TCL_OK) {
	return TCL_ERROR;
    }
    if (n != 4) {
	Tcl_AppendResult(interp, "wrong # of elements in quaterion \"",
		string, "\"", (char *)NULL);
	Blt_Free(elems);
	return TCL_ERROR;
    }
    if ((Tcl_GetDouble(interp, elems[0], &w) != TCL_OK) ||
	(Tcl_GetDouble(interp, elems[1], &x) != TCL_OK) ||
	(Tcl_GetDouble(interp, elems[2], &y) != TCL_OK) ||
	(Tcl_GetDouble(interp, elems[3], &z) != TCL_OK)) {
	Blt_Free(elems);
	return TCL_ERROR;
    }
    Blt_Free(elems);
    q->x = x, q->y = y, q->z = z, q->w = w;
    return TCL_OK;
}

static INLINE void
SetIdentity(Quaternion *q) 
{
    q->x = q->y = q->z = 0.0;
    q->w = 1.0;
}

static INLINE double 
Length(Vector3d *v)
{
    return sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

static INLINE double 
DotProduct(Vector3d *v1, Vector3d *v2)
{
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

/**
  * Calculate the cross product of two 3D vectors: c = a x b.
  * "c" must not refer to the same memory location as "a" or "b".
  */
static INLINE void 
CrossProduct(Vector3d *v1, Vector3d *v2, Vector3d *resultPtr)
{
    resultPtr->x = (v1->y * v2->z) - (v1->z * v2->y);
    resultPtr->y = (v1->z * v2->x) - (v1->x * v2->z);
    resultPtr->z = (v1->x * v2->y) - (v1->y * v2->x);
}


/* Return quaternion product qL * qR.  Note: order is important!
 * To combine rotations, use the product Mul(Second, First),
 * which gives the effect of rotating by First then Second. */
static void
CombineRotations(Quaternion *q1, Quaternion *q2, Quaternion *r)
{
    r->w = (q1->w*q2->w) - (q1->x*q2->x) - (q1->y*q2->y) - (q1->z*q2->z);
    r->x = (q1->w*q2->x) + (q1->x*q2->w) + (q1->y*q2->z) - (q1->z*q2->y);
    r->y = (q1->w*q2->y) + (q1->y*q2->w) + (q1->z*q2->x) - (q1->x*q2->z);
    r->z = (q1->w*q2->z) + (q1->z*q2->w) + (q1->x*q2->y) - (q1->y*q2->x);
}

static int
GetMatrix(Tcl_Interp *interp, char *string, HMatrix A)
{
    char **elems;
    int n;
    int i, j, k;
    
    if (Tcl_SplitList(interp, string, &n, &elems) != TCL_OK) {
	return TCL_ERROR;
    }
    if (n != 9) {
	Tcl_AppendResult(interp, "wrong # of elements in rotation matrix \"",
		string, "\"", (char *)NULL);
	Blt_Free(elems);
	return TCL_ERROR;
    }
    k = 0;
    for (i = 0; i < 3; i++) {
	for (j = 0; j < 3; j++) {
	    double x;

	    if (Tcl_GetDouble(interp, elems[k], &x) != TCL_OK) {
		Blt_Free(elems);
		return TCL_ERROR;
	    }
	    A[i][j] = x;
	    k++;
	}
    }
    Blt_Free(elems);
    return TCL_OK;
}

/**
 * Sets the value of this matrix to the result of multiplying itself
 * with matrix m1. 
 * @param m1 the other matrix 
 */

/** Multiply the upper left 3x3 parts of A and B to get AB **/
static void 
MultipleMatrices(HMatrix A, HMatrix B, HMatrix AB)
{
    int i;

    for (i = 0; i < 3; i++) {
	int j;

	for (j = 0; j < 3; j++) {
	    AB[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j];
	}
    }
} 

static void 
MultipleMatrices2(HMatrix A, HMatrix B, HMatrix AB)
{
    AB[0][0] = (A[0][0]*B[0][0]) + (A[0][1]*B[1][0]) + (A[0][2]*B[2][0]);
    AB[0][1] = (A[0][0]*B[0][1]) + (A[0][1]*B[1][1]) + (A[0][2]*B[2][1]);
    AB[0][2] = (A[0][0]*B[0][2]) + (A[0][1]*B[1][2]) + (A[0][2]*B[2][2]);
    
    AB[1][0] = (A[1][0]*B[0][0]) + (A[1][1]*B[1][0]) + (A[1][2]*B[2][0]);
    AB[1][1] = (A[1][0]*B[0][1]) + (A[1][1]*B[1][1]) + (A[1][2]*B[2][1]);
    AB[1][2] = (A[1][0]*B[0][2]) + (A[1][1]*B[1][2]) + (A[1][2]*B[2][2]);
    
    AB[2][0] = (A[2][0]*B[0][0]) + (A[2][1]*B[1][0]) + (A[2][2]*B[2][0]);
    AB[2][1] = (A[2][0]*B[0][1]) + (A[2][1]*B[1][1]) + (A[2][2]*B[2][1]);
    AB[2][2] = (A[2][0]*B[0][2]) + (A[2][1]*B[1][2]) + (A[2][2]*B[2][2]);
}

static double 
Matrix4fSVD(HMatrix A) 
{
    // this is a simple svd.
    // Not complete but fast and reasonable.
    // See comment in Matrix3d.
    return sqrt(((A[0][0]*A[0][0]) + (A[1][0]*A[1][0]) + 
		 (A[2][0]*A[2][0]) + (A[0][1]*A[0][1]) + 
		 (A[1][1]*A[1][1]) + (A[2][1]*A[2][1]) +
		 (A[0][2]*A[0][2]) + (A[1][2]*A[1][2]) + 
		 (A[2][2]*A[2][2])) / 3.0);
}

static void 
SetMatrix4x4FromMatrix3x3(HMatrix m1, HMatrix result)
{
    result[0][0] = m1[0][0]; 
    result[0][1] = m1[0][1]; 
    result[0][2] = m1[0][2];
    result[1][0] = m1[1][0]; 
    result[1][1] = m1[1][1]; 
    result[1][2] = m1[1][2];
    result[2][0] = m1[2][0]; 
    result[2][1] = m1[2][1]; 
    result[2][2] = m1[2][2];
}

static void 
ScaleMatrix(HMatrix A, double scale)
{
    A[0][0] *= scale; 
    A[0][1] *= scale; 
    A[0][2] *= scale;
    A[1][0] *= scale; 
    A[1][1] *= scale; 
    A[1][2] *= scale;
    A[2][0] *= scale; 
    A[2][1] *= scale; 
    A[2][2] *= scale;
}

static void 
Matrix4fSetRotationFromMatrix3f(HMatrix A, HMatrix B)
{
    double scale;
    
    scale = Matrix4fSVD(A);
    SetMatrix4x4FromMatrix3x3(B, A);
    ScaleMatrix(A, scale);
}

static void 
MatrixToQuaternion(HMatrix A, Quaternion *q)
{
    double trace;

   /* This algorithm avoids near-zero divides by looking for a large component
    * - first w, then x, y, or z.  When the trace is greater than zero, |w| is
    * greater than 1/2, which is as small as a largest component can be.
    * Otherwise, the largest diagonal entry corresponds to the largest of |x|,
    * |y|, or |z|, one of which must be larger than |w|, and at least 1/2. */

    // I removed + 1.0; see discussion with Ethan
    trace = A[0][0] + A[1][1] + A[2][2]; 
    if (trace >= 0.0) {			// I changed M_EPSILON to 0
	double s;

	s = 0.5 / sqrt(trace + 1.0);  /* A[3][3] = 1.0 */
	q->w = 0.25 / s;
	q->x = (A[2][1] - A[1][2]) * s;
	q->y = (A[0][2] - A[2][0]) * s;
	q->z = (A[1][0] - A[0][1]) * s;

    } else if ((A[0][0] > A[1][1]) && (A[0][0] > A[2][2])) {
	double s;
	
	s = 2.0 * sqrt(A[0][0] - (A[1][1] + A[2][2]) + 1.0);
	q->w = (A[2][1] - A[1][2]) / s;
	q->x = 0.25 * s;
	q->y = (A[0][1] + A[1][0]) / s;
	q->z = (A[0][2] + A[2][0]) / s;
    } else if (A[1][1] > A[2][2]) {
	double s;
	
	s = 2.0 * sqrt(1.0 + A[1][1] - A[0][0] - A[2][2]);
	q->w = (A[0][2] - A[2][0]) / s;
	q->x = (A[0][1] + A[1][0]) / s;
	q->y = 0.25 * s;
	q->z = (A[1][2] + A[2][1]) / s;
    } else {
	double s;
	
	s = 2.0 * sqrt(1.0 + A[2][2] - A[0][0] - A[1][1]);
	q->w = (A[1][0] - A[0][1]) / s;
	q->x = (A[0][2] + A[2][0]) / s;
	q->y = (A[1][2] + A[2][1]) / s;
	q->z = 0.25 * s;
    }
}

static void 
QuaternionToMatrix(Quaternion* q, HMatrix A)
{
    double n, s;
    double xs, ys, zs;
    double wx, wy, wz;
    double xx, xy, xz;
    double yy, yz, zz;

    n = (q->x * q->x) + (q->y * q->y) + (q->z * q->z) + (q->w * q->w);

    s = (n > 0.0) ? (2.0 / n) : 0.0;
    
    xs = q->x * s;  
    ys = q->y * s;  
    zs = q->z * s;
    wx = q->w * xs; 
    wy = q->w * ys; 
    wz = q->w * zs;
    xx = q->x * xs; 
    xy = q->x * ys; 
    xz = q->x * zs;
    yy = q->y * ys; 
    yz = q->y * zs; 
    zz = q->z * zs;
    
    A[0][0] = 1.0 - (yy + zz); 
    A[0][1] = xy - wz;  
    A[0][2] = xz + wy;
    A[1][0] = xy + wz;  
    A[1][1] = 1.0 - (xx + zz); 
    A[1][2] = yz - wx;
    A[2][0] = xz - wy;  
    A[2][1] = yz + wx;  
    A[2][2] = 1.0 - (xx + yy);
}


/*
 *----------------------------------------------------------------------
 *
 * GetArcBall --
 *
 *	Find the arcball command associated with the Tcl command "string".
 *	
 *	We have to do multiple lookups to get this right.  
 *
 *	The first step is to generate a canonical command name.  If an
 *	unqualified command name (i.e. no namespace qualifier) is
 *	given, we should search first the current namespace and then
 *	the global one.  Most Tcl commands (like Tcl_GetCmdInfo) look
 *	only at the global namespace.
 *
 *	Next check if the string is 
 *		a) a Tcl command and 
 *		b) really is a command for a tree object.  
 *	Tcl_GetCommandInfo will get us the objClientData field that 
 *	should be a cmdPtr.  We can verify that by searching our hashtable 
 *	of cmdPtr addresses.
 *
 * Results:
 *	A pointer to the tree command.  If no associated tree command
 *	can be found, NULL is returned.  It's up to the calling routines
 *	to generate an error message.
 *
 *---------------------------------------------------------------------- 
 */
static ArcBall *
GetArcBall(
    ArcBallCmdInterpData *dataPtr, 
    Tcl_Interp *interp, 
    const char *string)
{
    const char *name;
    Tcl_Namespace *nsPtr;
    Tcl_CmdInfo cmdInfo;
    Blt_HashEntry *hPtr;
    Tcl_DString dString;
    char *abName;
    int result;

    /* Put apart the tree name and put is back together in a standard
     * format. */
    if (Blt_ParseQualifiedName(interp, string, &nsPtr, &name) != TCL_OK) {
	return NULL;		/* No such parent namespace. */
    }
    if (nsPtr == NULL) {
	nsPtr = Tcl_GetCurrentNamespace(interp);
    }
    /* Rebuild the fully qualified name. */
    abName = Blt_GetQualifiedName(nsPtr, name, &dString);
    result = Tcl_GetCommandInfo(interp, abName, &cmdInfo);
    Tcl_DStringFree(&dString);
    if (!result) {
	return NULL;
    }
    hPtr = Blt_FindHashEntry(&dataPtr->arcballTable, 
			     (char *)(cmdInfo.objClientData));
    if (hPtr == NULL) {
	return NULL;
    }
    return Blt_GetHashValue(hPtr);
}

static void 
SetArcBallBounds(ArcBall *arcPtr, double w, double h)
{
    if (w <= 1.0 ) {
        w = 2.0;
    }
    if (h <= 1.0 ) {
        h = 2.0;
    }
    /* Set adjustment factor for width/height */
    arcPtr->xScale = 1.0 / ((w - 1.0) * 0.5);
    arcPtr->yScale = 1.0 / ((h - 1.0) * 0.5);
}

static ArcBall *
CreateArcBall(double w, double h)
{
    ArcBall *abPtr;

    abPtr = Blt_Calloc(1, sizeof(ArcBall));
    SetArcBallBounds (abPtr, w, h);
    return abPtr;
}

static void 
PointOnSphere(ArcBall *arcPtr, double x, double y, Vector3d *outPtr)
{
    double sx, sy;
    double d2;

    /* Adjust point coords and scale down to range of [-1 ... 1] */
    sx = (x * arcPtr->xScale)  - 1.0;
    sy = 1.0 - (y * arcPtr->yScale);

    /* Compute the square of the length of the vector to the point from the
     * center. */
    d2 = (sx * sx) + (sy * sy);

    /* If the point is mapped outside of the sphere ... 
     * (length > radius squared)
     */
    if (d2 > 1.0) {
        double scale;

        /* Compute a normalizing factor (radius / sqrt(length)) */
        scale = 1.0 / sqrt(d2);

        /* Return the "normalized" vector, a point on the sphere */
        outPtr->x = sx * scale;
        outPtr->y = sy * scale;
        outPtr->z = 0.0;
    } else {   /* else it's on the inside */
        /* Return a vector to a point mapped inside the sphere
         * sqrt(radius squared - length) */
        outPtr->x = sx;
        outPtr->y = sy;
        outPtr->z = sqrt(1.0 - d2);
    }
}

/* Mouse down: Supply mouse position in x and y */
static void 
ClickArcBall(ArcBall *arcPtr, double x, double y)
{
    PointOnSphere (arcPtr, x, y, &arcPtr->click);
}

/* Mouse drag, calculate rotation: Supply mouse position in x and y */
static void 
DragArcBall(ArcBall *arcPtr, double x, double y, Quaternion *q)
{
    /* Map the point to the sphere */
    PointOnSphere(arcPtr, x, y, &arcPtr->drag);

    /* Return the quaternion equivalent to the rotation */
    if (q != NULL) {
        Vector3d perp;

        /* Compute the vector perpendicular to the begin and end vectors */
        CrossProduct(&arcPtr->click, &arcPtr->drag, &perp);

        /* Compute the length of the perpendicular vector */
        if (Length(&perp) > DBL_EPSILON) {
            /* If its non-zero, we're ok, so return the perpendicular
             * vector as the transform after all
             */
            q->x = perp.x;
            q->y = perp.y;
            q->z = perp.z;
            /* In the quaternion values, w is cosine (theta / 2),
             * where theta is rotation angle
             */
            q->w = DotProduct(&arcPtr->click, &arcPtr->drag);
        } else {
            /* If it is zero, the begin and end vectors coincide,
             * so return an identity transform
             */
            q->w = 1.0;
            q->x = q->y = q->z = 0.0;
        }
    }
}

static int
GetEulerAngles(Tcl_Interp *interp, char *string, EulerAngles *e)
{
    double x, y, z;
    char **elems;
    int n;
    
    if (Tcl_SplitList(interp, string, &n, &elems) != TCL_OK) {
	return TCL_ERROR;
    }
    if (n != 4) {
	Tcl_AppendResult(interp, "wrong # of elements in quaterion \"",
		string, "\"", (char *)NULL);
	Blt_Free(elems);
	return TCL_ERROR;
    }
    if ((Tcl_GetDouble(interp, elems[0], &x) != TCL_OK) ||
	(Tcl_GetDouble(interp, elems[1], &y) != TCL_OK) ||
	(Tcl_GetDouble(interp, elems[2], &z) != TCL_OK)) {
	Blt_Free(elems);
	return TCL_ERROR;
    }
    Blt_Free(elems);
    e->x = x, e->y = y, e->z = z;
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallEulerOp --
 *
 * 	Sets/gets the current quaternion in terms of euler angles.
 *
 * Results:
 *	A standard Tcl result.  A list of three numbers representing
 *	the euler angles will be returned.
 *
 *	$arcball euler "$x $y $z"
 *	set angles [$arcball euler]
 *
 * --------------------------------------------------------------
 */
static int
ArcBallEulerOp(ClientData clientData, Tcl_Interp *interp, int argc, 
	       char **argv)
{
    ArcBall *abPtr = clientData;

    if (argc == 3) {
	EulerAngles euler;
	Quaternion q1, q2, q3;
	double theta, phi, psi;

	if (GetEulerAngles(interp, argv[2], &euler) != TCL_OK) {
	    return TCL_ERROR;
	}
	theta = euler.x * DEG2RAD;
	phi   = euler.y * DEG2RAD;
	psi   = euler.z * DEG2RAD;
	
	q1.w = cos(theta * 0.5);
	q1.x = sin(theta * 0.5);
	q1.y = 0.0;
	q1.z = 0.0;
	
	q2.w = cos(phi * 0.5);
	q2.x = sin(phi * 0.5);
	q2.y = 0.0;
	q2.z = 0.0;
	
	CombineRotations(&q1, &q2, &q3);
	
	q1.w = cos(psi * 0.5);
	q1.x = sin(psi * 0.5);
	q1.y = 0.0;
	q1.z = 0.0;
	
	CombineRotations(&q3, &q1, &abPtr->q);
    } else {
	HMatrix A;
	double phi, cosPhi;
	Tcl_Obj *objPtr, *listObjPtr;
	double x, y, z;

	QuaternionToMatrix(&abPtr->q, A);
	phi = -asin(A[0][2]);		/* Calculate Y-axis angle */
	cosPhi = cos(phi);
	y = phi * RAD2DEG;
	
	if (fabs(cosPhi) > 0.005) {	/* Gimball lock? */
	    double trx, try;

	    trx =  A[2][2] / cosPhi;	/* No, so get X-axis angle */
	    try = -A[1][2] / cosPhi;
	    x  = atan2(try, trx) * RAD2DEG;
	    
	    trx =  A[0][0] / cosPhi;	/* Get Z-axis angle */
	    try = -A[0][1] / cosPhi;
	    z  = atan2(try, trx) * RAD2DEG;
	} else {			/* Gimball lock has occurred */
	    double trx, try;

	    x = 0.0;			/* X-axis angle is zero. */
	    
	    trx = A[1][1];		/* Compute Z-axis angle */
	    try = A[1][0];
	    z  = atan2(try, trx) * RAD2DEG;
	}
	/* Clamp all angles to range */
#define CLAMP(x)	(((x) < 0.0) ? 0.0 : ((x) > 360.0) ? 360.0 : (x))
	x = CLAMP(x);
	y = CLAMP(y);
	z = CLAMP(z);

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
	objPtr = Tcl_NewDoubleObj(x);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
 	objPtr = Tcl_NewDoubleObj(y);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewDoubleObj(z);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
    }
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallMatrixOp --
 *
 * 	Sets/gets the rotation matrix from the current quaternion.  The 3x3
 * 	rotation matrix is represented by nine numbers (row-major).
 *
 * Results:
 *	A standard Tcl result.  A list representing the rotation matrix is
 *	returned.
 *
 *	$arcball matrix $matrix
 *	set q [$arcball quaternion]
 *
 * --------------------------------------------------------------
 */
static int
ArcBallMatrixOp(ClientData clientData, Tcl_Interp *interp, int argc, 
		char **argv)
{
    ArcBall *abPtr = clientData;

    if (argc == 3) {
	HMatrix A;

	if (GetMatrix(interp, argv[2], A) != TCL_OK) {
	    return TCL_ERROR;
	}
	MatrixToQuaternion(A, &abPtr->q);
    } else {
	HMatrix A;
	Tcl_Obj *listObjPtr;
	int i, j;

	QuaternionToMatrix(&abPtr->q, A);
	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
	for (i = 0; i < 3; i++) {
	    for (j = 0; j < 3; j++) {
		Tcl_Obj *objPtr;
		
		objPtr = Tcl_NewDoubleObj(A[i][j]);
		Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	    }
	}
	Tcl_SetObjResult(interp, listObjPtr);
    }
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallQuaternionOp --
 *
 * 	Sets/gets the current quaternion.
 *
 * Results:
 *	A standard Tcl result.  A list representing the quaternion is
 *	returned.
 *
 *	$arcball quaternion "$w $x $y $z"
 *	set q [$arcball quaternion]
 *
 * --------------------------------------------------------------
 */
static int
ArcBallQuaternionOp(ClientData clientData, Tcl_Interp *interp, int argc, 
		    char **argv)
{
    ArcBall *abPtr = clientData;

    if (argc == 3) {
	Quaternion q;

	if (GetQuaternion(interp, argv[2], &q) != TCL_OK) {
	    return TCL_ERROR;
	}
	abPtr->q = q;
    } else {
	Tcl_Obj *objPtr, *listObjPtr;

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
	objPtr = Tcl_NewDoubleObj(abPtr->q.w);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
 	objPtr = Tcl_NewDoubleObj(abPtr->q.x);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewDoubleObj(abPtr->q.y);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewDoubleObj(abPtr->q.z);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
    }
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallResetOp --
 *
 * 	Resets the quaterion to identify.  Used also the initialize the
 * 	quaternion.
 *
 * Results:
 *	A standard Tcl result.  Always returns TCL_OK.
 *
 *	$arcball reset
 *
 * --------------------------------------------------------------
 */
static int
ArcBallResetOp(ClientData clientData, Tcl_Interp *interp, int argc, 
		    char **argv)
{
    ArcBall *abPtr = clientData;

    SetIdentity(&abPtr->q);
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallResizeOp --
 *
 * 	Sets new dimensions for the arcball window.
 *
 * Results:
 *	A standard Tcl result.
 *
 *	$arcball resize $w $h
 *
 * --------------------------------------------------------------
 */
static int
ArcBallResizeOp(ClientData clientData, Tcl_Interp *interp, int argc, 
		    char **argv)
{
    ArcBall *abPtr = clientData;
    int w, h;

    if ((Tcl_GetInt(interp, argv[2], &w) != TCL_OK) ||
	(Tcl_GetInt(interp, argv[3], &h) != TCL_OK)) {
	return TCL_ERROR;
    }
    SetArcBallBounds(abPtr, w, h);
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallRotateOp --
 *
 * 	Rotates the arcball based upon the starting end ending coordinates
 * 	in the window.
 *
 * Results:
 *	A standard Tcl result.  A list representing the new rotated
 *	quaternion is returned.
 *
 *	$arcball rotate $x1 $y1 $x2 $y2
 *
 * --------------------------------------------------------------
 */
static int
ArcBallRotateOp(ClientData clientData, Tcl_Interp *interp, int argc, 
		char **argv)
{
    ArcBall *abPtr = clientData;
    Quaternion q, p;
    Tcl_Obj *listObjPtr;
    double x1, y1, x2, y2;

    if ((Tcl_GetDouble(interp, argv[2], &x1) != TCL_OK) ||
	(Tcl_GetDouble(interp, argv[3], &y1) != TCL_OK) ||
	(Tcl_GetDouble(interp, argv[4], &x2) != TCL_OK) ||
	(Tcl_GetDouble(interp, argv[5], &y2) != TCL_OK)) {
	return TCL_ERROR;
    }
    ClickArcBall(abPtr, x1, y1);
    DragArcBall(abPtr, x2, y2, &q);
    p = abPtr->q;
    CombineRotations(&p, &q, &abPtr->q);
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(abPtr->q.w));
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(abPtr->q.x));
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(abPtr->q.y));
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(abPtr->q.z));
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*
 * --------------------------------------------------------------
 *
 * ArcBallInstCmd --
 *
 * 	This procedure is invoked to process commands on behalf of
 *	the tree object.
 *
 * Results:
 *	A standard Tcl result.
 *
 * Side effects:
 *	See the user documentation.
 *
 * --------------------------------------------------------------
 */
static Blt_OpSpec arcBallOps[] =
{
    {"euler",      1, ArcBallEulerOp,      2, 3, "?angles?",},
    {"matrix",     1, ArcBallMatrixOp,     2, 3, "?matrix?",},
    {"quaternion", 1, ArcBallQuaternionOp, 2, 3, "?quat?",},
    {"reset",      3, ArcBallResetOp,      2, 2, "",},
    {"resize",     3, ArcBallResizeOp,     4, 4, "w h",},
    {"rotate",     2, ArcBallRotateOp,     6, 6, "x1 y1 x2 y2",},
};
static int nArcBallOps = sizeof(arcBallOps) / sizeof(Blt_OpSpec);

static int
ArcBallInstCmd(ClientData clientData, Tcl_Interp *interp, int argc, 
		 char **argv)
{
    Tcl_CmdProc *proc;
    int result;
    ArcBall *abPtr = clientData;

    proc = Blt_GetOp(interp, nArcBallOps, arcBallOps, BLT_OP_ARG1, argc, argv, 
		     0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    Tcl_Preserve(abPtr);
    result = (*proc) (clientData, interp, argc, argv);
    Tcl_Release(abPtr);
    return result;
}

/*
 * ----------------------------------------------------------------------
 *
 * ArcBallInstDeleteProc --
 *
 *	Deletes the command associated with the arcball.  This is
 *	called only when the command associated with the arcball is
 *	destroyed.
 *
 * Results:
 *	None.
 *
 * ----------------------------------------------------------------------
 */
static void
ArcBallInstDeleteProc(ClientData clientData)
{
    ArcBall *abPtr = clientData;

    if (abPtr->hashPtr != NULL) {
	Blt_DeleteHashEntry(abPtr->tablePtr, abPtr->hashPtr);
    }
    Blt_Free(abPtr);
}

/*
 * ----------------------------------------------------------------------
 *
 * GenerateName --
 *
 *	Generates an unique arcball command name.  Arcball names are in
 *	the form "arcballN", where N is a non-negative integer. Check 
 *	each name generated to see if it is already a tree. We want
 *	to recycle names if possible.
 *	
 * Results:
 *	Returns the unique name.  The string itself is stored in the
 *	dynamic string passed into the routine.
 *
 * ----------------------------------------------------------------------
 */
static const char *
GenerateName(Tcl_Interp *interp, CONST char *prefix, CONST char *suffix,
	     Tcl_DString *resultPtr)
{

    int n;
    Tcl_Namespace *nsPtr;
    char string[200];
    Tcl_CmdInfo cmdInfo;
    Tcl_DString dString;
    CONST char *abName, *name;

    /* 
     * Parse the command and put back so that it's in a consistent
     * format.  
     *
     *	t1         <current namespace>::t1
     *	n1::t1     <current namespace>::n1::t1
     *	::t1	   ::t1
     *  ::n1::t1   ::n1::t1
     */
    abName = NULL;		/* Suppress compiler warning. */
    for (n = 0; n < INT_MAX; n++) {
	Tcl_DStringInit(&dString);
	Tcl_DStringAppend(&dString, prefix, -1);
	sprintf(string, "arcball%d", n);
	Tcl_DStringAppend(&dString, string, -1);
	Tcl_DStringAppend(&dString, suffix, -1);
	abName = Tcl_DStringValue(&dString);
	if (Blt_ParseQualifiedName(interp, abName, &nsPtr, &name) != TCL_OK) {
	    Tcl_AppendResult(interp, "can't find namespace in \"", abName, 
		"\"", (char *)NULL);
	    return NULL;
	}
	if (nsPtr == NULL) {
	    nsPtr = Tcl_GetCurrentNamespace(interp);
	}
	abName = Blt_GetQualifiedName(nsPtr, name, resultPtr);
	/* 
	 * Check if the command already exists. 
	 */
	if (Tcl_GetCommandInfo(interp, (char *)abName, &cmdInfo)) {
	    continue;
	}
	break;
    }
    return abName;
}

/*
 *----------------------------------------------------------------------
 *
 * ArcBallCreateOp --
 *
 *	arcball create x w h 
 *---------------------------------------------------------------------- 
 */
/*ARGSUSED*/
static int
ArcBallCreateOp(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    ArcBallCmdInterpData *dataPtr = clientData;
    const char *abName;
    Tcl_DString dString;
    int isNew;
    ArcBall *abPtr;

    abName = NULL;
    if (argc == 5) {
	abName = argv[2];
	argc--;
	argv++;
    }
    Tcl_DStringInit(&dString);
    if (abName == NULL) {
	abName = GenerateName(interp, "", "", &dString);
    } else {
	char *p;

	p = strstr(abName, "#auto");
	if (p != NULL) {
	    *p = '\0';
	    abName = GenerateName(interp, abName, p + 5, &dString);
	    *p = '#';
	} else {
	    CONST char *name;
	    Tcl_CmdInfo cmdInfo;
	    Tcl_Namespace *nsPtr;

	    nsPtr = NULL;
	    /* 
	     * Parse the command and put back so that it's in a consistent
	     * format.  
	     *
	     *	t1         <current namespace>::t1
	     *	n1::t1     <current namespace>::n1::t1
	     *	::t1	   ::t1
	     *  ::n1::t1   ::n1::t1
	     */
	    if (Blt_ParseQualifiedName(interp, abName, &nsPtr, &name) 
		!= TCL_OK) {
		Tcl_AppendResult(interp, "can't find namespace in \"", abName,
			 "\"", (char *)NULL);
		return TCL_ERROR;
	    }
	    if (nsPtr == NULL) {
		nsPtr = Tcl_GetCurrentNamespace(interp);
	    }
	    abName = Blt_GetQualifiedName(nsPtr, name, &dString);
	    /* 
	     * Check if the command already exists. 
	     */
	    if (Tcl_GetCommandInfo(interp, (char *)abName, &cmdInfo)) {
		Tcl_AppendResult(interp, "a command \"", abName,
				 "\" already exists", (char *)NULL);
		goto error;
	    }
	} 
    } 
    if (abName != NULL) {
	int w, h;

	if ((Tcl_GetInt(interp, argv[2], &w) != TCL_OK) ||
	    (Tcl_GetInt(interp, argv[3], &h) != TCL_OK)) {
	    goto error;
	}
	abPtr = CreateArcBall(w, h);
	assert(abPtr);
	abPtr->dataPtr = dataPtr;
	abPtr->interp = interp;
	abPtr->cmdToken = Tcl_CreateCommand(interp, (char *)abName, 
		ArcBallInstCmd, abPtr, ArcBallInstDeleteProc);
	abPtr->tablePtr = &dataPtr->arcballTable;
	abPtr->hashPtr = Blt_CreateHashEntry(abPtr->tablePtr, (char *)abPtr,
		&isNew);
	Blt_SetHashValue(abPtr->hashPtr, abPtr);
	Tcl_SetResult(interp, (char *)abName, TCL_VOLATILE);
	Tcl_DStringFree(&dString);
	return TCL_OK;
    }
 error:
    Tcl_DStringFree(&dString);
    return TCL_ERROR;
}

/*
 *----------------------------------------------------------------------
 *
 * ArcBallDestroyOp --
 *
 *---------------------------------------------------------------------- 
 */
/*ARGSUSED*/
static int
ArcBallDestroyOp(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    ArcBallCmdInterpData *dataPtr = clientData;
    int i;

    for (i = 2; i < argc; i++) {
	ArcBall *abPtr;

	abPtr = GetArcBall(dataPtr, interp, argv[i]);
	if (abPtr == NULL) {
	    Tcl_AppendResult(interp, "can't find an arcball named \"", argv[i],
			     "\"", (char *)NULL);
	    return TCL_ERROR;
	}
	Tcl_DeleteCommandFromToken(interp, abPtr->cmdToken);
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ArcBallNamesOp --
 *
 *---------------------------------------------------------------------- 
 */
/*ARGSUSED*/
static int
ArcBallNamesOp(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    ArcBallCmdInterpData *dataPtr = clientData;
    Blt_HashEntry *hPtr;
    Blt_HashSearch cursor;
    Tcl_Obj *listObjPtr;
    Tcl_DString dString;

    Tcl_DStringInit(&dString);
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
    for (hPtr = Blt_FirstHashEntry(&dataPtr->arcballTable, &cursor);
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	ArcBall *abPtr;
	const char *qualName;
	Tcl_Obj *objPtr;

	abPtr = Blt_GetHashValue(hPtr);
	qualName = Blt_GetQualifiedName(
		Blt_GetCommandNamespace(interp, abPtr->cmdToken), 
		Tcl_GetCommandName(interp, abPtr->cmdToken), &dString);
	if (argc == 3) {
	    if (!Tcl_StringMatch(qualName, argv[2])) {
		continue;
	    }
	}
	objPtr = Tcl_NewStringObj(qualName, -1);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
    }
    Tcl_SetObjResult(interp, listObjPtr);
    Tcl_DStringFree(&dString);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ArcBallCmd --
 *
 *---------------------------------------------------------------------- 
 */
static Blt_OpSpec arcBallCmdOps[] =
{
    {"create",  1, (Blt_Op)ArcBallCreateOp, 4, 5, "?name? w h",},
    {"destroy", 1, (Blt_Op)ArcBallDestroyOp, 3, 0, "name...",},
    {"names",   1, (Blt_Op)ArcBallNamesOp, 2, 3, "?pattern?...",},
};

static int nArcBallCmdOps = sizeof(arcBallCmdOps) / sizeof(Blt_OpSpec);

/*ARGSUSED*/
static int
ArcBallCmd(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    Blt_Op proc;

    proc = Blt_GetOp(interp, nArcBallCmdOps, arcBallCmdOps, 
			    BLT_OP_ARG1, argc, argv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    return (*proc) (clientData, interp, argc, argv);
}

/*
 * -----------------------------------------------------------------------
 *
 * ArcballInterpDeleteProc --
 *
 *	This is called when the interpreter hosting the "arcball" command
 *	is deleted.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Removes the hash table managing all arcballs.
 *
 * ------------------------------------------------------------------------
 */
/* ARGSUSED */
static void
ArcBallInterpDeleteProc(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp)
{
    ArcBallCmdInterpData *dataPtr = clientData;

    /* All tree instances should already have been destroyed when
     * their respective Tcl commands were deleted. */
    Blt_DeleteHashTable(&dataPtr->arcballTable);
    Tcl_DeleteAssocData(interp, ARCBALL_THREAD_KEY);
    Blt_Free(dataPtr);
}


/*
 *----------------------------------------------------------------------
 *
 * GetArcBallCmdInterpData --
 *
 *---------------------------------------------------------------------- 
 */
static ArcBallCmdInterpData *
GetArcBallCmdInterpData(Tcl_Interp *interp)
{
    ArcBallCmdInterpData *dataPtr;
    Tcl_InterpDeleteProc *proc;

    dataPtr = (ArcBallCmdInterpData *)
	Tcl_GetAssocData(interp, ARCBALL_THREAD_KEY, &proc);
    if (dataPtr == NULL) {
	dataPtr = Blt_Malloc(sizeof(ArcBallCmdInterpData));
	assert(dataPtr);
	dataPtr->interp = interp;
	Tcl_SetAssocData(interp, ARCBALL_THREAD_KEY, ArcBallInterpDeleteProc,
		 dataPtr);
	Blt_InitHashTable(&dataPtr->arcballTable, BLT_ONE_WORD_KEYS);
    }
    return dataPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_ArcBallCmdInitProc --
 *
 *	This procedure is invoked to initialize the "tree" command.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Creates the new command and adds a new entry into a global Tcl
 *	associative array.
 *
 *---------------------------------------------------------------------------
 */
int
Blt_ArcBallInit(Tcl_Interp *interp)
{
    static Blt_CmdSpec cmdSpec = { 
	"arcball", ArcBallCmd,
    };

    cmdSpec.clientData = GetArcBallCmdInterpData(interp);
    if (Blt_InitCmd(interp, "::blt", &cmdSpec) == NULL) {
	return TCL_ERROR;
    } 
    return TCL_OK;
}

