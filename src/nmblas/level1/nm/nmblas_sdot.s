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
// nmblas_sdot returns the dot product x^T * y of two n-vectors x and y.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//
// X       (input)                       const float *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   float   ),
//         that contains the vector x. Unchanged on exit.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// Y       (input)                       const float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
//         that contains the vector y. Unchanged on exit.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit. 
//
// ---------------------------------------------------------------------

global _nmblas_sdot:label;
extern _fpu_sdot:label;

begin "text"
<_nmblas_sdot>
  ar5 = ar7 - 2;
  
  push ar5,gr5;
  push ar0,gr0;
  push ar1,gr1;

  gr5 = [--ar5];//ammount of elements
  ar0 = [--ar5];//address of x array
  gr0 = [--ar5];//inc x
  ar1 = [--ar5];//address of y array
  gr1 = [--ar5];//inc y

  call _fpu_sdot;

  pop ar1,gr1;
  pop ar0,gr0;
  pop ar5,gr5;
  return;
end "text";