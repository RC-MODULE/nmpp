///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc. 

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017
///////////

//Purpose
// =======
//
// ATL_drefscal performs the following operation:
//
//    x := alpha * x,
//
// where alpha is a scalar and x is an n-vector.
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
// X       (input/output)                double *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   double  ),
//         that contains the vector x.  On exit,  the entries of the in-
//         cremented array X are mutiplied by alpha.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX must not be zero. Unchanged on exit.
//
// ---------------------------------------------------------------------
//


global _nmblas_dscal:label;
extern _fpu_dscal:label;

begin "text"
<_nmblas_dscal>
  ar5 = ar7 -2;
  push ar0,gr0;
  push ar5,gr5;

  gr5 = [--ar5];//ammount of element//N
  ar5--;
  fpu 0 rep 1 vreg0 = [--ar5];//alpha//ALPHA
  ar0 = [--ar5];//addres of x array//X
  gr0 = [--ar5];//offset of x array//INCX

  call _fpu_dscal;
  
  pop ar5,gr5;
  pop ar0,gr0;
  return;

end "text";