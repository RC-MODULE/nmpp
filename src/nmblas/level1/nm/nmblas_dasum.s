///////////
// nmblas (NeuroMatrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at RC "Module" Moscow 
// Year 2017
///////////

////////// the purpose of function
//nmblas_dasum returns the sum of absolute values of the entries of a vector x.
//  Arguments
// =========
//  N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//  X       (input)                       const double *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   double  ),
//         that contains the vector x. Unchanged on exit.
//  INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX must not be zero. Unchanged on exit.
//


global _nmblas_dasum:label;
extern _fpu_dasum:label;

begin "text"
<_nmblas_dasum>
  ar5 = ar7-2;
  push ar0,gr0;
  push ar5,gr5;

  gr5 = [--ar5];//amount of elements//N
  ar0 = [--ar5];//address of array//X
  gr0 = [--ar5];//offset of array//NCX

  call _fpu_dasum;

  pop ar5,gr5;
  pop ar0,gr0;

  return;
end "text";