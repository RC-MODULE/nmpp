///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

// Purpose
// =======
//
// nmbals_ddot returns the dot product x^T * y of two n-vectors x and y.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
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
// Y       (input)                       const double *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   double  ),
//         that contains the vector y. Unchanged on exit.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// ---------------------------------------------------------------------
///

global _nmblas_ddot:label;
extern _fpu_ddot:label;

begin "text"
<_nmblas_ddot>
  ar5 = ar7 - 2;
  push ar0,gr0;
  push ar1,gr1;
  push gr5,ar5;
  
  
  gr5 = [--ar5];//N
  ar0 = [--ar5];//arr_x
  gr0 = [--ar5];//inc_x
  ar1 = [--ar5];//arr_y
  gr1 = [--ar5];//inc_y
  
  call _fpu_ddot;

  pop gr5,ar5;//ammount of elements
  pop ar1,gr1;//array y and incy
  pop ar0,gr0;//array x and incx
  return;

end "text";