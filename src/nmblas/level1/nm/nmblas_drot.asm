///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
// Copyright (c) RC Module Inc. 

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017
///////////

// Purpose
// nmbals_drot  applies a  plane  rotation to the two n-vectors x and y.
// This routine computes:
//
//    [ x_i ]   [ c  s ] [ x_i ]
//    [ y_i ] = [ -s c ] [ y_i ]    for all i = 1 .. n.
//
// If n <= 0 or if c = 1 and s = 0, this subroutine returns immediately.
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
//         cremented array  X are rotated with the entries of the incre-
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
//         cremented array  Y are rotated with the entries of the incre-
//         mented array  X.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// C       (input)                       const double
//         On entry, C specifies the scalar c definiting the plane rota-
//         tion. Unchanged on exit.
//
// S       (input)                       const double
//         On entry, S specifies the scalar s definiting the plane rota-
//         tion. Unchanged on exit.
//
// ---------------------------------------------------------------------


global _nmblas_drot : label;
extern _fpu_drot : label;

begin "text"
<_nmblas_drot>
  
  ar5 = ar7 - 2;
  
  push ar5,gr5;
  push ar0,gr0;
  push ar1,gr1;

  gr5 = [--ar5];//N ammount of elements
  ar0 = [--ar5];//addres of x array (input)
  gr0 = [--ar5];//offset of x array
  ar1 = [--ar5];//addres of y array (output)
  gr1 = [--ar5];//offset of y array
  ar5--;
  fpu 0 rep 1 vreg7 = [--ar5];//load c 
  fpu 0 rep 1 vreg6 = [--ar5];//load s  
  
  call _fpu_drot;

  pop ar1,gr1;
  pop ar0,gr0;
  pop gr5,ar5;
  return;
end "text";