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
// ATL_srefrotm applies the modified-Givens rotation  H  stored in PARAM
// to the two n-vectors x and y as follows:
//
//    [ x_i ]   [ h_11 h_12 ] [ x_i ]
//    [ y_i ] = [ h_21 h_22 ] [ y_i ]    for all i = 1 .. n.
//
// If n <= 0 or if H is the identity matrix, this subroutine returns im-
// mediately.
//
// See ``Basic Linear Algebra Subprograms for Fortran Usage'' by C. Law-
// son, R. Hanson, D. Kincaid and F. Krogh, ACM Transactions on Mathema-
// tical Software, 1979, 5(3) pp 308-323, for further information.
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
//         cremented array  X are rotated with the entries of the incre-
//         mented array  Y.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX must not be zero. Unchanged on exit.
//
// Y       (input/output)                float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
//         that contains the vector y.  On exit,  the entries of the in-
//         cremented array  Y are rotated with the entries of the incre-
//         mented array  X.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY must not be zero. Unchanged on exit.
//
// PARAM   (input)                       const float *
//         On entry, PARAM is an array of dimension at least 5 that con-
//         tains the matrix  H  as encoded by the routine ATL__refrotmg.
//         Unchanged on exit.
//
// ---------------------------------------------------------------------
//


global _nmblas_srotm : label;
extern _fpu_srotm : label;

begin "text"
<_nmblas_srotm>
  
  ar5 = ar7 - 2;
  
  push ar5,gr5;
  push ar0,gr0;
  push ar1,gr1;
  push ar2,gr2;

  gr5 = [--ar5];//N ammount of elements
  ar0 = [--ar5];//addres of x array (input)
  gr0 = [--ar5];//offset of x array
  ar1 = [--ar5];//addres of y array (output)
  gr1 = [--ar5];//offset of y array
  ar2 = [--ar5];//addres of param(size 5)
  
  call _fpu_srotm;

  pop ar2,gr2;
  pop ar1,gr1;
  pop ar0,gr0;
  pop gr5,ar5;
  return;
end "text";