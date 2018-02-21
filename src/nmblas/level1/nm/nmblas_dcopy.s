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
// ATL_drefcopy copies the entries of an n-vector x into an n-vector y.
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
// Y       (input/output)                double *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   double  ),
//         that contains the vector y.  On exit,  the entries of the in-
//         cremented array  X are  copied into the entries of the incre-
//         mented array  Y.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// ---------------------------------------------------------------------
///

global _nmblas_dcopy:label;
extern _fpu_dcopy:label;
begin "text"
<_nmblas_dcopy>
  ar5 = ar7-2;
  push ar5,gr5;
  push ar0,gr0;
  push ar1,gr1;

  gr5 = [--ar5];//ammount of elements//N
  ar0 = [--ar5] with gr5;//address of x array//X
  if <= delayed goto END;
  gr0 = [--ar5];//offset of x array//INCX
  ar1 = [--ar5];//address of y array//Y
  gr1 = [--ar5];//offset of y array//INCY

  call _fpu_dcopy;

<END>
  pop ar1,gr1;
  pop ar0,gr0;
  pop ar5,gr5;
return;
end "text";