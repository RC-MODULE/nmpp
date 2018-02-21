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
// nmblas_sswap swaps the entries of two n-vectors x and y.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//
// X       (input/output)                float *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   float   ),
//         that contains the vector x.  On exit,  the entries of the in-
//         cremented array  X are swapped with the entries of the incre-
//         mented array  Y.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// Y       (input/output)                float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
//         that contains the vector y.  On exit,  the entries of the in-
//         cremented array  Y are swapped with the entries of the incre-
//         mented array  X.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// ---------------------------------------------------------------------

global _nmblas_sswap:label;
extern _fpu_sswap:label;
begin "text"
<_nmblas_sswap>
  ar5 = ar7-2;
  push ar0,gr0;
  push ar1,gr1;
  push ar5,gr5;


  gr5 = [--ar5];//N ammount of elements
  ar0 = [--ar5];//SX address of the first array
  gr0 = [--ar5];//INCX offset of the fist array
  ar1 = [--ar5];//SY address of the second array
  gr1 = [--ar5];//INCY adress of the second array

  call _fpu_sswap;

  pop ar5,gr5;
  pop ar1,gr1;
  pop ar0,gr0;    
  return;
end "text";