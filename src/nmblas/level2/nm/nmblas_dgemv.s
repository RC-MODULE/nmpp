global _nmblas_dgemv:label;
extern _fpu_dgemv:label;
extern _fpu_dgemv_trans:label;  

begin "text"
<_nmblas_dgemv>
  ar5 = ar7 - 2;
  push ar0,gr0;
  push ar1,gr1;
  push ar2,gr2;
  push ar3,gr3;
  push ar6,gr6;


  gr3 = [--ar5];//enum to chose transponated or not the matrix a 
  gr5 = [--ar5];//On entry, M specifies  the number of rows of  the matrix  A//int
  gr5;
  if <= delayed goto END;
  gr6 = [--ar5];//On entry, N specifies  the number of columns of the matrix A//int
  gr6;
  if <= delayed goto END;
  ar5--;
  fpu 2 rep 1 vreg7 = [--ar5];//alpha//double
  ar0 = [--ar5];//the pointer onto the matrix//*double
  ar3 = [--ar5];//LDA lidding demention of the matrix//int
  ar1 = [--ar5];//the vectore x//*double
  gr1 = [--ar5];//inc of x//int
  fpu 3 rep 1 vreg7 = [--ar5];//beta//double
  gr3;
  .align;
  if <>0 delayed goto CALL_DGEMV_TRANS;
  ar2 = [--ar5];//the y vecore inout//*double
  gr2 = [--ar5];//inc of y//int

  call _fpu_dgemv; 
  pop ar6,gr6;
  pop ar3,gr3;
  pop ar2,gr2;
  pop ar1,gr1;
  pop ar0,gr0;
  return;
  <CALL_DGEMV_TRANS>
  call _fpu_dgemv_trans;
<END>
  pop ar6,gr6;
  pop ar3,gr3;
  pop ar2,gr2;
  pop ar1,gr1;
  pop ar0,gr0;
  return;

end "text";