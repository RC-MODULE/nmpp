global _fpu_sgemv_trans : label;

nobits "nobits"
  buff_to_dublicate : long[2];
end "nobits";

begin "text"
<_fpu_sgemv_trans>
  ar5 = gr5;
  gr5 = gr6;
  gr6 = ar5;
  //gr3 - enum to chose transponated or not the matrix a 
  //gr5 - On entry, M specifies  the number of collums//int
  //gr6 - On entry, N specifies  the number of rows//int
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

//description of perpose of registers
// ar0 pointer of even collums (matrix located in a mamorry as collume maj)
// gr0 saves gr3
// ar1 x 
// gr1 eqls 2 to offset x  
// ar2 y
// gr2 saves ar2 to upload y 
// ar3 pointer of odd collums
// gr3 rows devided by 2
// ar4 saves ar0
// gr4 offset to provide reading of even collumes
// gr5 is quotient of collums
// ar6 saves ar3
// gr6 works as gr4 but for odd collums
// gr7 is a reminder of collums
  
  gr3 = gr6>>1;//ammount of rows divided by 2 
  gr0 = ar3;
  ar3 = ar0+gr0 with gr4 = gr0<<1;
  ar4 = ar0 with gr6 = gr4;
  ar6 = ar3 with gr0 = gr3;

  gr7 = gr5<<26;
  gr7 = gr7>>27;
  gr5 = gr5>>6;
  
  if =0 delayed goto REMINDER with gr7;
  gr1 = 2;

<MAIN_LOOP>
  gr2 = ar2;//address of y
  gr3 = gr0;//ammount of rows
  fpu 2 rep 32 vreg0 = [ar2++];//load y 
  fpu 2 .float vreg1 = vreg0*.retrive(vreg7);//got betta*y
  fpu 0 vreg2 = fpu 2 vreg1;
  <LOOP_CULLUME_BY_COLLUME>
  fpu 1 rep 32 vreg0 = [ar1];//load x
  fpu 1 .float vreg1 = vreg0*.retrive(vreg7);//got alpha*x
  fpu 0 vreg3 = fpu 1 vreg1; 
  ar1 = ar1+gr1 with gr3--;
  ar0 = ar4;
  ar3 = ar6;
  fpu 0 rep 32 vreg0 = [ar0++];//load even collume of the matrix
  fpu 0 rep 32 vreg1 = [ar3++];//load odd collume of the matrix
  fpu 0 .matrix vreg2 = vreg3*(vreg0,vreg1) + vreg2;
  if <>0 delayed goto LOOP_CULLUME_BY_COLLUME;
  ar4 = ar4+gr4;
  ar6 = ar6+gr6;
  //upload the result
  ar2 = gr2 with gr1 = -gr1;
  fpu 0 rep 32 [ar2++] = vreg2;
  ar1 = ar1+gr1 with gr5--;
  if <>0 delayed goto MAIN_LOOP with gr7;
  ar4 = ar0 with gr4 = -gr4 noflags;
  ar6 = ar3 with gr6 = -gr6 noflags;
  
<REMINDER>
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;

  gr2 = ar2;//address of y
  gr3 = gr0;//ammount of rows
  fpu 2 rep vlen vreg0 = [ar2++];//load y 
  fpu 2 .float vreg1 = vreg0*.retrive(vreg7);//got betta*y
  fpu 0 vreg2 = fpu 2 vreg1;
  <LOOP_CULLUME_BY_COLLUME_REM>
  fpu 1 rep vlen vreg0 = [ar1];//load x
  fpu 1 .float vreg1 = vreg0*.retrive(vreg7);//got alpha*x
  fpu 0 vreg3 = fpu 1 vreg1; 
  ar1 = ar1+gr1 with gr3--;
  ar0 = ar4;
  ar3 = ar6;
  fpu 0 rep vlen vreg0 = [ar0++];//load even collume of the matrix
  fpu 0 rep vlen vreg1 = [ar3++];//load odd collume of the matrix
  fpu 0 .matrix vreg2 = vreg3*(vreg0,vreg1) + vreg2;
  if <>0 delayed goto LOOP_CULLUME_BY_COLLUME_REM;
  ar4 = ar4+gr4;
  ar6 = ar6+gr6;
  //upload the result
  ar2 = gr2 with gr1 = -gr1;
  fpu 0 rep vlen [ar2++] = vreg2;

<END>
return;
end "text";