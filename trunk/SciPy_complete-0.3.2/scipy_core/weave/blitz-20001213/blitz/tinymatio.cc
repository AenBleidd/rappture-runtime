/*
 * $Id: tinymatio.cc,v 1.1 2002/09/12 07:04:04 eric Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: tinymatio.cc,v $
 * Revision 1.1  2002/09/12 07:04:04  eric
 * major rewrite of weave.
 *
 * 0.
 * The underlying library code is significantly re-factored and simpler. There used to be a xxx_spec.py and xxx_info.py file for every group of type conversion classes.  The spec file held the python code that handled the conversion and the info file had most of the C code templates that were generated.  This proved pretty confusing in practice, so the two files have mostly been merged into the spec file.
 *
 * Also, there was quite a bit of code duplication running around.  The re-factoring was able to trim the standard conversion code base (excluding blitz and accelerate stuff) by about 40%.  This should be a huge maintainability and extensibility win.
 *
 * 1.
 * With multiple months of using Numeric arrays, I've found some of weave's "magic variable" names unwieldy and want to change them.  The following are the old declarations for an array x of Float32 type:
 *
 *         PyArrayObject* x = convert_to_numpy(...);
 *         float* x_data = (float*) x->data;
 *         int*   _Nx = x->dimensions;
 *         int*   _Sx = x->strides;
 *         int    _Dx = x->nd;
 *
 * The new declaration looks like this:
 *
 *         PyArrayObject* x_array = convert_to_numpy(...);
 *         float* x = (float*) x->data;
 *         int*   Nx = x->dimensions;
 *         int*   Sx = x->strides;
 *         int    Dx = x->nd;
 *
 * This is obviously not backward compatible, and will break some code (including a lot of mine).  It also makes inline() code more readable and natural to write.
 *
 * 2.
 * I've switched from CXX to Gordon McMillan's SCXX for list, tuples, and dictionaries.  I like CXX pretty well, but its use of advanced C++ (templates, etc.) caused some portability problems.  The SCXX library is similar to CXX but doesn't use templates at all.  This, like (1) is not an
 * API compatible change and requires repairing existing code.
 *
 * I have also thought about boost python, but it also makes heavy use of templates.  Moving to SCXX gets rid of almost all template usage for the standard type converters which should help portability.  std::complex and std::string from the STL are the only templates left.  Of course blitz still uses templates in a major way so weave.blitz will continue to be hard on compilers.
 *
 * I've actually considered scrapping the C++ classes for list, tuples, and
 * dictionaries, and just fall back to the standard Python C API because the classes are waaay slower than the raw API in many cases.  They are also more convenient and less error prone in many cases, so I've decided to stick with them.  The PyObject variable will always be made available for variable "x" under the name "py_x" for more speedy operations.  You'll definitely want to use these for anything that needs to be speedy.
 *
 * 3.
 * strings are converted to std::string now.  I found this to be the most useful type in for strings in my code.  Py::String was used previously.
 *
 * 4.
 * There are a number of reference count "errors" in some of the less tested conversion codes such as instance, module, etc.  I've cleaned most of these up.  I put errors in quotes here because I'm actually not positive that objects passed into "inline" really need reference counting applied to them.  The dictionaries passed in by inline() hold references to these objects so it doesn't seem that they could ever be garbage collected inadvertently.  Variables used by ext_tools, though, definitely need the reference counting done.  I don't think this is a major cost in speed, so it probably isn't worth getting rid of the ref count code.
 *
 * 5.
 * Unicode objects are now supported.  This was necessary to support rendering Unicode strings in the freetype wrappers for Chaco.
 *
 * 6.
 * blitz++ was upgraded to the latest CVS.  It compiles about twice as fast as the old blitz and looks like it supports a large number of compilers (though only gcc 2.95.3 is tested).  Compile times now take about 9 seconds on my 850 MHz PIII laptop.
 *
 * Revision 1.1  2002/05/22 22:38:54  jcumming
 * I/O operations for blitz TinyMatrix.
 *
 *
 */

#ifndef BZ_TINYMATIO_CC
#define BZ_TINYMATIO_CC

#ifndef BZ_TINYMAT_H
 #include <blitz/tinymat.h>
#endif

BZ_NAMESPACE(blitz)

template <typename P_numtype, int N_rows, int N_columns>
ostream& operator<<(ostream& os,
    const TinyMatrix<P_numtype, N_rows, N_columns>& x)
{
    os << "(" << N_rows << "," << N_columns << "): " << endl;
    for (int i=0; i < N_rows; ++i)
    {
        os << " [ ";
        for (int j=0; j < N_columns; ++j)
        {
            os << setw(10) << x(i,j);
            if (!((j+1)%7))
                os << endl << "  ";
        }
        os << " ]" << endl;
    }
    return os;
}

template <typename P_numtype, int N_rows, int N_columns>
istream& operator>>(istream& is, 
    TinyMatrix<P_numtype, N_rows, N_columns>& x)
{
    int rows, columns;
    char sep;
             
    is >> rows >> columns;

    BZPRECHECK(rows == N_rows, "Size mismatch in number of rows");
    BZPRECHECK(columns == N_columns, "Size mismatch in number of columns");

    for (int i=0; i < N_rows; ++i) 
    {
        is >> sep;
        BZPRECHECK(sep == '[', "Format error while scanning input matrix"
            << endl << " (expected '[' before beginning of row data)");
        for (int j = 0; j < N_columns; ++j)
        {
            BZPRECHECK(!is.bad(), "Premature end of input while scanning matrix");
            is >> x(i,j);
        }
        is >> sep;
        BZPRECHECK(sep == ']', "Format error while scanning input matrix"
            << endl << " (expected ']' after end of row data)");
    }

    return is;
}

BZ_NAMESPACE_END

#endif // BZ_TINYMATIO_CC

