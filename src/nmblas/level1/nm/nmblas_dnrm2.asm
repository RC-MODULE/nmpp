///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc. 

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017
///////////

//
// Purpose
// =======
//
// ATL_drefnrm2 returns the 2-norm of an n-vector x.
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
///

global _nmblas_dnrm2:label;
extern _fpu_dnrm2:label;

begin "text"
<_nmblas_dnrm2>
  ar5 = ar7 - 2;
  push ar5,gr5;
  push ar0,gr0;
  gr5 = [--ar5];//ammount of elements//N
  ar0 = [--ar5];//address of array//X
  gr0 = [--ar5];//offset of array//INCX
  call _fpu_dnrm2;

  pop ar0,gr0;
  pop ar5,gr5;
  return;
end "text";