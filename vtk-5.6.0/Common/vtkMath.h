/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMath.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
  license for use of this work by or on behalf of the
  U.S. Government. Redistribution and use in source and binary forms, with
  or without modification, are permitted provided that this Notice and any
  statement of authorship are reproduced on all copies.

  Contact: pppebay@sandia.gov,dcthomp@sandia.gov

=========================================================================*/
// .NAME vtkMath - performs common math operations
// .SECTION Description
// vtkMath provides methods to perform common math operations. These 
// include providing constants such as Pi; conversion from degrees to 
// radians; vector operations such as dot and cross products and vector 
// norm; matrix determinant for 2x2 and 3x3 matrices; univariate polynomial
// solvers; and for random number generation (for backward compatibility only).
// .SECTION See Also
// vtkMinimalStandardRandomSequence, vtkBoxMuellerRandomSequence

#ifndef __vtkMath_h
#define __vtkMath_h

#include "vtkObject.h"
#include "vtkPolynomialSolversUnivariate.h" // For backwards compatibility of old solvers

#include <assert.h> // assert() in inline implementations.

#ifndef DBL_EPSILON
#  define VTK_DBL_EPSILON    2.2204460492503131e-16
#else  // DBL_EPSILON
#  define VTK_DBL_EPSILON    DBL_EPSILON
#endif  // DBL_EPSILON

class vtkDataArray;
class vtkPoints;
class vtkMathInternal;
class vtkMinimalStandardRandomSequence;
class vtkBoxMuellerRandomSequence;

class VTK_COMMON_EXPORT vtkMath : public vtkObject
{
public:
  static vtkMath *New();
  vtkTypeRevisionMacro(vtkMath,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // A mathematical constant. This version is 3.14159265358979f.
  static float Pi() { return 3.14159265358979f; };

  // Description:
  // A mathematical constant (double-precision version). This version 
  // is 6.283185307179586.
  static double DoubleTwoPi() { return  6.283185307179586; };

  // Description:
  // A mathematical constant (double-precision version). This version
  // is 3.1415926535897932384626.
  static double DoublePi() { return 3.1415926535897932384626; };

  // Description:
  // Convert degrees into radians
  static float RadiansFromDegrees( float degrees);
  static double RadiansFromDegrees( double degrees);

  // Description:
  // Convert radians into degrees
  static float DegreesFromRadians( float radians);
  static double DegreesFromRadians( double radians);

  // Description:
  // @deprecated Replaced by vtkMath::RadiansFromDegrees() as of VTK 5.4.
  VTK_LEGACY(static float DegreesToRadians());
  VTK_LEGACY(static double DoubleDegreesToRadians());

  // Description:
  // @deprecated Replaced by vtkMath::DegreesFromRadians() as of VTK 5.4.
  VTK_LEGACY(static float RadiansToDegrees());
  VTK_LEGACY(static double DoubleRadiansToDegrees());

  // Description:
  // Rounds a float to the nearest integer.
  static int Round(float f) {
    return static_cast<int>( f + ( f >= 0 ? 0.5 : -0.5 ) ); }
  static int Round(double f) {
    return static_cast<int>( f + ( f >= 0 ? 0.5 : -0.5 ) ); }

  // Description:
  // Rounds a double to the nearest integer less than itself.
  static int Floor(double x);
  
  // Description:
  // Compute N factorial, N! = N*(N-1) * (N-2)...*3*2*1.
  // 0! is taken to be 1.
  static vtkTypeInt64 Factorial( int N );

  // Description:
  // The number of combinations of n objects from a pool of m objects (m>n).
  // This is commonly known as "m choose n" and sometimes denoted \f$_mC_n\f$
  // or \f$\left(\begin{array}{c}m \\ n\end{array}\right)\f$.
  static vtkTypeInt64 Binomial( int m, int n );

  // Description:
  // Start iterating over "m choose n" objects.
  // This function returns an array of n integers, each from 0 to m-1.
  // These integers represent the n items chosen from the set [0,m[. 
  //
  // You are responsible for calling vtkMath::FreeCombination() once the iterator is no longer needed.
  //
  // Warning: this gets large very quickly, especially when n nears m/2!
  // (Hint: think of Pascal's triangle.)
  static int* BeginCombination( int m, int n );

  // Description:
  // Given \a m, \a n, and a valid \a combination of \a n integers in
  // the range [0,m[, this function alters the integers into the next
  // combination in a sequence of all combinations of \a n items from
  // a pool of \a m.
  //
  // If the \a combination is the last item in the sequence on input,
  // then \a combination is unaltered and 0 is returned.
  // Otherwise, 1 is returned and \a combination is updated.
  static int NextCombination( int m, int n, int* combination );

  // Description:
  // Free the "iterator" array created by vtkMath::BeginCombination.
  static void FreeCombination( int* combination);

  // Description:
  // Initialize seed value. NOTE: Random() has the bad property that 
  // the first random number returned after RandomSeed() is called 
  // is proportional to the seed value! To help solve this, call 
  // RandomSeed() a few times inside seed. This doesn't ruin the 
  // repeatability of Random().
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static void RandomSeed(int s);  

  // Description:
  // Return the current seed used by the random number generator.
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static int GetSeed();
  
  // Description:
  // Generate pseudo-random numbers distributed according to the uniform 
  // distribution between 0.0 and 1.0.
  // This is used to provide portability across different systems.
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static double Random();  

  // Description:
  // Generate  pseudo-random numbers distributed according to the uniform 
  // distribution between \a min and \a max.
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static double Random( double min, double max );

  // Description:
  // Generate pseudo-random numbers distributed according to the standard
  // normal distribution.
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static double Gaussian();  

  // Description:
  // Generate  pseudo-random numbers distributed according to the Gaussian
  // distribution with mean \a mean and standard deviation \a std.
  //
  // DON'T USE Random(), RandomSeed(), GetSeed(), Gaussian()
  // THIS IS STATIC SO THIS IS PRONE TO ERRORS (SPECIALLY FOR REGRESSION TESTS)
  // THIS IS HERE FOR BACKWARD COMPATIBILITY ONLY.
  // Instead, for a sequence of random numbers with a uniform distribution
  // create a vtkMinimalStandardRandomSequence object.
  // For a sequence of random numbers with a gaussian/normal distribution
  // create a vtkBoxMuellerRandomSequence object.
  static double Gaussian( double mean, double std );

  // Description:
  // Addition of two 3-vectors (float version). Result is stored in c.
  static void Add(const float a[3], const float b[3], float c[3]) {
    for (int i = 0; i < 3; ++i)
      c[i] = a[i] + b[i];
  }

  // Description:
  // Addition of two 3-vectors (double version). Result is stored in c.
  static void Add(const double a[3], const double b[3], double c[3]) {
    for (int i = 0; i < 3; ++i)
      c[i] = a[i] + b[i];
  }

  // Description:
  // Subtraction of two 3-vectors (float version). Result is stored in c according to c = a - b.
  static void Subtract(const float a[3], const float b[3], float c[3]) {
    for (int i = 0; i < 3; ++i)
      c[i] = a[i] - b[i];
  }

  // Description:
  // Subtraction of two 3-vectors (double version). Result is stored in c according to c = a - b.
  static void Subtract(const double a[3], const double b[3], double c[3]) {
    for (int i = 0; i < 3; ++i)
      c[i] = a[i] - b[i];
  }

  // Description:
  // Multiplies a 3-vector by a scalar (float version).
  // This modifies the input 3-vector.
  static void MultiplyScalar(float a[3], float s) {
    for (int i = 0; i < 3; ++i)
      a[i] *= s;
  }

  // Description:
  // Multiplies a 3-vector by a scalar (double version).
  // This modifies the input 3-vector.
  static void MultiplyScalar(double a[3], double s) {
    for (int i = 0; i < 3; ++i)
      a[i] *= s;
  }

  // Description:
  // Dot product of two 3-vectors (float version).
  static float Dot(const float x[3], const float y[3]) {
    return ( x[0] * y[0] + x[1] * y[1] + x[2] * y[2] );};

  // Description:
  // Dot product of two 3-vectors (double-precision version).
  static double Dot(const double x[3], const double y[3]) {
    return ( x[0] * y[0] + x[1] * y[1] + x[2] * y[2] );};
  
  // Description:
  // Outer product of two 3-vectors (float version).
  static void Outer(const float x[3], const float y[3], float A[3][3]) {
    for (int i=0; i < 3; i++)
      for (int j=0; j < 3; j++)
        A[i][j] = x[i] * y[j];
  }
  // Description:
  // Outer product of two 3-vectors (double-precision version).
  static void Outer(const double x[3], const double y[3], double A[3][3]) {
    for (int i=0; i < 3; i++)
      for (int j=0; j < 3; j++)
        A[i][j] = x[i] * y[j];
  }

  // Description:
  // Cross product of two 3-vectors. Result (a x b) is stored in z.
  static void Cross(const float x[3], const float y[3], float z[3]);

  // Description:
  // Cross product of two 3-vectors. Result (a x b) is stored in z. (double-precision
  // version)
  static void Cross(const double x[3], const double y[3], double z[3]);

  // Description:
  // Compute the norm of n-vector. x is the vector, n is its length.
  static float Norm(const float* x, int n); 
  static double Norm(const double* x, int n); 

  // Description:
  // Compute the norm of 3-vector.
  static float Norm(const float x[3]) {
    return static_cast<float> (sqrt( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] ) );};
  
  // Description:
  // Compute the norm of 3-vector (double-precision version).
  static double Norm(const double x[3]) {
    return sqrt( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] );};
  
  // Description:
  // Normalize (in place) a 3-vector. Returns norm of vector.
  static float Normalize(float x[3]);

  // Description:
  // Normalize (in place) a 3-vector. Returns norm of vector
  // (double-precision version).
  static double Normalize(double x[3]);

  // Description:
  // Given a unit vector x, find two unit vectors y and z such that 
  // x cross y = z (i.e. the vectors are perpendicular to each other).
  // There is an infinite number of such vectors, specify an angle theta 
  // to choose one set.  If you want only one perpendicular vector, 
  // specify NULL for z.
  static void Perpendiculars(const double x[3], double y[3], double z[3], 
                             double theta);
  static void Perpendiculars(const float x[3], float y[3], float z[3],
                             double theta);

  // Description:
  // Compute distance squared between two points x and y.
  static float Distance2BetweenPoints(const float x[3], const float y[3]);

  // Description:
  // Compute distance squared between two points x and y(double precision version).
  static double Distance2BetweenPoints(const double x[3], const double y[3]);

  // Description:
  // Dot product of two 2-vectors.
  static float Dot2D(const float x[2], const float y[2]) {
    return ( x[0] * y[0] + x[1] * y[1] );};
  
  // Description:
  // Dot product of two 2-vectors. (double-precision version).
  static double Dot2D(const double x[2], const double y[2]) {
    return ( x[0] * y[0] + x[1] * y[1] );};

  // Description:
  // Outer product of two 2-vectors (float version).
  static void Outer2D(const float x[2], const float y[2], float A[2][2]) 
    {
    for (int i=0; i < 2; i++)
      {
      for (int j=0; j < 2; j++)
        {
        A[i][j] = x[i] * y[j];
        }
      }
    }
  // Description:
  // Outer product of two 2-vectors (float version).
  static void Outer2D(const double x[2], const double y[2], double A[2][2]) 
    {
    for (int i=0; i < 2; i++)
      {
      for (int j=0; j < 2; j++)
        {
        A[i][j] = x[i] * y[j];
        }
      }
    }

  // Description:
  // Compute the norm of a 2-vector.
  static float Norm2D(const float x[2]) {
    return static_cast<float> (sqrt( x[0] * x[0] + x[1] * x[1] ) );};

  // Description:
  // Compute the norm of a 2-vector.
  // (double-precision version).
  static double Norm2D(const double x[2]) {
    return sqrt( x[0] * x[0] + x[1] * x[1] );};

  // Description:
  // Normalize (in place) a 2-vector. Returns norm of vector.
  static float Normalize2D(float x[2]);

  // Description:
  // Normalize (in place) a 2-vector. Returns norm of vector.
  // (double-precision version).
  static double Normalize2D(double x[2]);

  // Description:
  // Compute determinant of 2x2 matrix. Two columns of matrix are input.
  static float Determinant2x2(const float c1[2], const float c2[2]) {
    return (c1[0] * c2[1] - c2[0] * c1[1] );};

  // Description:
  // Calculate the determinant of a 2x2 matrix: | a b | | c d |
  static double Determinant2x2(double a, double b, double c, double d) {
    return (a * d - b * c);};
  static double Determinant2x2(const double c1[2], const double c2[2]) {
    return (c1[0] * c2[1] - c2[0] * c1[1] );};

  // Description:
  // LU Factorization of a 3x3 matrix.
  static void LUFactor3x3(float A[3][3], int index[3]);
  static void LUFactor3x3(double A[3][3], int index[3]);

  // Description:
  // LU back substitution for a 3x3 matrix.
  static void LUSolve3x3(const float A[3][3], const int index[3], 
                         float x[3]);
  static void LUSolve3x3(const double A[3][3], const int index[3], 
                         double x[3]);

  // Description:
  // Solve Ay = x for y and place the result in y.  The matrix A is
  // destroyed in the process.
  static void LinearSolve3x3(const float A[3][3], const float x[3], 
                             float y[3]);
  static void LinearSolve3x3(const double A[3][3], const double x[3], 
                             double y[3]);

  // Description:
  // Multiply a vector by a 3x3 matrix.  The result is placed in out.
  static void Multiply3x3(const float A[3][3], const float in[3], 
                          float out[3]);
  static void Multiply3x3(const double A[3][3], const double in[3], 
                          double out[3]);
  
  // Description:
  // Multiply one 3x3 matrix by another according to C = AB.
  static void Multiply3x3(const float A[3][3], const float B[3][3], 
                          float C[3][3]);
  static void Multiply3x3(const double A[3][3], const double B[3][3], 
                          double C[3][3]);

  // Description:
  // General matrix multiplication.  You must allocate output storage.
  // colA == rowB
  // and matrix C is rowA x colB
  static void MultiplyMatrix(const double **A, const double **B,
                             unsigned int rowA, unsigned int colA, 
                             unsigned int rowB, unsigned int colB,
                             double **C);

  // Description:
  // Transpose a 3x3 matrix. The input matrix is A. The output
  // is stored in AT.
  static void Transpose3x3(const float A[3][3], float AT[3][3]);
  static void Transpose3x3(const double A[3][3], double AT[3][3]);

  // Description:
  // Invert a 3x3 matrix. The input matrix is A. The output is
  // stored in AI.
  static void Invert3x3(const float A[3][3], float AI[3][3]);
  static void Invert3x3(const double A[3][3], double AI[3][3]);

  // Description:
  // Set A to the identity matrix.
  static void Identity3x3(float A[3][3]);
  static void Identity3x3(double A[3][3]);

  // Description:
  // Return the determinant of a 3x3 matrix.
  static double Determinant3x3(float A[3][3]);
  static double Determinant3x3(double A[3][3]);

  // Description:
  // Compute determinant of 3x3 matrix. Three columns of matrix are input.
  static float Determinant3x3(const float c1[3], 
                              const float c2[3], 
                              const float c3[3]);

  // Description:
  // Compute determinant of 3x3 matrix. Three columns of matrix are input.
  static double Determinant3x3(const double c1[3], 
                               const double c2[3], 
                               const double c3[3]);

  // Description:
  // Calculate the determinant of a 3x3 matrix in the form:
  //     | a1,  b1,  c1 |
  //     | a2,  b2,  c2 |
  //     | a3,  b3,  c3 |
  static double Determinant3x3(double a1, double a2, double a3, 
                               double b1, double b2, double b3, 
                               double c1, double c2, double c3);

  // Description:
  // Convert a quaternion to a 3x3 rotation matrix.  The quaternion
  // does not have to be normalized beforehand.
  static void QuaternionToMatrix3x3(const float quat[4], float A[3][3]); 
  static void QuaternionToMatrix3x3(const double quat[4], double A[3][3]); 

  // Description:
  // Convert a 3x3 matrix into a quaternion.  This will provide the
  // best possible answer even if the matrix is not a pure rotation matrix.
  // The method used is that of B.K.P. Horn.
  static void Matrix3x3ToQuaternion(const float A[3][3], float quat[4]);
  static void Matrix3x3ToQuaternion(const double A[3][3], double quat[4]);
  
  // Description:
  // Orthogonalize a 3x3 matrix and put the result in B.  If matrix A
  // has a negative determinant, then B will be a rotation plus a flip
  // i.e. it will have a determinant of -1.
  static void Orthogonalize3x3(const float A[3][3], float B[3][3]);
  static void Orthogonalize3x3(const double A[3][3], double B[3][3]);

  // Description:
  // Diagonalize a symmetric 3x3 matrix and return the eigenvalues in
  // w and the eigenvectors in the columns of V.  The matrix V will 
  // have a positive determinant, and the three eigenvectors will be
  // aligned as closely as possible with the x, y, and z axes.
  static void Diagonalize3x3(const float A[3][3], float w[3], float V[3][3]);
  static void Diagonalize3x3(const double A[3][3],double w[3],double V[3][3]);

  // Description:
  // Perform singular value decomposition on a 3x3 matrix.  This is not
  // done using a conventional SVD algorithm, instead it is done using
  // Orthogonalize3x3 and Diagonalize3x3.  Both output matrices U and VT
  // will have positive determinants, and the w values will be arranged
  // such that the three rows of VT are aligned as closely as possible
  // with the x, y, and z axes respectively.  If the determinant of A is
  // negative, then the three w values will be negative.
  static void SingularValueDecomposition3x3(const float A[3][3],
                                            float U[3][3], float w[3],
                                            float VT[3][3]);
  static void SingularValueDecomposition3x3(const double A[3][3],
                                            double U[3][3], double w[3],
                                            double VT[3][3]);

  // Description:
  // Solve linear equations Ax = b using Crout's method. Input is square
  // matrix A and load vector x. Solution x is written over load vector. The
  // dimension of the matrix is specified in size. If error is found, method
  // returns a 0.
  static int SolveLinearSystem(double **A, double *x, int size);

  // Description:
  // Invert input square matrix A into matrix AI. 
  // Note that A is modified during
  // the inversion. The size variable is the dimension of the matrix. Returns 0
  // if inverse not computed.
  static int InvertMatrix(double **A, double **AI, int size);

  // Description:
  // Thread safe version of InvertMatrix method.
  // Working memory arrays tmp1SIze and tmp2Size
  // of length size must be passed in.
  static int InvertMatrix(double **A, double **AI, int size,
                          int *tmp1Size, double *tmp2Size);

  // Description:
  // Factor linear equations Ax = b using LU decomposition A = LU where L is
  // lower triangular matrix and U is upper triangular matrix. Input is 
  // square matrix A, integer array of pivot indices index[0->n-1], and size
  // of square matrix n. Output factorization LU is in matrix A. If error is 
  // found, method returns 0. 
  static int LUFactorLinearSystem(double **A, int *index, int size);

  // Description:
  // Thread safe version of LUFactorLinearSystem method.
  // Working memory array tmpSize of length size
  // must be passed in.
  static int LUFactorLinearSystem(double **A, int *index, int size,
                                  double *tmpSize);

  // Description:
  // Solve linear equations Ax = b using LU decomposition A = LU where L is
  // lower triangular matrix and U is upper triangular matrix. Input is 
  // factored matrix A=LU, integer array of pivot indices index[0->n-1],
  // load vector x[0->n-1], and size of square matrix n. Note that A=LU and
  // index[] are generated from method LUFactorLinearSystem). Also, solution
  // vector is written directly over input load vector.
  static void LUSolveLinearSystem(double **A, int *index, 
                                  double *x, int size);

  // Description:
  // Estimate the condition number of a LU factored matrix. Used to judge the
  // accuracy of the solution. The matrix A must have been previously factored
  // using the method LUFactorLinearSystem. The condition number is the ratio
  // of the infinity matrix norm (i.e., maximum value of matrix component)
  // divided by the minimum diagonal value. (This works for triangular matrices
  // only: see Conte and de Boor, Elementary Numerical Analysis.)
  static double EstimateMatrixCondition(double **A, int size);

  // Description:
  // Jacobi iteration for the solution of eigenvectors/eigenvalues of a 3x3
  // real symmetric matrix. Square 3x3 matrix a; output eigenvalues in w;
  // and output eigenvectors in v. Resulting eigenvalues/vectors are sorted
  // in decreasing order; eigenvectors are normalized.
  static int Jacobi(float **a, float *w, float **v);
  static int Jacobi(double **a, double *w, double **v);

  // Description:
  // JacobiN iteration for the solution of eigenvectors/eigenvalues of a nxn
  // real symmetric matrix. Square nxn matrix a; size of matrix in n; output
  // eigenvalues in w; and output eigenvectors in v. Resulting
  // eigenvalues/vectors are sorted in decreasing order; eigenvectors are
  // normalized.  w and v need to be allocated previously
  static int JacobiN(float **a, int n, float *w, float **v);
  static int JacobiN(double **a, int n, double *w, double **v);

  // Description:
  // Solves a cubic equation c0*t^3 + c1*t^2 + c2*t + c3 = 0 when c0, c1, c2,
  // and c3 are REAL.  Solution is motivated by Numerical Recipes In C 2nd
  // Ed.  Return array contains number of (real) roots (counting multiple
  // roots as one) followed by roots themselves. The value in roots[4] is a
  // integer giving further information about the roots (see return codes for
  // int SolveCubic() ).
  static double* SolveCubic(double c0, double c1, double c2, double c3);

  // Description:
  // Solves a quadratic equation c1*t^2 + c2*t + c3 = 0 when c1, c2, and c3
  // are REAL.  Solution is motivated by Numerical Recipes In C 2nd Ed.
  // Return array contains number of (real) roots (counting multiple roots as
  // one) followed by roots themselves. Note that roots[3] contains a return
  // code further describing solution - see documentation for SolveCubic()
  // for meaning of return codes.
  static double* SolveQuadratic(double c0, double c1, double c2);

  // Description:
  // Solves a linear equation c2*t  + c3 = 0 when c2 and c3 are REAL.
  // Solution is motivated by Numerical Recipes In C 2nd Ed.
  // Return array contains number of roots followed by roots themselves.
  static double* SolveLinear(double c0, double c1);

  // Description:
  // Solves a cubic equation when c0, c1, c2, And c3 Are REAL.  Solution
  // is motivated by Numerical Recipes In C 2nd Ed.  Roots and number of
  // real roots are stored in user provided variables r1, r2, r3, and
  // num_roots. Note that the function can return the following integer
  // values describing the roots: (0)-no solution; (-1)-infinite number
  // of solutions; (1)-one distinct real root of multiplicity 3 (stored
  // in r1); (2)-two distinct real roots, one of multiplicity 2 (stored
  // in r1 & r2); (3)-three distinct real roots; (-2)-quadratic equation
  // with complex conjugate solution (real part of root returned in r1,
  // imaginary in r2); (-3)-one real root and a complex conjugate pair
  // (real root in r1 and real part of pair in r2 and imaginary in r3).
  static int SolveCubic(double c0, double c1, double c2, double c3, 
                        double *r1, double *r2, double *r3, int *num_roots);

  // Description:
  // Solves a quadratic equation c1*t^2  + c2*t  + c3 = 0 when 
  // c1, c2, and c3 are REAL.
  // Solution is motivated by Numerical Recipes In C 2nd Ed.
  // Roots and number of roots are stored in user provided variables
  // r1, r2, num_roots
  static int SolveQuadratic(double c0, double c1, double c2, 
                            double *r1, double *r2, int *num_roots);
  
  // Description:
  // Algebraically extracts REAL roots of the quadratic polynomial with 
  // REAL coefficients c[0] X^2 + c[1] X + c[2]
  // and stores them (when they exist) and their respective multiplicities
  // in the \a r and \a m arrays.
  // Returns either the number of roots, or -1 if ininite number of roots.
  static int SolveQuadratic( double* c, double* r, int* m );

  // Description:
  // Solves a linear equation c2*t + c3 = 0 when c2 and c3 are REAL.
  // Solution is motivated by Numerical Recipes In C 2nd Ed.
  // Root and number of (real) roots are stored in user provided variables
  // r2 and num_roots.
  static int SolveLinear(double c0, double c1, double *r1, int *num_roots);

  // Description:
  // Solves for the least squares best fit matrix for the homogeneous equation X'M' = 0'.
  // Uses the method described on pages 40-41 of Computer Vision by 
  // Forsyth and Ponce, which is that the solution is the eigenvector 
  // associated with the minimum eigenvalue of T(X)X, where T(X) is the
  // transpose of X.
  // The inputs and output are transposed matrices.
  //    Dimensions: X' is numberOfSamples by xOrder,
  //                M' dimension is xOrder by yOrder.
  // M' should be pre-allocated. All matrices are row major. The resultant
  // matrix M' should be pre-multiplied to X' to get 0', or transposed and
  // then post multiplied to X to get 0
  static int SolveHomogeneousLeastSquares(int numberOfSamples, double **xt, int xOrder,
                                double **mt);


  // Description:
  // Solves for the least squares best fit matrix for the equation X'M' = Y'.
  // Uses pseudoinverse to get the ordinary least squares. 
  // The inputs and output are transposed matrices.
  //    Dimensions: X' is numberOfSamples by xOrder,
  //                Y' is numberOfSamples by yOrder,
  //                M' dimension is xOrder by yOrder.
  // M' should be pre-allocated. All matrices are row major. The resultant
  // matrix M' should be pre-multiplied to X' to get Y', or transposed and
  // then post multiplied to X to get Y
  // By default, this method checks for the homogeneous condition where Y==0, and
  // if so, invokes SolveHomogeneousLeastSquares. For better performance when
  // the system is known not to be homogeneous, invoke with checkHomogeneous=0.
  static int SolveLeastSquares(int numberOfSamples, double **xt, int xOrder,
                               double **yt, int yOrder, double **mt, int checkHomogeneous=1);

  // Description:
  // Convert color in RGB format (Red, Green, Blue) to HSV format
  // (Hue, Saturation, Value). The input color is not modified.
  static void RGBToHSV(const float rgb[3], float hsv[3])
    { RGBToHSV(rgb[0], rgb[1], rgb[2], hsv, hsv+1, hsv+2); }
  static void RGBToHSV(float r, float g, float b, float *h, float *s, float *v);
  static double* RGBToHSV(const double rgb[3]);
  static double* RGBToHSV(double r, double g, double b);
  static void RGBToHSV(const double rgb[3], double hsv[3])
    { RGBToHSV(rgb[0], rgb[1], rgb[2], hsv, hsv+1, hsv+2); }
  static void RGBToHSV(double r, double g, double b, double *h, double *s, double *v);

  // Description:
  // Convert color in HSV format (Hue, Saturation, Value) to RGB
  // format (Red, Green, Blue). The input color is not modified.
  static void HSVToRGB(const float hsv[3], float rgb[3])
    { HSVToRGB(hsv[0], hsv[1], hsv[2], rgb, rgb+1, rgb+2); }
  static void HSVToRGB(float h, float s, float v, float *r, float *g, float *b);
  static double* HSVToRGB(const double hsv[3]);
  static double* HSVToRGB(double h, double s, double v);
  static void HSVToRGB(const double hsv[3], double rgb[3])
    { HSVToRGB(hsv[0], hsv[1], hsv[2], rgb, rgb+1, rgb+2); }
  static void HSVToRGB(double h, double s, double v, double *r, double *g, double *b);

  // Description:
  // Convert color from the CIE-L*ab system to CIE XYZ.
  static void LabToXYZ(const double lab[3], double xyz[3]) {
    LabToXYZ(lab[0], lab[1], lab[2], xyz+0, xyz+1, xyz+2);
  }
  static void LabToXYZ(double L, double a, double b,
                       double *x, double *y, double *z);
  static double *LabToXYZ(const double lab[3]);

  // Description:
  // Convert Color from the CIE XYZ system to CIE-L*ab.
  static void XYZToLab(const double xyz[3], double lab[3]) {
    XYZToLab(xyz[0], xyz[1], xyz[2], lab+0, lab+1, lab+2);
  }
  static void XYZToLab(double x, double y, double z,
                       double *L, double *a, double *b);
  static double *XYZToLab(const double xyz[3]);

  // Description:
  // Convert color from the CIE XYZ system to RGB.
  static void XYZToRGB(const double xyz[3], double rgb[3]) {
    XYZToRGB(xyz[0], xyz[1], xyz[2], rgb+0, rgb+1, rgb+2);
  }
  static void XYZToRGB(double x, double y, double z,
                       double *r, double *g, double *b);
  static double *XYZToRGB(const double xyz[3]);

  // Description:
  // Convert color from the RGB system to CIE XYZ.
  static void RGBToXYZ(const double rgb[3], double xyz[3]) {
    RGBToXYZ(rgb[0], rgb[1], rgb[2], xyz+0, xyz+1, xyz+2);
  }
  static void RGBToXYZ(double r, double g, double b,
                       double *x, double *y, double *z);
  static double *RGBToXYZ(const double rgb[3]);

  // Description:
  // Convert color from the RGB system to CIE-L*ab.
  static void RGBToLab(const double rgb[3], double lab[3]) {
    RGBToLab(rgb[0], rgb[1], rgb[2], lab+0, lab+1, lab+2);
  }
  static void RGBToLab(double red, double green, double blue,
                       double *L, double *a, double *b);
  static double *RGBToLab(const double rgb[3]);

  // Description:
  // Convert color from the CIE-L*ab system to RGB.
  static void LabToRGB(const double lab[3], double rgb[3]) {
    LabToRGB(lab[0], lab[1], lab[2], rgb+0, rgb+1, rgb+2);
  }
  static void LabToRGB(double L, double a, double b,
                       double *red, double *green, double *blue);
  static double *LabToRGB(const double lab[3]);

  // Description:
  // Set the bounds to an uninitialized state
  static void UninitializeBounds(double bounds[6]){
    bounds[0] = 1.0;
    bounds[1] = -1.0;
    bounds[2] = 1.0;
    bounds[3] = -1.0;
    bounds[4] = 1.0;
    bounds[5] = -1.0;
  }
  
  // Description:
  // Are the bounds initialized?
  static int AreBoundsInitialized(double bounds[6]){
    if ( bounds[1]-bounds[0]<0.0 )
      {
      return 0;
      }
    return 1;
  }

  // Description:
  // Clamp some values against a range
  // The method without 'clamped_values' will perform in-place clamping.
  static void ClampValue(double *value, const double range[2]);
  static void ClampValue(double value, const double range[2], double *clamped_value);
  static void ClampValues(
    double *values, int nb_values, const double range[2]);
  static void ClampValues(
    const double *values, int nb_values, const double range[2], double *clamped_values);

  // Description:
  // Clamp a value against a range and then normalized it between 0 and 1.
  // If range[0]==range[1], the result is 0.
  // \pre valid_range: range[0]<=range[1]
  // \post valid_result: result>=0.0 && result<=1.0
  static double ClampAndNormalizeValue(double value,
                                       const double range[2]);

  // Description:
  // Return the scalar type that is most likely to have enough precision 
  // to store a given range of data once it has been scaled and shifted 
  // (i.e. [range_min * scale + shift, range_max * scale + shift]. 
  // If any one of the parameters is not an integer number (decimal part != 0),
  // the search will default to float types only (float or double)
  // Return -1 on error or no scalar type found.
  static int GetScalarTypeFittingRange(
    double range_min, double range_max, 
    double scale = 1.0, double shift = 0.0);

  // Description:
  // Get a vtkDataArray's scalar range for a given component. 
  // If the vtkDataArray's data type is unsigned char (VTK_UNSIGNED_CHAR)
  // the range is adjusted to the whole data type range [0, 255.0]. 
  // Same goes for unsigned short (VTK_UNSIGNED_SHORT) but the upper bound 
  // is also adjusted down to 4095.0 if was between ]255, 4095.0].
  // Return 1 on success, 0 otherwise.
  static int GetAdjustedScalarRange(
    vtkDataArray *array, int comp, double range[2]);
 
  // Description:
  // Return true if first 3D extent is within second 3D extent
  // Extent is x-min, x-max, y-min, y-max, z-min, z-max
  static int ExtentIsWithinOtherExtent(int extent1[6], int extent2[6]);
  
  // Description:
  // Return true if first 3D bounds is within the second 3D bounds
  // Bounds is x-min, x-max, y-min, y-max, z-min, z-max
  // Delta is the error margin along each axis (usually a small number)
  static int BoundsIsWithinOtherBounds(double bounds1[6], double bounds2[6], double delta[3]);
  
  // Description:
  // Return true if point is within the given 3D bounds
  // Bounds is x-min, x-max, y-min, y-max, z-min, z-max
  // Delta is the error margin along each axis (usually a small number)
  static int PointIsWithinBounds(double point[3], double bounds[6], double delta[3]);

  // Description:
  // Calculate \a num points, at a regular interval, along a parametric 
  // spiral. Note this spiral is only in two dimensions having a constant
  // z value.
  static void SpiralPoints(vtkIdType num, vtkPoints * offsets);
  
  // Description:
  // In Euclidean space, there is a unique circle passing through any given 
  // three non-collinear points P1, P2, and P3. Using Cartesian coordinates 
  // to represent these points as spatial vectors, it is possible to use the 
  // dot product and cross product to calculate the radius and center of the 
  // circle. See: http://en.wikipedia.org/wiki/Circumcircle and more
  // specifically the section Barycentric coordinates from cross- and 
  // dot-products
  static double Solve3PointCircle(const double p1[3], const double p2[3], const double p3[3], double center[3]);

  // Description:
  // Special IEEE-754 number used to represent positive infinity.
  static double Inf();

  // Description:
  // Special IEEE-754 number used to represent negative infinity.
  static double NegInf();

  // Description:
  // Special IEEE-754 number used to represent Not-A-Number (Nan).
  static double Nan();

  // Description:
  // Test if a number is equal to the special floating point value infinity.
  static int IsInf(double x);

  // Test if a number is equal to the special floating point value Not-A-Number (Nan).
  static int IsNan(double x);

protected:
  vtkMath() {};
  ~vtkMath() {};
  
  static vtkMathInternal Internal;
private:
  vtkMath(const vtkMath&);  // Not implemented.
  void operator=(const vtkMath&);  // Not implemented.
};

//BTX
class vtkMathInternal
{
public:
  vtkMathInternal();
  ~vtkMathInternal();
  vtkMinimalStandardRandomSequence *Uniform;
  vtkBoxMuellerRandomSequence *Gaussian;
};
//ETX

//----------------------------------------------------------------------------
inline float vtkMath::RadiansFromDegrees( float x )
{
  return x * 0.017453292f;
}

//----------------------------------------------------------------------------
inline double vtkMath::RadiansFromDegrees( double x )
{
  return x * 0.017453292519943295;
}

//----------------------------------------------------------------------------
inline float vtkMath::DegreesFromRadians( float x )
{
  return x * 57.2957795131f;
}

//----------------------------------------------------------------------------
inline double vtkMath::DegreesFromRadians( double x )
{
  return x * 57.29577951308232;
}

#ifndef VTK_LEGACY_REMOVE
//----------------------------------------------------------------------------
inline float vtkMath::DegreesToRadians()
{
  VTK_LEGACY_REPLACED_BODY(vtkMath::DegreesToRadians, "VTK 5.4",
                           vtkMath::RadiansFromDegrees);

  return vtkMath::RadiansFromDegrees( 1.f );
}

//----------------------------------------------------------------------------
inline double vtkMath::DoubleDegreesToRadians()
{
  VTK_LEGACY_REPLACED_BODY(vtkMath::DoubleDegreesToRadians, "VTK 5.4",
                           vtkMath::RadiansFromDegrees);


  return vtkMath::RadiansFromDegrees( 1. );
}

//----------------------------------------------------------------------------
inline float vtkMath::RadiansToDegrees()
{
  VTK_LEGACY_REPLACED_BODY(vtkMath::RadiansToDegrees, "VTK 5.4",
                           vtkMath::DegreesFromRadians);

  return vtkMath::DegreesFromRadians( 1.f );
}

//----------------------------------------------------------------------------
inline double vtkMath::DoubleRadiansToDegrees()
{
  VTK_LEGACY_REPLACED_BODY(vtkMath::DoubleRadiansToDegrees, "VTK 5.4",
                           vtkMath::DegreesFromRadians);

  return vtkMath::DegreesFromRadians( 1. );
}
#endif // #ifndef VTK_LEGACY_REMOVE

//----------------------------------------------------------------------------
inline vtkTypeInt64 vtkMath::Factorial( int N )
{
  vtkTypeInt64 r = 1;
  while ( N > 1 )
    {
    r *= N--;
    }
  return r;
}

//----------------------------------------------------------------------------
inline int vtkMath::Floor(double x)
{
#if defined i386 || defined _M_IX86
  union { int i[2]; double d; } u;
  // use 52-bit precision of IEEE double to round (x - 0.25) to 
  // the nearest multiple of 0.5, according to prevailing rounding
  // mode which is IEEE round-to-nearest,even
  u.d = (x - 0.25) + 3377699720527872.0; // (2**51)*1.5
  // extract mantissa, use shift to divide by 2 and hence get rid
  // of the bit that gets messed up because the FPU uses
  // round-to-nearest,even mode instead of round-to-nearest,+infinity
  return u.i[0] >> 1;
#else
  return static_cast<int>(floor( x ) );
#endif
}

//----------------------------------------------------------------------------
inline float vtkMath::Normalize(float x[3])
{
  float den; 
  if ( ( den = vtkMath::Norm( x ) ) != 0.0 )
    {
    for (int i=0; i < 3; i++)
      {
      x[i] /= den;
      }
    }
  return den;
}

//----------------------------------------------------------------------------
inline double vtkMath::Normalize(double x[3])
{
  double den; 
  if ( ( den = vtkMath::Norm( x ) ) != 0.0 )
    {
    for (int i=0; i < 3; i++)
      {
      x[i] /= den;
      }
    }
  return den;
}

//----------------------------------------------------------------------------
inline float vtkMath::Normalize2D(float x[3])
{
  float den; 
  if ( ( den = vtkMath::Norm2D( x ) ) != 0.0 )
    {
    for (int i=0; i < 2; i++)
      {
      x[i] /= den;
      }
    }
  return den;
}

//----------------------------------------------------------------------------
inline double vtkMath::Normalize2D(double x[3])
{
  double den; 
  if ( ( den = vtkMath::Norm2D( x ) ) != 0.0 )
    {
    for (int i=0; i < 2; i++)
      {
      x[i] /= den;
      }
    }
  return den;
}

//----------------------------------------------------------------------------
inline float vtkMath::Determinant3x3(const float c1[3], 
                                     const float c2[3], 
                                     const float c3[3])
{
  return c1[0] * c2[1] * c3[2] + c2[0] * c3[1] * c1[2] + c3[0] * c1[1] * c2[2] -
         c1[0] * c3[1] * c2[2] - c2[0] * c1[1] * c3[2] - c3[0] * c2[1] * c1[2];
}

//----------------------------------------------------------------------------
inline double vtkMath::Determinant3x3(const double c1[3], 
                                      const double c2[3], 
                                      const double c3[3])
{
  return c1[0] * c2[1] * c3[2] + c2[0] * c3[1] * c1[2] + c3[0] * c1[1] * c2[2] -
         c1[0] * c3[1] * c2[2] - c2[0] * c1[1] * c3[2] - c3[0] * c2[1] * c1[2];
}

//----------------------------------------------------------------------------
inline double vtkMath::Determinant3x3(double a1, double a2, double a3, 
                                      double b1, double b2, double b3, 
                                      double c1, double c2, double c3)
{
    return ( a1 * vtkMath::Determinant2x2( b2, b3, c2, c3 )
           - b1 * vtkMath::Determinant2x2( a2, a3, c2, c3 )
           + c1 * vtkMath::Determinant2x2( a2, a3, b2, b3 ) );
}

//----------------------------------------------------------------------------
inline float vtkMath::Distance2BetweenPoints(const float x[3], 
                                             const float y[3])
{
  return ( ( x[0] - y[0] ) * ( x[0] - y[0] ) 
           + ( x[1] - y[1] ) * ( x[1] - y[1] ) 
           + ( x[2] - y[2] ) * ( x[2] - y[2] ) );
}

//----------------------------------------------------------------------------
inline double vtkMath::Distance2BetweenPoints(const double x[3], 
                                              const double y[3])
{
  return ( ( x[0] - y[0] ) * ( x[0] - y[0] ) 
           + ( x[1] - y[1] ) * ( x[1] - y[1] ) 
           + ( x[2] - y[2] ) * ( x[2] - y[2] ) );
}

//----------------------------------------------------------------------------
// Cross product of two 3-vectors. Result (a x b) is stored in z[3].
inline void vtkMath::Cross(const float x[3], const float y[3], float z[3])
{
  float Zx = x[1] * y[2] - x[2] * y[1]; 
  float Zy = x[2] * y[0] - x[0] * y[2];
  float Zz = x[0] * y[1] - x[1] * y[0];
  z[0] = Zx; z[1] = Zy; z[2] = Zz; 
}

//----------------------------------------------------------------------------
// Cross product of two 3-vectors. Result (a x b) is stored in z[3].
inline void vtkMath::Cross(const double x[3], const double y[3], double z[3])
{
  double Zx = x[1] * y[2] - x[2] * y[1]; 
  double Zy = x[2] * y[0] - x[0] * y[2];
  double Zz = x[0] * y[1] - x[1] * y[0];
  z[0] = Zx; z[1] = Zy; z[2] = Zz; 
}

//BTX
//----------------------------------------------------------------------------
template<class T>
inline double vtkDeterminant3x3(T A[3][3])
{
  return A[0][0] * A[1][1] * A[2][2] + A[1][0] * A[2][1] * A[0][2] + 
         A[2][0] * A[0][1] * A[1][2] - A[0][0] * A[2][1] * A[1][2] - 
         A[1][0] * A[0][1] * A[2][2] - A[2][0] * A[1][1] * A[0][2];
}
//ETX

//----------------------------------------------------------------------------
inline double vtkMath::Determinant3x3(float A[3][3])
{
  return vtkDeterminant3x3( A );
}

//----------------------------------------------------------------------------
inline double vtkMath::Determinant3x3(double A[3][3])
{
  return vtkDeterminant3x3( A );
}

//----------------------------------------------------------------------------
inline double* vtkMath::SolveCubic(double c0, double c1, double c2, double c3)
{
  return vtkPolynomialSolversUnivariate::SolveCubic( c0, c1, c2, c3 );
}

//----------------------------------------------------------------------------
inline double* vtkMath::SolveQuadratic(double c0, double c1, double c2)
{
  return vtkPolynomialSolversUnivariate::SolveQuadratic( c0, c1, c2 );
}

//----------------------------------------------------------------------------
inline double* vtkMath::SolveLinear(double c0, double c1)
{
  return vtkPolynomialSolversUnivariate::SolveLinear( c0, c1 );
}

//----------------------------------------------------------------------------
inline int vtkMath::SolveCubic(double c0, double c1, double c2, double c3, 
                               double *r1, double *r2, double *r3, int *num_roots)
{
  return vtkPolynomialSolversUnivariate::SolveCubic( c0, c1, c2, c3, r1, r2, r3, num_roots );
}

//----------------------------------------------------------------------------
inline int vtkMath::SolveQuadratic(double c0, double c1, double c2, 
                                   double *r1, double *r2, int *num_roots)
{
  return vtkPolynomialSolversUnivariate::SolveQuadratic( c0, c1, c2, r1, r2, num_roots );
}
  
//----------------------------------------------------------------------------
inline int vtkMath::SolveQuadratic( double* c, double* r, int* m )
{
  return vtkPolynomialSolversUnivariate::SolveQuadratic( c, r, m );
}

//----------------------------------------------------------------------------
inline int vtkMath::SolveLinear(double c0, double c1, double *r1, int *num_roots)
{
  return vtkPolynomialSolversUnivariate::SolveLinear( c0, c1, r1, num_roots );
}

//----------------------------------------------------------------------------
inline void vtkMath::ClampValue(double *value, const double range[2])
{
  if (value && range)
    {
    if (*value < range[0])
      {
      *value = range[0];
      }
    else if (*value > range[1])
      {
      *value = range[1];
      }
    }
}

//----------------------------------------------------------------------------
inline void vtkMath::ClampValue(
  double value, const double range[2], double *clamped_value)
{
  if (range && clamped_value)
    {
    if (value < range[0])
      {
      *clamped_value = range[0];
      }
    else if (value > range[1])
      {
      *clamped_value = range[1];
      }
    else
      {
      *clamped_value = value;
      }
    }
}

// ---------------------------------------------------------------------------
inline double vtkMath::ClampAndNormalizeValue(double value,
                                              const double range[2])
{
  assert("pre: valid_range" && range[0]<=range[1]);
  
  double result;
  if(range[0]==range[1])
    {
      result=0.0;
    }
  else
    {
      // clamp
      if(value<range[0])
        {
          result=range[0];
        }
      else
        {
          if(value>range[1])
            {
              result=range[1];
            }
          else
            {
              result=value;
            }
        }

      // normalize
      result=( result - range[0] ) / ( range[1] - range[0] );
    }

  assert("post: valid_result" && result>=0.0 && result<=1.0);

  return result;
}

#endif