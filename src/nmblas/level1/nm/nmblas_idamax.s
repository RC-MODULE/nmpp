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
// nmblas_idamax  returns the index in an n-vector x of the first element
// having maximum absolute value.
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
// ---------------------------------------------------------------------
//

global _nmblas_idamax:label;
extern _fpu_idamax:label;

begin "text"
<_nmblas_idamax>  
  ar5 = ar7 - 2;
  
  push ar5,gr5;
  push ar0,gr0;

  gr5 = [--ar5];//N
  ar0 = [--ar5];//X
  gr0 = [--ar5];//INCX

  call _fpu_idamax;

  pop ar0,gr0;
  pop ar5,gr5;
  return;
end "text";