
/*
 * bltPs.c --
 *
 *      This module implements general PostScript conversion routines.
 *
 * Copyright 1991-1998 Lucent Technologies, Inc.
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

#include "bltInt.h"
#include "bltPs.h"

#include <X11/Xutil.h>
#include <X11/Xatom.h>
#if defined(__STDC__)
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#define PS_MAXPATH	1500	/* Maximum number of components in a PostScript
				 * (level 1) path. */
#define FONT_ITALIC	(1<<0)
#define FONT_BOLD	(1<<1)

/*
 * Possible values for the "weight" field in a TkFontAttributes structure.
 * Weight is a subjective term and depends on what the company that created
 * the font considers bold.
 */

#define TK_FW_NORMAL	0
#define TK_FW_BOLD	1

#define TK_FW_UNKNOWN	-1	/* Unknown weight.  This value is used for
				 * error checking and is never actually stored
				 * in the weight field. */

/*
 * Possible values for the "slant" field in a TkFontAttributes structure.
 */

#define TK_FS_ROMAN	0	
#define TK_FS_ITALIC	1
#define TK_FS_OBLIQUE	2	/* This value is only used when parsing X
				 * font names to determine the closest
				 * match.  It is only stored in the
				 * XLFDAttributes structure, never in the
				 * slant field of the TkFontAttributes. */

#define TK_FS_UNKNOWN	-1	/* Unknown slant.  This value is used for
				 * error checking and is never actually stored
				 * in the slant field. */
static Tcl_Interp *psInterp;

PsToken
Blt_GetPsToken(interp, tkwin)
    Tcl_Interp *interp;
    Tk_Window tkwin;
{
    struct PsTokenStruct *tokenPtr;

    tokenPtr = Blt_Malloc(sizeof(struct PsTokenStruct));
    assert(tokenPtr);

    tokenPtr->fontVarName = tokenPtr->colorVarName = NULL;
    tokenPtr->interp = interp;
    tokenPtr->tkwin = tkwin;
    tokenPtr->colorMode = PS_MODE_COLOR;
    Tcl_DStringInit(&(tokenPtr->dString));
    return tokenPtr;
}

void
Blt_ReleasePsToken(tokenPtr)
    struct PsTokenStruct *tokenPtr;
{
    Tcl_DStringFree(&(tokenPtr->dString));
    Blt_Free(tokenPtr);
}

char *
Blt_PostScriptFromToken(tokenPtr)
    struct PsTokenStruct *tokenPtr;
{
    return Tcl_DStringValue(&(tokenPtr->dString));
}

char *
Blt_ScratchBufferFromToken(tokenPtr)
    struct PsTokenStruct *tokenPtr;
{
    return tokenPtr->scratchArr;
}

Tcl_Interp *
Blt_GetPostScriptInterp(void)
{
    return psInterp;
}

int 
Blt_WantPostScriptWidths(void)
{
    return (psInterp != NULL);
}

void 
Blt_UsePostScriptWidths(tokenPtr, state)
    struct PsTokenStruct *tokenPtr;
    int state;
{
    psInterp = ((state) ? (tokenPtr->interp) : NULL);
}

void
Blt_AppendToPostScript
TCL_VARARGS_DEF(PsToken, arg1)
{
    va_list argList;
    struct PsTokenStruct *tokenPtr;
    char *string;

    tokenPtr = TCL_VARARGS_START(struct PsTokenStruct, arg1, argList);
    for (;;) {
	string = va_arg(argList, char *);
	if (string == NULL) {
	    break;
	}
	Tcl_DStringAppend(&(tokenPtr->dString), string, -1);
    }
}

void
Blt_FormatToPostScript
TCL_VARARGS_DEF(PsToken, arg1)
{
    va_list argList;
    struct PsTokenStruct *tokenPtr;
    char *fmt;

    tokenPtr = TCL_VARARGS_START(struct PsTokenStruct, arg1, argList);
    fmt = va_arg(argList, char *);
    vsprintf(tokenPtr->scratchArr, fmt, argList);
    va_end(argList);
    Tcl_DStringAppend(&(tokenPtr->dString), tokenPtr->scratchArr, -1);
}

#define PICA_MM		2.83464566929
#define PICA_INCH	72.0
#define PICA_CM		28.3464566929

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Ps_GetPica --
 *
 *	Given a string, returns the number of pica corresponding to that
 *	string.
 *
 * Results:
 *	The return value is a standard TCL return result.  If TCL_OK is
 *	returned, then everything went well and the pixel distance is stored
 *	at *doublePtr; otherwise TCL_ERROR is returned and an error message is
 *	left in interp->result.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
int
Blt_Ps_GetPica(
    Tcl_Interp *interp,		/* Use this for error reporting. */
    char *string,		/* String describing a number of pixels. */
    int *picaPtr)		/* Place to store converted result. */
{
    char *p;
    double pica;

    pica = strtod((char *)string, &p);
    if (p == string) {
	goto error;
    }
    if (pica < 0.0) {
	goto error;
    }
    while ((*p != '\0') && isspace(UCHAR(*p))) {
	p++;
    }
    switch (*p) {
	case '\0':
	    break;
	case 'c':
	    pica *= PICA_CM;
	    p++;
	    break;
	case 'i':
	    pica *= PICA_INCH;
	    p++;
	    break;
	case 'm':
	    pica *= PICA_MM;
	    p++;
	    break;
	case 'p':
	    p++;
	    break;
	default:
	    goto error;
    }
    while ((*p != '\0') && isspace(UCHAR(*p))) {
	p++;
    }
    if (*p == '\0') {
	*picaPtr = ROUND(pica);
	return TCL_OK;
    }
 error:
    Tcl_AppendResult(interp, "bad screen distance \"", string, "\"", 
	(char *) NULL);
    return TCL_ERROR;
}

int
Blt_Ps_GetPad(
    Tcl_Interp *interp,		/* Interpreter to send results back to */
    char *string,		/* Pixel value string */
    Blt_Pad *padPtr)
{
    int side1, side2;
    int argc;
    char **argv;

    if (Tcl_SplitList(interp, string, &argc, &argv) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((argc < 1) || (argc > 2)) {
	Tcl_AppendResult(interp, "wrong # elements in padding list",
	    (char *)NULL);
	Blt_Free(argv);
	return TCL_ERROR;
    }
    if (Blt_Ps_GetPica(interp, argv[0], &side1) != TCL_OK) {
	Blt_Free(argv);
	return TCL_ERROR;
    }
    side2 = side1;
    if ((argc > 1) && (Blt_Ps_GetPica(interp, argv[1], &side2) != TCL_OK)) {
	Blt_Free(argv);
	return TCL_ERROR;
    }
    /* Don't update the pad structure until we know both values are okay. */
    Blt_Free(argv);
    padPtr->side1 = side1;
    padPtr->side2 = side2;
    return TCL_OK;
}

int
Blt_FileToPostScript(tokenPtr, fileName)
    struct PsTokenStruct *tokenPtr;
    char *fileName;
{
    Tcl_Channel channel;
    Tcl_DString dString;
    Tcl_Interp *interp;
    char *buf;
    char *libDir;
    int nBytes;

    interp = tokenPtr->interp;
    buf = tokenPtr->scratchArr;

    /*
     * Read in a standard prolog file from file and append it to the
     * PostScript output stored in the Tcl_DString in tokenPtr.
     */

    libDir = (char *)Tcl_GetVar(interp, "blt_library", TCL_GLOBAL_ONLY);
    if (libDir == NULL) {
	Tcl_AppendResult(interp, "couldn't find BLT script library:",
	    "global variable \"blt_library\" doesn't exist", (char *)NULL);
	return TCL_ERROR;
    }
    Tcl_DStringInit(&dString);
    Tcl_DStringAppend(&dString, libDir, -1);
    Tcl_DStringAppend(&dString, "/", -1);
    Tcl_DStringAppend(&dString, fileName, -1);
    fileName = Tcl_DStringValue(&dString);
    Blt_AppendToPostScript(tokenPtr, "\n% including file \"", fileName, 
	"\"\n\n", (char *)NULL);
    channel = Tcl_OpenFileChannel(interp, fileName, "r", 0);
    if (channel == NULL) {
	Tcl_AppendResult(interp, "couldn't open prologue file \"", fileName,
		 "\": ", Tcl_PosixError(interp), (char *)NULL);
	return TCL_ERROR;
    }
    for(;;) {
	nBytes = Tcl_Read(channel, buf, PSTOKEN_BUFSIZ);
	if (nBytes < 0) {
	    Tcl_AppendResult(interp, "error reading prologue file \"", 
		     fileName, "\": ", Tcl_PosixError(interp), 
		     (char *)NULL);
	    Tcl_Close(interp, channel);
	    Tcl_DStringFree(&dString);
	    return TCL_ERROR;
	}
	if (nBytes == 0) {
	    break;
	}
	buf[nBytes] = '\0';
	Blt_AppendToPostScript(tokenPtr, buf, (char *)NULL);
    }
    Tcl_DStringFree(&dString);
    Tcl_Close(interp, channel);
    return TCL_OK;
}


typedef struct {
    const char *alias;
    const char *fontName;
} FamilyMap;

static FamilyMap familyMap[] =
{
    { "Arial",		        "Helvetica"	   },
    { "AvantGarde",             "AvantGarde"       },
    { "Bookman",                "Bookman"          },
    { "Courier New",            "Courier"          },
    { "Courier",                "Courier"          },
    { "Geneva",                 "Helvetica"        },
    { "Helvetica",              "Helvetica"        },
    { "Mathematica1",		"Helvetica"	   },
    { "Monaco",                 "Courier"          },
    { "New Century Schoolbook", "NewCenturySchlbk" },
    { "New York",               "Times"            },
    { "Nimbus Roman No9 L"	"Times"		   },
    { "Nimbus Sans L Condensed","Helvetica"        },
    { "Nimbus Sans L",		"Helvetica"        },
    { "Palatino",               "Palatino"         },
    { "Standard Symbols L",	"Symbol"           },
    { "Swiss 721",              "Helvetica"        },
    { "Symbol",                 "Symbol"           },
    { "Times New Roman",        "Times"            },
    { "Times Roman",            "Times"            },
    { "Times",                  "Times"            },
    { "ZapfChancery",           "ZapfChancery"     },
    { "ZapfDingbats",           "ZapfDingbats"     }
};

static int nFamilyNames = (sizeof(familyMap) / sizeof(FamilyMap));

static const char *
FamilyToPsFamily(const char *family) 
{
    FamilyMap *fp, *fend;

    if (strncasecmp(family, "itc ", 4) == 0) {
	family += 4;
    }
    for (fp = familyMap, fend = fp + nFamilyNames; fp < fend; fp++) {
	if (strcasecmp(fp->alias, family) == 0) {
	    return fp->fontName;
	}
    }
    return NULL;
}

void
Blt_Ps_FontName(const char *family, int flags, Tcl_DString *resultPtr)
{
    const char *familyName, *weightName, *slantName;
    int len;

    len = Tcl_DStringLength(resultPtr);

    familyName = FamilyToPsFamily(family);
    if (familyName == NULL) {
	Tcl_UniChar ch;
	char *src, *dest;
	int upper;

	/*
	 * Inline, capitalize the first letter of each word, lowercase the
	 * rest of the letters in each word, and then take out the spaces
	 * between the words.  This may make the DString shorter, which is
	 * safe to do.
	 */
	Tcl_DStringAppend(resultPtr, family, -1);
	src = dest = Tcl_DStringValue(resultPtr) + len;
	upper = TRUE;
	while (*src != '\0') {
	    while (isspace(*src)) { /* INTL: ISO space */
		src++;
		upper = TRUE;
	    }
	    src += Tcl_UtfToUniChar(src, &ch);
	    if (upper) {
		ch = Tcl_UniCharToUpper(ch);
		upper = FALSE;
	    } else {
	        ch = Tcl_UniCharToLower(ch);
	    }
	    dest += Tcl_UniCharToUtf(ch, dest);
	}
	*dest = '\0';
	Tcl_DStringSetLength(resultPtr, dest - Tcl_DStringValue(resultPtr));
	familyName = Tcl_DStringValue(resultPtr) + len;
    }
    if (familyName != Tcl_DStringValue(resultPtr) + len) {
	Tcl_DStringAppend(resultPtr, familyName, -1);
	familyName = Tcl_DStringValue(resultPtr) + len;
    }
    if (strcasecmp(familyName, "NewCenturySchoolbook") == 0) {
	Tcl_DStringSetLength(resultPtr, len);
	Tcl_DStringAppend(resultPtr, "NewCenturySchlbk", -1);
	familyName = Tcl_DStringValue(resultPtr) + len;
    }

    /* Get the string to use for the weight. */
    weightName = NULL;
    if (flags & FONT_BOLD) {
	if ((strcmp(familyName, "Bookman") == 0) || 
	    (strcmp(familyName, "AvantGarde") == 0)) {
	    weightName = "Demi";
	} else {
	    weightName = "Bold";
	}
    } else {
	if (strcmp(familyName, "Bookman") == 0) {
	    weightName = "Light";
	} else if (strcmp(familyName, "AvantGarde") == 0) {
	    weightName = "Book";
	} else if (strcmp(familyName, "ZapfChancery") == 0) {
	    weightName = "Medium";
	}
    }

    /* Get the string to use for the slant. */
    slantName = NULL;
    if (flags & FONT_ITALIC) {
	if ((strcmp(familyName, "Helvetica") == 0) || 
	    (strcmp(familyName, "Courier") == 0) || 
	    (strcmp(familyName, "AvantGarde") == 0)) {
	    slantName = "Oblique";
	} else {
	    slantName = "Italic";
	}
    }

    /*
     * The string "Roman" needs to be added to some fonts that are not bold
     * and not italic.
     */
    if ((slantName == NULL) && (weightName == NULL)) {
	if ((strcmp(familyName, "Times") == 0) || 
	    (strcmp(familyName, "NewCenturySchlbk") == 0) || 
	    (strcmp(familyName, "Palatino") == 0)) {
	    Tcl_DStringAppend(resultPtr, "-Roman", -1);
	}
    } else {
	Tcl_DStringAppend(resultPtr, "-", -1);
	if (weightName != NULL) {
	    Tcl_DStringAppend(resultPtr, weightName, -1);
	}
	if (slantName != NULL) {
	    Tcl_DStringAppend(resultPtr, slantName, -1);
	}
    }
}

static int
PostscriptFontName(Tk_Font font, Tcl_DString *resultPtr) 
{
    TkFont *tkFontPtr;
    unsigned int flags;

    tkFontPtr = (TkFont *)font;
    flags = 0;
    if (tkFontPtr->fa.slant != TK_FS_ROMAN) {
	flags |= FONT_ITALIC;
    }
    if (tkFontPtr->fa.weight != TK_FW_NORMAL) {
	flags |= FONT_BOLD;
    }
    Blt_Ps_FontName(tkFontPtr->fa.family, flags, resultPtr);
    return tkFontPtr->fa.pointsize;
}

/*
 *----------------------------------------------------------------------
 *
 * XColorToPostScript --
 *
 *	Convert the a XColor (from its RGB values) to a PostScript
 *	command.  If a Tk color map variable exists, it will be
 *	consulted for a PostScript translation based upon the color
 *	name.
 *
 *	Maps an X color intensity (0 to 2^16-1) to a floating point
 *      value [0..1].  Many versions of Tk don't properly handle the 
 *	the lower 8 bits of the color intensity, so we can only 
 *	consider the upper 8 bits. 
 *
 * Results:
 *	The string representing the color mode is returned.
 *
 *----------------------------------------------------------------------
 */
static void
XColorToPostScript(tokenPtr, colorPtr)
    struct PsTokenStruct *tokenPtr;
    XColor *colorPtr;		/* Color value to be converted */
{
    /* 
     * Shift off the lower byte before dividing because some versions
     * of Tk don't fill the lower byte correctly.  
     */
    Blt_FormatToPostScript(tokenPtr, "%g %g %g",
	((double)(colorPtr->red >> 8) / 255.0),
	((double)(colorPtr->green >> 8) / 255.0),
	((double)(colorPtr->blue >> 8) / 255.0));
}

void
Blt_BackgroundToPostScript(tokenPtr, colorPtr)
    struct PsTokenStruct *tokenPtr;
    XColor *colorPtr;
{
    /* If the color name exists in Tcl array variable, use that translation */
    if (tokenPtr->colorVarName != NULL) {
	CONST char *psColor;

	psColor = Tcl_GetVar2(tokenPtr->interp, tokenPtr->colorVarName,
	    Tk_NameOfColor(colorPtr), 0);
	if (psColor != NULL) {
	    Blt_AppendToPostScript(tokenPtr, " ", psColor, "\n", (char *)NULL);
	    return;
	}
    }
    XColorToPostScript(tokenPtr, colorPtr);
    Blt_AppendToPostScript(tokenPtr, " SetBgColor\n", (char *)NULL);
}

void
Blt_ForegroundToPostScript(tokenPtr, colorPtr)
    struct PsTokenStruct *tokenPtr;
    XColor *colorPtr;
{
    /* If the color name exists in Tcl array variable, use that translation */
    if (tokenPtr->colorVarName != NULL) {
	CONST char *psColor;

	psColor = Tcl_GetVar2(tokenPtr->interp, tokenPtr->colorVarName,
	    Tk_NameOfColor(colorPtr), 0);
	if (psColor != NULL) {
	    Blt_AppendToPostScript(tokenPtr, " ", psColor, "\n", (char *)NULL);
	    return;
	}
    }
    XColorToPostScript(tokenPtr, colorPtr);
    Blt_AppendToPostScript(tokenPtr, " SetFgColor\n", (char *)NULL);
}

/*
 *----------------------------------------------------------------------
 *
 * ReverseBits --
 *
 *	Convert a byte from a X image into PostScript image order.
 *	This requires not only the nybbles to be reversed but also
 *	their bit values.
 *
 * Results:
 *	The converted byte is returned.
 *
 *----------------------------------------------------------------------
 */
INLINE static unsigned char
ReverseBits(byte)
    register unsigned char byte;
{
    byte = ((byte >> 1) & 0x55) | ((byte << 1) & 0xaa);
    byte = ((byte >> 2) & 0x33) | ((byte << 2) & 0xcc);
    byte = ((byte >> 4) & 0x0f) | ((byte << 4) & 0xf0);
    return byte;
}

/*
 *----------------------------------------------------------------------
 *
 * ByteToHex --
 *
 *	Convert a byte to its ASCII hexidecimal equivalent.
 *
 * Results:
 *	The converted 2 ASCII character string is returned.
 *
 *----------------------------------------------------------------------
 */
INLINE static void
ByteToHex(byte, string)
    register unsigned char byte;
    char *string;
{
    static char hexDigits[] = "0123456789ABCDEF";

    string[0] = hexDigits[byte >> 4];
    string[1] = hexDigits[byte & 0x0F];
}

#ifdef WIN32
/*
 * -------------------------------------------------------------------------
 *
 * Blt_BitmapDataToPostScript --
 *
 *      Output a PostScript image string of the given bitmap image.
 *      It is assumed the image is one bit deep and a zero value
 *      indicates an off-pixel.  To convert to PostScript, the bits
 *      need to be reversed from the X11 image order.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *      The PostScript image string is appended.
 *
 * -------------------------------------------------------------------------
 */
void
Blt_BitmapDataToPostScript(
    struct PsTokenStruct *tokenPtr,
    Display *display,
    Pixmap bitmap,
    int width, int height)
{
    register unsigned char byte;
    register int x, y, bitPos;
    unsigned long pixel;
    int byteCount;
    char string[10];
    unsigned char *srcBits, *srcPtr;
    int bytesPerRow;

    srcBits = Blt_GetBitmapData(display, bitmap, width, height, &bytesPerRow);
    if (srcBits == NULL) {
        OutputDebugString("Can't get bitmap data");
	return;
    }
    Blt_AppendToPostScript(tokenPtr, "\t<", (char *)NULL);
    byteCount = bitPos = 0;	/* Suppress compiler warning */
    for (y = height - 1; y >= 0; y--) {
	srcPtr = srcBits + (bytesPerRow * y);
	byte = 0;
	for (x = 0; x < width; x++) {
	    bitPos = x % 8;
	    pixel = (*srcPtr & (0x80 >> bitPos));
	    if (pixel) {
		byte |= (unsigned char)(1 << bitPos);
	    }
	    if (bitPos == 7) {
		byte = ReverseBits(byte);
		ByteToHex(byte, string);
		string[2] = '\0';
		byteCount++;
		srcPtr++;
		byte = 0;
		if (byteCount >= 30) {
		    string[2] = '\n';
		    string[3] = '\t';
		    string[4] = '\0';
		    byteCount = 0;
		}
		Blt_AppendToPostScript(tokenPtr, string, (char *)NULL);
	    }
	}			/* x */
	if (bitPos != 7) {
	    byte = ReverseBits(byte);
	    ByteToHex(byte, string);
	    string[2] = '\0';
	    Blt_AppendToPostScript(tokenPtr, string, (char *)NULL);
	    byteCount++;
	}
    }				/* y */
    Blt_Free(srcBits);
    Blt_AppendToPostScript(tokenPtr, ">\n", (char *)NULL);
}

#else

/*
 * -------------------------------------------------------------------------
 *
 * Blt_BitmapDataToPostScript --
 *
 *      Output a PostScript image string of the given bitmap image.
 *      It is assumed the image is one bit deep and a zero value
 *      indicates an off-pixel.  To convert to PostScript, the bits
 *      need to be reversed from the X11 image order.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *      The PostScript image string is appended to interp->result.
 *
 * -------------------------------------------------------------------------
 */
void
Blt_BitmapDataToPostScript(tokenPtr, display, bitmap, width, height)
    struct PsTokenStruct *tokenPtr;
    Display *display;
    Pixmap bitmap;
    int width, height;
{
    register unsigned char byte = 0;
    register int x, y, bitPos;
    unsigned long pixel;
    XImage *imagePtr;
    int byteCount;
    char string[10];

    imagePtr = XGetImage(display, bitmap, 0, 0, width, height, 1, ZPixmap);
    Blt_AppendToPostScript(tokenPtr, "\t<", (char *)NULL);
    byteCount = bitPos = 0;	/* Suppress compiler warning */
    for (y = 0; y < height; y++) {
	byte = 0;
	for (x = 0; x < width; x++) {
	    pixel = XGetPixel(imagePtr, x, y);
	    bitPos = x % 8;
	    byte |= (unsigned char)(pixel << bitPos);
	    if (bitPos == 7) {
		byte = ReverseBits(byte);
		ByteToHex(byte, string);
		string[2] = '\0';
		byteCount++;
		byte = 0;
		if (byteCount >= 30) {
		    string[2] = '\n';
		    string[3] = '\t';
		    string[4] = '\0';
		    byteCount = 0;
		}
		Blt_AppendToPostScript(tokenPtr, string, (char *)NULL);
	    }
	}			/* x */
	if (bitPos != 7) {
	    byte = ReverseBits(byte);
	    ByteToHex(byte, string);
	    string[2] = '\0';
	    Blt_AppendToPostScript(tokenPtr, string, (char *)NULL);
	    byteCount++;
	}
    }				/* y */
    Blt_AppendToPostScript(tokenPtr, ">\n", (char *)NULL);
    XDestroyImage(imagePtr);
}

#endif /* WIN32 */

/*
 *----------------------------------------------------------------------
 *
 * Blt_ColorImageToPsData --
 *
 *	Converts a color image to PostScript RGB (3 components)
 *	or Greyscale (1 component) output.  With 3 components, we
 *	assume the "colorimage" operator is available.
 *
 *	Note that the image converted from bottom to top, to conform
 *	to the PostScript coordinate system.
 *
 * Results:
 *	The PostScript data comprising the color image is written
 *	into the dynamic string.
 *
 *----------------------------------------------------------------------
 */
int
Blt_ColorImageToPsData(image, nComponents, resultPtr, prefix)
    Blt_ColorImage image;
    int nComponents;
    Tcl_DString *resultPtr;
    char *prefix;
{
    char string[10];
    register int count;
    register int x, y;
    register Pix32 *pixelPtr;
    unsigned char byte;
    int width, height;
    int offset;
    int nLines;
    width = Blt_ColorImageWidth(image);
    height = Blt_ColorImageHeight(image);

    nLines = 0;
    count = 0;
    offset = (height - 1) * width;
    if (nComponents == 3) {
	for (y = (height - 1); y >= 0; y--) {
	    pixelPtr = Blt_ColorImageBits(image) + offset;
	    for (x = 0; x < width; x++, pixelPtr++) {
		if (count == 0) {
		    Tcl_DStringAppend(resultPtr, prefix, -1);
		    Tcl_DStringAppend(resultPtr, " ", -1);
		}
		count += 6;
		ByteToHex(pixelPtr->Red, string);
		ByteToHex(pixelPtr->Green, string + 2);
		ByteToHex(pixelPtr->Blue, string + 4);
		string[6] = '\0';
		if (count >= 60) {
		    string[6] = '\n';
		    string[7] = '\0';
		    count = 0;
		    nLines++;
		}
		Tcl_DStringAppend(resultPtr, string, -1);
	    }
	    offset -= width;
	}
    } else if (nComponents == 1) {
	for (y = (height - 1); y >= 0; y--) {
	    pixelPtr = Blt_ColorImageBits(image) + offset;
	    for (x = 0; x < width; x++, pixelPtr++) {
		if (count == 0) {
		    Tcl_DStringAppend(resultPtr, prefix, -1);
		    Tcl_DStringAppend(resultPtr, " ", -1);
		}
		count += 2;
		byte = ~(pixelPtr->Red);
		ByteToHex(byte, string);
		string[2] = '\0';
		if (count >= 60) {
		    string[2] = '\n';
		    string[3] = '\0';
		    count = 0;
		    nLines++;
		}
		Tcl_DStringAppend(resultPtr, string, -1);
	    }
	    offset -= width;
	}
    }
    if (count != 0) {
	Tcl_DStringAppend(resultPtr, "\n", -1);
	nLines++;
    }
    return nLines;
}

/*
 *----------------------------------------------------------------------
 *
 * NameOfAtom --
 *
 *	Wrapper routine for Tk_GetAtomName.  Returns NULL instead of
 *	"?bad atom?" if the atom can't be found.
 *
 * Results:
 *	The name of the atom is returned if found. Otherwise NULL.
 *
 *----------------------------------------------------------------------
 */
static char *
NameOfAtom(tkwin, atom)
    Tk_Window tkwin;
    Atom atom;
{
    char *result;

    result = Tk_GetAtomName(tkwin, atom);
    if ((result[0] == '?') && (strcmp(result, "?bad atom?") == 0)) {
	return NULL;
    }
    return result;
}


typedef struct {
    char *alias;
    char *fontName;
} FontMap;

static FontMap psFontMap[] =
{
    {"Arial", "Helvetica",},
    {"AvantGarde", "AvantGarde",},
    {"Courier New", "Courier",},
    {"Courier", "Courier",},
    {"Geneva", "Helvetica",},
    {"Helvetica", "Helvetica",},
    {"Monaco", "Courier",},
    {"New Century Schoolbook", "NewCenturySchlbk",},
    {"New York", "Times",},
    {"Palatino", "Palatino",},
    {"Swiss 721", "Helvetica",},
    {"Symbol", "Symbol",},
    {"Times New Roman", "Times",},
    {"Times Roman", "Times",},
    {"Times", "Times",},
    {"ZapfChancery", "ZapfChancery",},
    {"ZapfDingbats", "ZapfDingbats",},
};

static int nFontNames = (sizeof(psFontMap) / sizeof(FontMap));

#ifndef  WIN32
/*
 * -----------------------------------------------------------------
 *
 * XFontStructToPostScript --
 *
 *      Map X11 font to a PostScript font. Currently, only fonts whose
 *      FOUNDRY property are "Adobe" are converted. Simply gets the
 *      XA_FULL_NAME and XA_FAMILY properties and pieces together a
 *      PostScript fontname.
 *
 * Results:
 *      Returns the mapped PostScript font name if one is possible.
 *	Otherwise returns NULL.
 *
 * -----------------------------------------------------------------
 */
static char *
XFontStructToPostScript(tkwin, fsPtr)
    Tk_Window tkwin;			/* Window to query for atoms */
    XFontStruct *fsPtr;			/* Font structure to map to name */
{
    Atom atom;
    unsigned long retval;
    char *fullName, *family, *foundry;
    register char *src, *dest;
    int familyLen;
    char *start;
    static char string[200];	/* What size? */

    fullName = family = foundry = NULL;
    if (XGetFontProperty(fsPtr, XA_FULL_NAME, &atom)) {
	fullName = NameOfAtom(tkwin, atom);
    }
    atom = Tk_InternAtom(tkwin, "FOUNDRY");
    if (XGetFontProperty(fsPtr, atom, &atom)) {
	foundry = NameOfAtom(tkwin, atom);
    }	
    if (XGetFontProperty(fsPtr, XA_FAMILY_NAME, &atom)) {
	family = NameOfAtom(tkwin, atom);
    }	
    /*
     * Try to map the font only if the foundry is Adobe
     */
    if ((foundry == NULL) || (family == NULL) || (fullName == NULL)) {
	return NULL;
    }
    src = NULL;
    familyLen = strlen(family);
    if (strncasecmp(fullName, family, familyLen) == 0) {
	src = fullName + familyLen;
    }
    if (strcmp(foundry, "Adobe") != 0) {
	register int i;

	if (strncasecmp(family, "itc ", 4) == 0) {
	    family += 4;	/* Throw out the "itc" prefix */
	}
	for (i = 0; i < nFontNames; i++) {
	    if (strcasecmp(family, psFontMap[i].alias) == 0) {
		family = psFontMap[i].fontName;
	    }
	}
	if (i == nFontNames) {
	    family = "Helvetica";	/* Default to a known font */
	}
    }
    /*
     * PostScript font name is in the form <family>-<type face>
     */
    sprintf(string, "%s-", family);
    dest = start = string + strlen(string);

    /*
     * Append the type face (part of the full name trailing the family name)
     * to the the PostScript font name, removing any spaces or dashes
     *
     * ex. " Bold Italic" ==> "BoldItalic"
     */
    if (src != NULL) {
	while (*src != '\0') {
	    if ((*src != ' ') && (*src != '-')) {
		*dest++ = *src;
	    }
	    src++;
	}
    }
    if (dest == start) {
	--dest;			/* Remove '-' to leave just the family name */
    }
    *dest = '\0';		/* Make a valid string */
    return string;
}

#endif /* !WIN32 */


/*
 * -------------------------------------------------------------------
 * Routines to convert X drawing functions to PostScript commands.
 * -------------------------------------------------------------------
 */
void
Blt_ClearBackgroundToPostScript(tokenPtr)
    struct PsTokenStruct *tokenPtr;
{
    Blt_AppendToPostScript(tokenPtr, 
	" 1.0 1.0 1.0 SetBgColor\n", 
	(char *)NULL);
}

void
Blt_CapStyleToPostScript(tokenPtr, capStyle)
    struct PsTokenStruct *tokenPtr;
    int capStyle;
{
    /*
     * X11:not last = 0, butt = 1, round = 2, projecting = 3
     * PS: butt = 0, round = 1, projecting = 2
     */
    if (capStyle > 0) {
	capStyle--;
    }
    Blt_FormatToPostScript(tokenPtr, 
	"%d setlinecap\n", 
	capStyle);
}

void
Blt_JoinStyleToPostScript(tokenPtr, joinStyle)
    struct PsTokenStruct *tokenPtr;
    int joinStyle;
{
    /*
     * miter = 0, round = 1, bevel = 2
     */
    Blt_FormatToPostScript(tokenPtr, 
	"%d setlinejoin\n", 
	joinStyle);
}

void
Blt_LineWidthToPostScript(tokenPtr, lineWidth)
    struct PsTokenStruct *tokenPtr;
    int lineWidth;
{
    if (lineWidth < 1) {
	lineWidth = 1;
    }
    Blt_FormatToPostScript(tokenPtr, 
	"%d setlinewidth\n", 
	lineWidth);
}

void
Blt_LineDashesToPostScript(tokenPtr, dashesPtr)
    struct PsTokenStruct *tokenPtr;
    Blt_Dashes *dashesPtr;
{

    Blt_AppendToPostScript(tokenPtr, "[ ", (char *)NULL);
    if (dashesPtr != NULL) {
	unsigned char *p;

	for (p = dashesPtr->values; *p != 0; p++) {
	    Blt_FormatToPostScript(tokenPtr, " %d", *p);
	}
    }
    Blt_AppendToPostScript(tokenPtr, "] 0 setdash\n", (char *)NULL);
}

void
Blt_LineAttributesToPostScript(tokenPtr, colorPtr, lineWidth, dashesPtr,
    capStyle, joinStyle)
    struct PsTokenStruct *tokenPtr;
    XColor *colorPtr;
    int lineWidth;
    Blt_Dashes *dashesPtr;
    int capStyle, joinStyle;
{
    Blt_JoinStyleToPostScript(tokenPtr, joinStyle);
    Blt_CapStyleToPostScript(tokenPtr, capStyle);
    Blt_ForegroundToPostScript(tokenPtr, colorPtr);
    Blt_LineWidthToPostScript(tokenPtr, lineWidth);
    Blt_LineDashesToPostScript(tokenPtr, dashesPtr);
    Blt_AppendToPostScript(tokenPtr, "/DashesProc {} def\n", (char *)NULL);
}

void
Blt_RectangleToPostScript(tokenPtr, x, y, width, height)
    struct PsTokenStruct *tokenPtr;
    double x, y;
    int width, height;
{
    Blt_FormatToPostScript(tokenPtr, 
	"%g %g %d %d Box fill\n\n", 
	x, y, width, height);
}

void
Blt_RegionToPostScript(tokenPtr, x, y, width, height)
    struct PsTokenStruct *tokenPtr;
    double x, y;
    int width, height;
{
    Blt_FormatToPostScript(tokenPtr, "%g %g %d %d Box\n\n", 
			   x, y, width, height);
}

void
Blt_PathToPostScript(tokenPtr, screenPts, nScreenPts)
    struct PsTokenStruct *tokenPtr;
    register Point2D *screenPts;
    int nScreenPts;
{
    register Point2D *pointPtr, *endPtr;

    pointPtr = screenPts;
    Blt_FormatToPostScript(tokenPtr, "newpath %g %g moveto\n", 
	pointPtr->x, pointPtr->y);
    pointPtr++;
    endPtr = screenPts + nScreenPts;
    while (pointPtr < endPtr) {
	Blt_FormatToPostScript(tokenPtr, "%g %g lineto\n",
		pointPtr->x, pointPtr->y);
	pointPtr++;
    }
}

void
Blt_PolygonToPostScript(tokenPtr, screenPts, nScreenPts)
    struct PsTokenStruct *tokenPtr;
    Point2D *screenPts;
    int nScreenPts;
{
    Blt_PathToPostScript(tokenPtr, screenPts, nScreenPts);
    Blt_FormatToPostScript(tokenPtr, "%g %g ", screenPts[0].x, screenPts[0].y);
    Blt_AppendToPostScript(tokenPtr, " lineto closepath Fill\n", (char *)NULL);
}

void
Blt_SegmentsToPostScript(tokenPtr, segPtr, nSegments)
    struct PsTokenStruct *tokenPtr;
    register XSegment *segPtr;
    int nSegments;
{
    register int i;

    for (i = 0; i < nSegments; i++, segPtr++) {
	Blt_FormatToPostScript(tokenPtr, "%d %d moveto\n", 
			       segPtr->x1, segPtr->y1);
	Blt_FormatToPostScript(tokenPtr, " %d %d lineto\n", 
			       segPtr->x2, segPtr->y2);
	Blt_AppendToPostScript(tokenPtr, "DashesProc stroke\n", (char *)NULL);
    }
}


void
Blt_RectanglesToPostScript(tokenPtr, rectArr, nRects)
    struct PsTokenStruct *tokenPtr;
    XRectangle rectArr[];
    int nRects;
{
    register int i;

    for (i = 0; i < nRects; i++) {
	Blt_RectangleToPostScript(tokenPtr, 
		  (double)rectArr[i].x, (double)rectArr[i].y, 
		  (int)rectArr[i].width, (int)rectArr[i].height);
    }
}

#ifndef TK_RELIEF_SOLID
#define TK_RELIEF_SOLID		-1	/* Set the an impossible value. */
#endif /* TK_RELIEF_SOLID */

void
Blt_Draw3DRectangleToPostScript(tokenPtr, border, x, y, width, height,
    borderWidth, relief)
    struct PsTokenStruct *tokenPtr;
    Tk_3DBorder border;		/* Token for border to draw. */
    double x, y;		/* Coordinates of rectangle */
    int width, height;		/* Region to be drawn. */
    int borderWidth;		/* Desired width for border, in pixels. */
    int relief;			/* Should be either TK_RELIEF_RAISED or
                                 * TK_RELIEF_SUNKEN;  indicates position of
                                 * interior of window relative to exterior. */
{
    TkBorder *borderPtr = (TkBorder *) border;
    XColor lightColor, darkColor;
    XColor *lightColorPtr, *darkColorPtr;
    XColor *topColor, *bottomColor;
    Point2D points[7];
    int twiceWidth = (borderWidth * 2);

    if ((width < twiceWidth) || (height < twiceWidth)) {
	return;
    }
    if (borderWidth <= 0) {
	return;
    }
    if (relief == TK_RELIEF_SOLID) {
	if (borderWidth > 1) {
	    x += borderWidth / 2;
	    y += borderWidth / 2;
	    width -= borderWidth;
	    height -= borderWidth;
	}
	darkColor.red = darkColor.blue = darkColor.green = 0x00;
	Blt_BackgroundToPostScript(tokenPtr, &darkColor);
	Blt_LineWidthToPostScript(tokenPtr, borderWidth);
	Blt_FormatToPostScript(tokenPtr, "%g %g %d %d Box stroke\n\n", 
			       x, y, width - 1, height - 1);
	return;
    }
    if ((relief == TK_RELIEF_SOLID) ||
	(borderPtr->lightColor == NULL) || (borderPtr->darkColor == NULL)) {
	if (relief == TK_RELIEF_SOLID) {
	    darkColor.red = darkColor.blue = darkColor.green = 0x00;
	    lightColor.red = lightColor.blue = lightColor.green = 0x00;
	    relief = TK_RELIEF_SUNKEN;
	} else {
	    Screen *screenPtr;

	    lightColor = *borderPtr->bgColor;
	    screenPtr = Tk_Screen(tokenPtr->tkwin);
	    if (lightColor.pixel == WhitePixelOfScreen(screenPtr)) {
		darkColor.red = darkColor.blue = darkColor.green = 0x00;
	    } else {
		darkColor.red = darkColor.blue = darkColor.green = 0xFF;
	    }
	}
	lightColorPtr = &lightColor;
	darkColorPtr = &darkColor;
    } else {
	lightColorPtr = borderPtr->lightColor;
	darkColorPtr = borderPtr->darkColor;
    }


    /*
     * Handle grooves and ridges with recursive calls.
     */

    if ((relief == TK_RELIEF_GROOVE) || (relief == TK_RELIEF_RIDGE)) {
	int halfWidth, insideOffset;

	halfWidth = borderWidth / 2;
	insideOffset = borderWidth - halfWidth;
	Blt_Draw3DRectangleToPostScript(tokenPtr, border, (double)x, (double)y,
	    width, height, halfWidth, 
	    (relief == TK_RELIEF_GROOVE) ? TK_RELIEF_SUNKEN : TK_RELIEF_RAISED);
	Blt_Draw3DRectangleToPostScript(tokenPtr, border, 
  	    (double)(x + insideOffset), (double)(y + insideOffset), 
	    width - insideOffset * 2, height - insideOffset * 2, halfWidth,
	    (relief == TK_RELIEF_GROOVE) ? TK_RELIEF_RAISED : TK_RELIEF_SUNKEN);
	return;
    }
    if (relief == TK_RELIEF_RAISED) {
	topColor = lightColorPtr;
	bottomColor = darkColorPtr;
    } else if (relief == TK_RELIEF_SUNKEN) {
	topColor = darkColorPtr;
	bottomColor = lightColorPtr;
    } else {
	topColor = bottomColor = borderPtr->bgColor;
    }
    Blt_BackgroundToPostScript(tokenPtr, bottomColor);
    Blt_RectangleToPostScript(tokenPtr, x, y + height - borderWidth, width,
	borderWidth);
    Blt_RectangleToPostScript(tokenPtr, x + width - borderWidth, y,
	borderWidth, height);
    points[0].x = points[1].x = points[6].x = x;
    points[0].y = points[6].y = y + height;
    points[1].y = points[2].y = y;
    points[2].x = x + width;
    points[3].x = x + width - borderWidth;
    points[3].y = points[4].y = y + borderWidth;
    points[4].x = points[5].x = x + borderWidth;
    points[5].y = y + height - borderWidth;
    if (relief != TK_RELIEF_FLAT) {
	Blt_BackgroundToPostScript(tokenPtr, topColor);
    }
    Blt_PolygonToPostScript(tokenPtr, points, 7);
}

void
Blt_Fill3DRectangleToPostScript(tokenPtr, border, x, y, width, height,
    borderWidth, relief)
    struct PsTokenStruct *tokenPtr;
    Tk_3DBorder border;		/* Token for border to draw. */
    double x, y;		/* Coordinates of top-left of border area */
    int width, height;		/* Dimension of border to be drawn. */
    int borderWidth;		/* Desired width for border, in pixels. */
    int relief;			/* Should be either TK_RELIEF_RAISED or
                                 * TK_RELIEF_SUNKEN;  indicates position of
                                 * interior of window relative to exterior. */
{
    TkBorder *borderPtr = (TkBorder *) border;

    /*
     * I'm assuming that the rectangle is to be drawn as a background.
     * Setting the pen color as foreground or background only affects
     * the plot when the colormode option is "monochrome".
     */
    Blt_BackgroundToPostScript(tokenPtr, borderPtr->bgColor);
    Blt_RectangleToPostScript(tokenPtr, x, y, width, height);
    Blt_Draw3DRectangleToPostScript(tokenPtr, border, x, y, width, height,
	borderWidth, relief);
}

void
Blt_StippleToPostScript(tokenPtr, display, bitmap)
    struct PsTokenStruct *tokenPtr;
    Display *display;
    Pixmap bitmap;
{
    int width, height;

    Tk_SizeOfBitmap(display, bitmap, &width, &height);
    Blt_FormatToPostScript(tokenPtr, 
	"gsave\n  clip\n  %d %d\n", 
	width, height);
    Blt_BitmapDataToPostScript(tokenPtr, display, bitmap, width, height);
    Blt_AppendToPostScript(tokenPtr, 
	"  StippleFill\ngrestore\n", 
	(char *)NULL);
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_ColorImageToPostScript --
 *
 *      Translates a color image into 3 component RGB PostScript output.
 *	Uses PS Language Level 2 operator "colorimage".
 *
 * Results:
 *      The dynamic string will contain the PostScript output.
 *
 *----------------------------------------------------------------------
 */
void
Blt_ColorImageToPostScript(tokenPtr, image, x, y)
    struct PsTokenStruct *tokenPtr;
    Blt_ColorImage image;
    double x, y;
{
    int width, height;
    int tmpSize;

    width = Blt_ColorImageWidth(image);
    height = Blt_ColorImageHeight(image);

    tmpSize = width;
    if (tokenPtr->colorMode == PS_MODE_COLOR) {
	tmpSize *= 3;
    }
    Blt_FormatToPostScript(tokenPtr, "\n/tmpStr %d string def\n", tmpSize);
    Blt_AppendToPostScript(tokenPtr, "gsave\n", (char *)NULL);
    Blt_FormatToPostScript(tokenPtr, "  %g %g translate\n", x, y);
    Blt_FormatToPostScript(tokenPtr, "  %d %d scale\n", width, height);
    Blt_FormatToPostScript(tokenPtr, "  %d %d 8\n", width, height);
    Blt_FormatToPostScript(tokenPtr, "  [%d 0 0 %d 0 %d] ", width, -height,
	height);
    Blt_AppendToPostScript(tokenPtr, 
	"{\n    currentfile tmpStr readhexstring pop\n  } ",
	(char *)NULL);
    if (tokenPtr->colorMode != PS_MODE_COLOR) {
	Blt_AppendToPostScript(tokenPtr, "image\n", (char *)NULL);
	Blt_ColorImageToGreyscale(image);
	Blt_ColorImageToPsData(image, 1, &(tokenPtr->dString), " ");
    } else {
	Blt_AppendToPostScript(tokenPtr, 
		"false 3 colorimage\n", 
		(char *)NULL);
	Blt_ColorImageToPsData(image, 3, &(tokenPtr->dString), " ");
    }
    Blt_AppendToPostScript(tokenPtr, 
	"\ngrestore\n\n", 
	(char *)NULL);
}

/*
 *----------------------------------------------------------------------
 *
 * Blt_WindowToPostScript --
 *
 *      Converts a Tk window to PostScript.  If the window could not
 *	be "snapped", then a grey rectangle is drawn in its place.
 *
 * Results:
 *      None.
 *
 *----------------------------------------------------------------------
 */
void
Blt_WindowToPostScript(tokenPtr, tkwin, x, y)
    struct PsTokenStruct *tokenPtr;
    Tk_Window tkwin;
    double x, y;
{
    Blt_ColorImage image;
    int width, height;

    width = Tk_Width(tkwin);
    height = Tk_Height(tkwin);
    image = Blt_DrawableToColorImage(tkwin, Tk_WindowId(tkwin), 0, 0, width, 
	height, GAMMA);
    if (image == NULL) {
	/* Can't grab window image so paint the window area grey */
	Blt_AppendToPostScript(tokenPtr, "% Can't grab window \"",
	    Tk_PathName(tkwin), "\"\n", (char *)NULL);
	Blt_AppendToPostScript(tokenPtr, "0.5 0.5 0.5 SetBgColor\n",
	    (char *)NULL);
	Blt_RectangleToPostScript(tokenPtr, x, y, width, height);
	return;
    }
    Blt_ColorImageToPostScript(tokenPtr, image, x, y);
    Blt_FreeColorImage(image);
}

/*
 * -------------------------------------------------------------------------
 *
 * Blt_PhotoToPostScript --
 *
 *      Output a PostScript image string of the given photo image.
 *	The photo is first converted into a color image and then
 *	translated into PostScript.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *      The PostScript output representing the photo is appended to
 *	the tokenPtr's dynamic string.
 *
 * -------------------------------------------------------------------------
 */
void
Blt_PhotoToPostScript(tokenPtr, photo, x, y)
    struct PsTokenStruct *tokenPtr;
    Tk_PhotoHandle photo;
    double x, y;		/* Origin of photo image */
{
    Blt_ColorImage image;

    image = Blt_PhotoToColorImage(photo);
    Blt_ColorImageToPostScript(tokenPtr, image, x, y);
    Blt_FreeColorImage(image);
}

/*
 * -----------------------------------------------------------------
 *
 * Blt_FontToPostScript --
 *
 *      Map the Tk font to a PostScript font and point size.
 *
 *	If a Tcl array variable was specified, each element should be
 *	indexed by the X11 font name and contain a list of 1-2
 *	elements; the PostScript font name and the desired point size.
 *	The point size may be omitted and the X font point size will
 *	be used.
 *
 *	Otherwise, if the foundry is "Adobe", we try to do a plausible
 *	mapping looking at the full name of the font and building a
 *	string in the form of "Family-TypeFace".
 *
 * Returns:
 *      None.
 *
 * Side Effects:
 *      PostScript commands are output to change the type and the
 *      point size of the current font.
 *
 * -----------------------------------------------------------------
 */

void
Blt_FontToPostScript(tokenPtr, font)
    struct PsTokenStruct *tokenPtr;
    Tk_Font font;		/* Tk font to query about */
{
    XFontStruct *fsPtr = (XFontStruct *)font;
    Tcl_Interp *interp = tokenPtr->interp;
    char *fontName;
    double pointSize;
#if (TK_MAJOR_VERSION > 4)
    Tk_Uid family;
    register int i;
#endif /* TK_MAJOR_VERSION > 4 */

    fontName = Tk_NameOfFont(font);
    pointSize = 12.0;
    /*
     * Use the font variable information if it exists.
     */
    if (tokenPtr->fontVarName != NULL) {
	char *fontInfo;

	fontInfo = (char *)Tcl_GetVar2(interp, tokenPtr->fontVarName, fontName,
	       0);
	if (fontInfo != NULL) {
	    int nProps;
	    char **propArr = NULL;

	    if (Tcl_SplitList(interp, fontInfo, &nProps, &propArr) == TCL_OK) {
		int newSize;

		fontName = propArr[0];
		if ((nProps == 2) &&
		    (Tcl_GetInt(interp, propArr[1], &newSize) == TCL_OK)) {
		    pointSize = (double)newSize;
		}
	    }
	    Blt_FormatToPostScript(tokenPtr, 
				   "%g /%s SetFont\n", 
				   pointSize, fontName);
	    if (propArr != (char **)NULL) {
		Blt_Free(propArr);
	    }
	    return;
	}
    }
#if (TK_MAJOR_VERSION > 4)

    /*
     * Otherwise do a quick test to see if it's a PostScript font.
     * Tk_PostScriptFontName will silently generate a bogus PostScript
     * font description, so we have to check to see if this is really a
     * PostScript font.
     */
    family = ((TkFont *) fsPtr)->fa.family;
    for (i = 0; i < nFontNames; i++) {
	if (strcasecmp(psFontMap[i].alias, family) == 0) {
	    Tcl_DString dString;

	    Tcl_DStringInit(&dString);
	    pointSize = (double)PostscriptFontName(font, &dString);
	    fontName = Tcl_DStringValue(&dString);
	    Blt_FormatToPostScript(tokenPtr, "%g /%s SetFont\n", pointSize,
		fontName);
	    Tcl_DStringFree(&dString);
	    return;
	}
    }

#endif /* TK_MAJOR_VERSION > 4 */

    /*
     * Can't find it. Try to use the current point size.
     */
    fontName = NULL;
    pointSize = 12.0;

#ifndef  WIN32
#if (TK_MAJOR_VERSION > 4)
    /* Can you believe what I have to go through to get an XFontStruct? */
#ifdef notdef
    fsPtr = XLoadQueryFont(Tk_Display(tokenPtr->tkwin), Tk_NameOfFont(font));
#endif
    fsPtr = XQueryFont(Tk_Display(tokenPtr->tkwin), Tk_FontId(font));
#endif
    if (fsPtr != NULL) {
	unsigned long fontProp;

	if (XGetFontProperty(fsPtr, XA_POINT_SIZE, &fontProp) != False) {
	    pointSize = (double)fontProp / 10.0;
	}
	fontName = XFontStructToPostScript(tokenPtr->tkwin, fsPtr);
#if (TK_MAJOR_VERSION > 4)
	XFreeFontInfo(NULL, fsPtr, 0);
#endif /* TK_MAJOR_VERSION > 4 */
    }
#endif /* !WIN32 */
    if ((fontName == NULL) || (fontName[0] == '\0')) {
	fontName = "HeLveTica-Bold";	/* Defaulting to a known PS font */
    }
    Blt_FormatToPostScript(tokenPtr, "%g /%s SetFont\n", pointSize, fontName);
}


double
Blt_PostScriptFontName(Tcl_Interp *interp, Tk_Font font, Tcl_DString *dsPtr)
{
    Tk_Window tkwin;
    XFontStruct *fsPtr = (XFontStruct *)font;
    char *fontName;
    double pointSize;
    TkFont *tkFontPtr;

#if (TK_MAJOR_VERSION > 4)
    Tk_Uid family;
    register int i;
#endif /* TK_MAJOR_VERSION > 4 */

    fontName = Tk_NameOfFont(font);
    pointSize = 12.0;
    Tcl_DStringInit(dsPtr);
    tkFontPtr = (TkFont *)font;
#if (TK_MAJOR_VERSION > 4)
    /*
     * Otherwise do a quick test to see if it's a PostScript font.
     * Tk_PostScriptFontName will silently generate a bogus PostScript
     * font description, so we have to check to see if this is really a
     * PostScript font.
     */
    family = tkFontPtr->fa.family;
    for (i = 0; i < nFontNames; i++) {
	if (strcasecmp(psFontMap[i].alias, family) == 0) {
	    pointSize = (double)PostscriptFontName(font, dsPtr);
	    return pointSize;
	}
    }
#endif /* TK_MAJOR_VERSION > 4 */
    /*
     * Can't find it. Try to use the current point size.
     */
    fontName = NULL;
    pointSize = 12.0;

#ifndef  WIN32
#if (TK_MAJOR_VERSION > 4)
    tkwin = Tk_MainWindow(interp);
    /* Can you believe what I have to go through to get an XFontStruct? */
#ifdef notdef
    fsPtr = XLoadQueryFont(Tk_Display(tkwin), Tk_NameOfFont(font));
#endif
    fsPtr = XQueryFont(Tk_Display(tkwin), Tk_FontId(font));
#endif
    if (fsPtr != NULL) {
	unsigned long fontProp;

	if (XGetFontProperty(fsPtr, XA_POINT_SIZE, &fontProp) != False) {
	    pointSize = (double)fontProp / 10.0;
	}
	fontName = XFontStructToPostScript(tkwin, fsPtr);
#if (TK_MAJOR_VERSION > 4)
	XFreeFontInfo(NULL, fsPtr, 0);
#endif /* TK_MAJOR_VERSION > 4 */
    }
#endif /* !WIN32 */
    if ((fontName == NULL) || (fontName[0] == '\0')) {
	fontName = "HelvetiCA-Bold";	/* Defaulting to a known PS font */
    }
    Tcl_DStringAppend(dsPtr, fontName, -1);
    return pointSize;
}

static void
TextLayoutToPostScript(tokenPtr, x, y, textPtr)
    struct PsTokenStruct *tokenPtr;
    int x, y;
    TextLayout *textPtr;
{
    char *src, *dst, *end;
    int count;			/* Counts the # of bytes written to
				 * the intermediate scratch buffer. */
    TextFragment *fragPtr;
    int i;
    unsigned char c;
#if HAVE_UTF
    Tcl_UniChar ch;
#endif
    int limit;

    limit = PSTOKEN_BUFSIZ - 4; /* High water mark for the scratch
				   * buffer. */
    fragPtr = textPtr->fragArr;
    for (i = 0; i < textPtr->nFrags; i++, fragPtr++) {
	if (fragPtr->count < 1) {
	    continue;
	}
	Blt_AppendToPostScript(tokenPtr, "(", (char *)NULL);
	count = 0;
	dst = tokenPtr->scratchArr;
	src = fragPtr->text;
	end = fragPtr->text + fragPtr->count;
	while (src < end) {
	    if (count > limit) {
		/* Don't let the scatch buffer overflow */
		dst = tokenPtr->scratchArr;
		dst[count] = '\0';
		Blt_AppendToPostScript(tokenPtr, dst, (char *)NULL);
		count = 0;
	    }
#if HAVE_UTF
	    /*
	     * INTL: For now we just treat the characters as binary
	     * data and display the lower byte.  Eventually this should
	     * be revised to handle international postscript fonts.
	     */
	    src += Tcl_UtfToUniChar(src, &ch);
	    c = (unsigned char)(ch & 0xff);
#else 
	    c = *src++;
#endif

	    if ((c == '\\') || (c == '(') || (c == ')')) {
		/*
		 * If special PostScript characters characters "\", "(",
		 * and ")" are contained in the text string, prepend
		 * backslashes to them.
		 */
		*dst++ = '\\';
		*dst++ = c;
		count += 2;
	    } else if ((c < ' ') || (c > '~')) {
		/* 
		 * Present non-printable characters in their octal
		 * representation.
		 */
		sprintf(dst, "\\%03o", c);
		dst += 4;
		count += 4;

	    } else {
		*dst++ = c;
		count++;
	    }
	}
	tokenPtr->scratchArr[count] = '\0';
	Blt_AppendToPostScript(tokenPtr, tokenPtr->scratchArr, (char *)NULL);
	Blt_FormatToPostScript(tokenPtr, ") %d %d %d DrawAdjText\n",
	    fragPtr->width, x + fragPtr->x, y + fragPtr->y);
    }
}

/*
 * -----------------------------------------------------------------
 *
 * Blt_TextToPostScript --
 *
 *      Output PostScript commands to print a text string. The string
 *      may be rotated at any arbitrary angle, and placed according
 *      the anchor type given. The anchor indicates how to interpret
 *      the window coordinates as an anchor for the text bounding box.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *      Text string is drawn using the given font and GC on the graph
 *      window at the given coordinates, anchor, and rotation
 *
 * -----------------------------------------------------------------
 */
void
Blt_TextToPostScript(tokenPtr, string, tsPtr, x, y)
    struct PsTokenStruct *tokenPtr;
    char *string;		/* String to convert to PostScript */
    TextStyle *tsPtr;		/* Text attribute information */
    double x, y;		/* Window coordinates where to print text */
{
    double theta;
    double rotWidth, rotHeight;
    TextLayout *textPtr;
    Point2D anchorPos;

    if ((string == NULL) || (*string == '\0')) { /* Empty string, do nothing */
	return;
    }
    theta = FMOD(tsPtr->theta, (double)360.0);
    textPtr = Blt_GetTextLayout(string, tsPtr);
    Blt_GetBoundingBox(textPtr->width, textPtr->height, theta, &rotWidth, 
		       &rotHeight, (Point2D *)NULL);
    /*
     * Find the center of the bounding box
     */
    anchorPos.x = x, anchorPos.y = y;
    anchorPos = Blt_TranslatePoint(&anchorPos, ROUND(rotWidth), 
	ROUND(rotHeight), tsPtr->anchor);
    anchorPos.x += (rotWidth * 0.5);
    anchorPos.y += (rotHeight * 0.5);

    /* Initialize text (sets translation and rotation) */
    Blt_FormatToPostScript(tokenPtr, "%d %d %g %g %g BeginText\n", 
	textPtr->width, textPtr->height, tsPtr->theta, anchorPos.x, 
	anchorPos.y);

    Blt_FontToPostScript(tokenPtr, tsPtr->font);

    /* All coordinates are now relative to what was set by BeginText */
    if ((tsPtr->shadow.offset > 0) && (tsPtr->shadow.color != NULL)) {
	Blt_ForegroundToPostScript(tokenPtr, tsPtr->shadow.color);
	TextLayoutToPostScript(tokenPtr, tsPtr->shadow.offset, 
	       tsPtr->shadow.offset, textPtr);
    }
    Blt_ForegroundToPostScript(tokenPtr, (tsPtr->state & STATE_ACTIVE)
	? tsPtr->activeColor : tsPtr->color);
    TextLayoutToPostScript(tokenPtr, 0, 0, textPtr);
    Blt_Free(textPtr);
    Blt_AppendToPostScript(tokenPtr, "EndText\n", (char *)NULL);
}

/*
 * -----------------------------------------------------------------
 *
 * Blt_LineToPostScript --
 *
 *      Outputs PostScript commands to print a multi-segmented line.
 *      It assumes a procedure DashesProc was previously defined.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *      Segmented line is printed.
 *
 * -----------------------------------------------------------------
 */
void
Blt_LineToPostScript(tokenPtr, pointPtr, nPoints)
    struct PsTokenStruct *tokenPtr;
    register XPoint *pointPtr;
    int nPoints;
{
    register int i;

    if (nPoints <= 0) {
	return;
    }
    Blt_FormatToPostScript(tokenPtr, " newpath %d %d moveto\n", 
			   pointPtr->x, pointPtr->y);
    pointPtr++;
    for (i = 1; i < (nPoints - 1); i++, pointPtr++) {
	Blt_FormatToPostScript(tokenPtr, " %d %d lineto\n", 
			       pointPtr->x, pointPtr->y);
	if ((i % PS_MAXPATH) == 0) {
	    Blt_FormatToPostScript(tokenPtr,
		"DashesProc stroke\n newpath  %d %d moveto\n", 
				   pointPtr->x, pointPtr->y);
	}
    }
    Blt_FormatToPostScript(tokenPtr, " %d %d lineto\n", 
			   pointPtr->x, pointPtr->y);
    Blt_AppendToPostScript(tokenPtr, "DashesProc stroke\n", (char *)NULL);
}

void
Blt_BitmapToPostScript(tokenPtr, display, bitmap, scaleX, scaleY)
    struct PsTokenStruct *tokenPtr;
    Display *display;
    Pixmap bitmap;		/* Bitmap to be converted to PostScript */
    double scaleX, scaleY;
{
    int width, height;
    double scaledWidth, scaledHeight;

    Tk_SizeOfBitmap(display, bitmap, &width, &height);
    scaledWidth = (double)width * scaleX;
    scaledHeight = (double)height * scaleY;
    Blt_AppendToPostScript(tokenPtr, "  gsave\n", (char *)NULL);
    Blt_FormatToPostScript(tokenPtr, "    %g %g translate\n", 
			   scaledWidth * -0.5, scaledHeight * 0.5);
    Blt_FormatToPostScript(tokenPtr, "    %g %g scale\n", 
			   scaledWidth, -scaledHeight);
    Blt_FormatToPostScript(tokenPtr, "    %d %d true [%d 0 0 %d 0 %d] {", 
			   width, height, width, -height, height);
    Blt_BitmapDataToPostScript(tokenPtr, display, bitmap, width, height);
    Blt_AppendToPostScript(tokenPtr, "    } imagemask\n  grestore\n",
	(char *)NULL);
}

void
Blt_2DSegmentsToPostScript(psToken, segPtr, nSegments)
    PsToken psToken;
    register Segment2D *segPtr;
    int nSegments;
{
    register Segment2D *endPtr;

    for (endPtr = segPtr + nSegments; segPtr < endPtr; segPtr++) {
	Blt_FormatToPostScript(psToken, "%g %g moveto\n", 
			       segPtr->p.x, segPtr->p.y);
	Blt_FormatToPostScript(psToken, " %g %g lineto\n", 
			       segPtr->q.x, segPtr->q.y);
	Blt_AppendToPostScript(psToken, "DashesProc stroke\n", (char *)NULL);
    }
}
