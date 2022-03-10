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
 // nmblas_dsdot returns the dot product x^T * y of two n-vectors x and
 // y. The result is internally computed using double precision arithmetic.
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
 //         INCX must not be zero. Unchanged on exit.
 //
 // Y       (input)                       const float *
 //         On entry,  Y  points to the  first entry to be accessed of an
 //         incremented array of size equal to or greater than
 //            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
 //         that contains the vector y. Unchanged on exit.
 //
 // INCY    (input)                       const int
 //         On entry, INCY specifies the increment for the elements of Y.
 //         INCY must not be zero. Unchanged on exit.
 //
 // ---------------------------------------------------------------------
 ///

global _nmblas_dsdot:label;
extern _fpu_dsdot:label;

begin "text"
<_nmblas_dsdot>
  ar5 = ar7 - 2;
  push ar0,gr0;//array x and incx
  push ar1,gr1;//array y and incy
  push gr5,ar5;//ammount of elements
  
  
  
  gr5 = [--ar5];//N
  ar0 = [--ar5];//array_x//X
  gr0 = [--ar5];//inc_x//INCX
  ar1 = [--ar5];//array_y//Y
  gr1 = [--ar5];//inc_y//INCY

  call _fpu_dsdot;

  pop gr5,ar5;//ammount of elements
  pop ar1,gr1;//array y and incy
  pop ar0,gr0;//array x and incx
  return;

end "text";