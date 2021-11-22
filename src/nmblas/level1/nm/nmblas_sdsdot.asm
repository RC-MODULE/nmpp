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
// nmblas_sdsdot returns the dot product b + x^T * y of two n-vectors x
// and  y.  The  result  is internally  computed  using float precision
// arithmetic and casted to a single precision scalar  just before being
// returned.
//
// Arguments
// =========
//
// N       (input)                       const int
//         On entry, N specifies the length of the vector x. N  must  be
//         at least zero. Unchanged on exit.
//
// B       (input)                       const float
//         On entry, B specifies the scalar b. Unchanged on exit.
//
// X       (input)                       const float *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   float  ),
//         that contains the vector x. Unchanged on exit.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// Y       (input)                       const float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float  ),
//         that contains the vector y. Unchanged on exit.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// ---------------------------------------------------------------------
///

global _nmblas_sdsdot:label;
extern _fpu_sdsdot:label;

begin "text"
<_nmblas_sdsdot>
  ar5 = ar7 - 2;
  push ar0,gr0;//array x and incx
  push ar1,gr1;//array y and incy
  push ar2,gr2;//param b type float 
  push gr5,ar5;//ammount of elements
  
  
  
  gr5 = [--ar5];//N
  gr2 = [--ar5] with gr5;//B
  if <= delayed goto END;
  ar0 = [--ar5];//array_x//X
  gr0 = [--ar5];//inc_x//INCX
  ar1 = [--ar5];//array_y//Y
  gr1 = [--ar5];//inc_y//INCY

  call _fpu_sdsdot;
  <END>
  pop gr5,ar5;//ammount of elements
  pop ar2,gr2;//param b type float 
  pop ar1,gr1;//array y and incy
  pop ar0,gr0;//array x and incx
  return;

end "text";