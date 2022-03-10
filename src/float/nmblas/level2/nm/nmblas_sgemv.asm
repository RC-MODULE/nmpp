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
// ATL_srefgemv performs one of the matrix-vector operations
//
//    y := alpha * op( A ) * x + beta * y,
//
// where op( X ) is one of
//
//    op( X ) = X   or   op( X ) = X`(trans).
//
// where  alpha and beta are scalars, x and y are vectors and op( A ) is
// an m by n matrix.
//
// Arguments
// =========
//
// TRANS   (input)                       const enum ATLAS_TRANS
//         On entry,  TRANS  specifies the  operation to be performed as
//         follows:
//
//            TRANS = AtlasNoTrans    y := alpha*A *x + beta*y,
//
//            TRANS = AtlasConj       y := alpha*A *x + beta*y,
//
//            TRANS = AtlasTrans      y := alpha*A'*x + beta*y,
//
//            TRANS = AtlasConjTrans  y := alpha*A'*x + beta*y.
//
//         Unchanged on exit.
//
// M       (input)                       const int
//         On entry,  M  specifies  the number of rows of  the matrix  A
//         when TRANS = AtlasNoTrans or TRANS = AtlasConj,  and the num-
//         ber of columns of the matrix  A otherwise. M must be at least
//         zero. Unchanged on exit.
//         M HAS TO BE ONLY EVEN!!!!!!!!!!!!!!!! 
//
// N       (input)                       const int
//         On entry, N  specifies  the number of columns of the matrix A
//         when TRANS = AtlasNoTrans or TRANS = AtlasConj,  and the num-
//         ber of rows of the matrix A otherwise. N must be at least ze-
//         ro. Unchanged on exit.
//         N HAS TO BE ONLY EVEN!!!!!!!!!!!!!!!!  
//
// ALPHA   (input)                       const float
//         On entry, ALPHA specifies the scalar alpha.   When  ALPHA  is
//         supplied as zero then  A and X  need not be set on input. Un-
//         changed on exit.
//
// A       (input)                       const float *
//         On entry,  A  points  to an array of size equal to or greater
//         than   LDA * ka * sizeof(   float   ), where  ka  is  n  when
//         TRANS = AtlasNotrans or TRANS = AtlasConj, and  m  otherwise.
//         Before entry, when TRANS = AtlasNotrans or TRANS = AtlasConj,
//         the leading m by n part of the array  A  must contain the ma-
//         trix coefficients,  and otherwise the leading n by m  part of
//         the array A  must contain the matrix coefficients.  Unchanged
//         on exit.
//
// LDA     (input)                       const int
//         On entry, LDA  specifies the leading dimension of A as decla-
//         red  in  the  calling  (sub) program.  LDA  must be  at least
//         MAX( 1, m )  when  TRANS = AtlasNotrans or TRANS = AtlasConj,
//         and MAX( 1, n ) otherwise. Unchanged on exit.
//
// X       (input)                       const float *
//         On entry,  X  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   float   ),
//         that contains the vector x. Unchanged on exit.
//
// INCX    (input)                       const int
//         On entry, INCX specifies the increment for the elements of X.
//         INCX MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// BETA    (input)                       const float
//         On entry,  BETA  specifies the scalar  beta.   When  BETA  is
//         supplied as zero then Y  need not be set on input.  Unchanged
//         on exit.
//
// Y       (input/output)                float *
//         On entry,  Y  points to the  first entry to be accessed of an
//         incremented array of size equal to or greater than
//            ( 1 + ( m - 1 ) * abs( INCY ) ) * sizeof(   float   ),
//         that contains the vector y.  Before entry with BETA non-zero,
//         the incremented array  Y  must contain the vector y. On exit,
//         Y is overwritten by the updated vector y.
//
// INCY    (input)                       const int
//         On entry, INCY specifies the increment for the elements of Y.
//         INCY MUST BE ONLY ONE OTHER INCREMENTS ARE PROHIBITED. Unchanged on exit.
//
// ---------------------------------------------------------------------
//

global _nmblas_sgemv:label;
extern _fpu_sgemv:label;
extern _fpu_sgemv_trans:label;

begin "text"
<_nmblas_sgemv>
  
  ar5 = ar7 - 2;
  push ar0,gr0;
  push ar1,gr1;
  push ar2,gr2;
  push ar3,gr3;
  push ar4,gr4;
  push ar5,gr5;
  push ar6,gr6;

  gr3 = [--ar5];//enum to chose transponated or not the matrix a//TRANS
  gr5 = [--ar5];//On entry, M specifies  the number of rows of  the matrix in case notrans oterwise number of collums A//int//N
  gr5;
  if <= delayed goto END;
  gr6 = [--ar5];//On entry, N specifies  the number of collums of the matrix A//int//M
  gr6;
  if <= delayed goto END;
  gr4 = [--ar5];//load alpha//ALPHA
  ar0 = [--ar5];//the pointer onto the matrix//*float//A
  ar3 = [--ar5];//LDA lidding demention of the matrix//int//LDA
  ar1 = [--ar5];//the vectore x//*float//X
  gr1 = [--ar5];//inc of x//int//INCX
  ar4 = [--ar5] with gr3; //beta//float//BETA
  if <>0 delayed goto CALL_SGEMV_TRANS;
  ar2 = [--ar5];//the y vecore inout//*float//Y
  gr2 = [--ar5];//inc of y//int//INCY

  call _fpu_sgemv;
  pop ar6,gr6;
  pop ar5,gr5;
  pop ar4,gr4;
  pop ar3,gr3;
  pop ar2,gr2;
  pop ar1,gr1;
  pop ar0,gr0;
  return;

<CALL_SGEMV_TRANS>
  call _fpu_sgemv_trans;
<END>
  pop ar6,gr6;
  pop ar5,gr5;
  pop ar4,gr4;
  pop ar3,gr3;
  pop ar2,gr2;
  pop ar1,gr1;
  pop ar0,gr0;
  return;


end "text";