///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc. 

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017
///////////



//The purpose of the function
// =======
//
// nmblas_daxpy performs the following operation:
//
//    y := y + alpha * x,
//
// where alpha is a scalar and x and y are two n-vectors.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//
// ALPHA   (input)                       const double
//         On entry, ALPHA specifies the scalar alpha.   When  ALPHA  is
//         supplied as zero, then the entries of the incremented array X
//         need not be set on input. Unchanged on exit.
//
// X       (input)                       const double *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   double  ),
//         that contains the vector x. Unchanged on exit.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX must not be zero. Unchanged on exit.
//
// Y       (input/output)                double *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   double  ),
//         that contains the vector y.  On exit,  the entries of the in-
//         cremented array  Y are updated with the scaled entries of the
//         incremented array  X.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// ---------------------------------------------------------------------
///

global _nmblas_daxpy:label;
extern _fpu_daxpy:label;

begin "text"
<_nmblas_daxpy>
  
  ar5 = ar7-2;
  push ar0,gr0;
  push ar1,gr1;
  push ar5,gr5;
 
  gr5 = [--ar5];//ammount of elements of vectore
  ar5--;
  fpu 0 rep 1 vreg0 = [--ar5];//alpha
  ar0 = [--ar5];//address of x array
  gr0 = [--ar5];//offset of x array 
  ar1 = [--ar5];//address of y array
  gr1 = [--ar5];//offset of y array
  
  call _fpu_daxpy;
 
  pop ar5,gr5;
  pop ar1,gr1;  
  pop ar0,gr0;
  
  return;
end "text";