///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc. 

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017
///////////

// Purpose
// =======
//
// nmblas_dswap swaps the entries of two n-vectors x and y.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//
// X       (input/output)                double *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   double  ),
//         that contains the vector x.  On exit,  the entries of the in-
//         cremented array  X are swapped with the entries of the incre-
//         mented array  Y.
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
//         cremented array  Y are swapped with the entries of the incre-
//         mented array  X.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// ---------------------------------------------------------------------
///

global _nmblas_dswap:label;
extern _fpu_dswap:label;

begin "text"
<_nmblas_dswap >
  ar5 = ar7 -2;
  push ar0,gr0;
  push ar1,gr1;  
  push ar5,gr5;
  
  gr5 = [--ar5];//ammount of elements//N
  ar0 = [--ar5];//address of x array//X
  gr0 = [--ar5];//offset of x array//INCX
  ar1 = [--ar5];//address of y array//Y
  gr1 = [--ar5];//offset of y array//INCY

  call _fpu_dswap;

  pop ar5,gr5;
  pop ar1,gr1;  
  pop ar0,gr0;
  return;
end "text";