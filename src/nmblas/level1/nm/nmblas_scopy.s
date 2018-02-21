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
// nmblas_scopy copies the entries of an n-vector x into an n-vector y.
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
// Y       (input/output)                float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
//         that contains the vector y.  On exit,  the entries of the in-
//         cremented array  X are  copied into the entries of the incre-
//         mented array  Y.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// ---------------------------------------------------------------------
//

global _nmblas_scopy:label;
extern _fpu_scopy:label;

begin "text"
<_nmblas_scopy>
  ar5 = ar7-2;
  push gr5,ar5;
  push gr0,ar0;
  push gr1,ar1;

  gr5 = [--ar5];//N ammount of elements
  ar0 = [--ar5];//addres of x array (input)
  gr0 = [--ar5];//offset of x array
  ar1 = [--ar5];//addres of y array (output)
  gr1 = [--ar5];//offset of y array

  call _fpu_scopy;


  pop ar1,gr1;
  pop ar0,gr0;
  pop gr5,ar5;
  return;
end "text";