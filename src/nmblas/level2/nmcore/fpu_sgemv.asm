global _fpu_sgemv : label;

nobits "nobits"
  buff_to_dublicate : long[2];
end "nobits";

begin "text"
<_fpu_sgemv>
  //gr3 - enum to chose transponated or not the matrix a 
  //gr5 - On entry, M specifies  the number of rows of  the matrix  A//int
  //gr6 - On entry, N specifies  the number of collums of the matrix A//int
  //gr4 - load alpha
  //ar0 - the pointer onto the matrix//*double
  //ar3 - LDA lidding demention of the matrix//int
  //ar1 - the vectore x//*float
  //gr1 - inc of x//int
  //ar4 - beta//double
  //ar2 - the y vecore inout//*float
  //gr2 - inc of y//int

  ar5 = buff_to_dublicate;
  [ar5++] = gr4;
  [ar5++] = gr4;
  [ar5++] = ar4;
  [ar5++] = ar4;

  fpu 2 rep 1 vreg7 = [--ar5];//load betta
  fpu 1 rep 1 vreg7 = [--ar5];//load alpha

//list of registers usied in the program and there perpose
//
//(ar0,gr0 - matrix)
//(ar1,gr1 - x)
//(ar2-y),
//gr2 saves address of y 
//(ar3,gr3 matrix)
//(ar4,gr4 -offset to next collume)
//(ar5 saves gr6 ammount of collumes devided by 2)
//(gr5 quotient of rows)
//(ar6,gr6 - offset ot nex collume)
//gr7 counter of collumes
//(vlen saves the reminder of rows)
//sir

//gr1 offset of x
//gr4 2 or -2 to provide movement of pointer from one collume to another one 
//gr6 eqls gr4
//
  

  //computting the addresses of poiters to the matrix
  gr0 = ar3;
  ar3 = ar0+gr0 with gr0 = gr0<<1;//address of the first element of the odd row
  ar4 = ar0 with gr3 = gr0;
  //
  ar6 = ar3 with gr1 = gr1<<1;//offset of x 
  gr4 = 2;//offset to the next collume
  gr7 = gr6>>1;    
  ar5 = gr7 with gr6 = gr4;
  gr7 = gr5<<26;
  gr7 = gr7>>27;//reminder of rows
  gr5 = gr5>>6;//quotient of rows
  if =0 delayed goto REMAINDER;
  vlen = gr7;
  gr2 = ar2;
<MAIN_LOOP>
  gr7 = ar5;
  //y
  fpu 2 rep 32 vreg0 = [ar2++];//load y 
  fpu 2 .float vreg2 = vreg0*.retrive(vreg7);//got betta*y
  fpu 0 vreg2 = fpu 2 vreg2;
<LOOP_COLLUME_BY_COLLUME> 
  //x 
  fpu 1 rep 32 vreg0 = [ar1];//load the first elemnt of x
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7);//got alpha*x
  fpu 0 vreg3 = fpu 1 vreg2;
  ar1 = ar1+gr1 with gr7--;
  //matrix
  ar0 = ar4;
  ar3 = ar6;
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load the even collume of matrix
  fpu 0 rep 32 vreg1 = [ar3++gr3];//load the odd collume of the matrix
  fpu 0 .matrix vreg2 = (vreg0,vreg1)*vreg3+vreg2;
  if <>0 delayed goto LOOP_COLLUME_BY_COLLUME;
  ar4 = ar4+gr4;
  ar6 = ar6+gr6;
  //upload
  ar2 = gr2;
  fpu 0 rep 32 [ar2++] = vreg2;
  ar4 = ar0 with gr4 = -gr4;
  ar6 = ar3 with gr1 = -gr1;
  ar1 = ar1+gr1 with gr5--;
  if <>0  delayed goto MAIN_LOOP;
  gr6 = gr4;
  gr2 = ar2;
<REMAINDER> 
  gr7 = vlen;
  gr7;
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  gr7 = ar5;
  //y
  fpu 2 rep vlen vreg0 = [ar2++];//load y 
  fpu 2 .float vreg2 = vreg0*.retrive(vreg7);//got betta*y
  fpu 0 vreg2 = fpu 2 vreg2;
<LOOP_COLLUME_BY_COLLUME_REM> 
  //x 
  fpu 1 rep vlen vreg0 = [ar1];//load the first elemnt of x
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7);//got alpha*x
  fpu 0 vreg3 = fpu 1 vreg2;
  ar1 = ar1+gr1 with gr7--;
  //matrix
  ar0 = ar4;
  ar3 = ar6;
  fpu 0 rep vlen vreg0 = [ar0++gr0];//load the even collume of matrix
  fpu 0 rep vlen vreg1 = [ar3++gr3];//load the odd collume of the matrix
  fpu 0 .matrix vreg2 = (vreg0,vreg1)*vreg3+vreg2;
  if <>0 delayed goto LOOP_COLLUME_BY_COLLUME_REM;
  ar4 = ar4+gr4;
  ar6 = ar6+gr6;
  //upload
  ar2 = gr2;
  fpu 0 rep vlen [ar2++] = vreg2;
<END>
return;
end "text";