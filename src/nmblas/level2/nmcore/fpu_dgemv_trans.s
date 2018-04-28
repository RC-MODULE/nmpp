 global _fpu_dgemv_trans:label;

  //gr3 = [--ar5];//enum to chose transponated or not the matrix A
  //gr5 = [--ar5];//On entry, M specifies  the number of collums of  the matrix  A//int
  //gr6 = [--ar5];//On entry, N specifies  the number of rows of the matrix A//int
  //fpu 2 rep 1 vreg7 = [--ar5];//alpha//double
  //ar0 = [--ar5];//the pointer onto the matrix//*double
  //ar3 = [--ar5];//LDA lidding demention of the matrix//int
  //ar1 = [--ar5];//the vectore x//*double
  //gr1 = [--ar5];//inc of x//int
  //fpu 3 rep 1 vreg7 = [--ar5];//beta//double
  //ar2 = [--ar5];//the y vecore inout//*double
  //gr2 = [--ar5];//inc of y//int
 begin "text"
 <_fpu_dgemv_trans>
push ar4,gr4;
  gr1 = gr1<<1;
  gr2 = gr2<<1;
  
  ar4 = ar0; 
  gr0 = 2;
  //gr4 = gr5<<1;
  gr4 = ar3;
  gr4 = gr4<<1;
  ar6 = gr6;
  ar3 = ar1;//save address of x array

  gr7 = gr5<<27;//REMAINDER of collums
  gr7 = gr7>>27;
  gr5 = gr5>>5;//QUOTIEN of collums

  if =0 delayed goto REMAINDER_MAIN;
<MAIN_LOOP>
  gr6 = ar6;
  ar5 = ar2;
  gr6 = gr6>>5;
 // ar1 = ar3;
  fpu 3 rep 32 vreg0 = [ar2++gr2];//load y
  if =0 delayed goto CASE_AMMOUNT_OF_ROWS_LT_32;
  fpu 3 .double vreg0 = vreg0*.retrive(vreg7);//getting betta*y
  fpu 0 vreg2 = fpu 3 vreg0;//coppy betta*y

<MAIN_LOOP_32_ROWS>
  fpu 2 rep 32 vreg0 = [ar1++gr1];//load x 
  gr3 = true;
  fpu 2 .double vreg0 = vreg0*.retrive(vreg7);//getting alpha*x
  fpu 0 vreg1 = fpu 2 vreg0;//coppy alpha*x
//the loop below is very slow becoze matrix is located in one bank of memorry   
  <LOOP_ROW_BY_ROW_32>
    gr3 = gr3>>1;
    ar0 = ar4;
    fpu 0 rep 32 vreg3 = [ar0++gr0];//load the collume of martix A 
    if <>0 delayed goto LOOP_ROW_BY_ROW_32;
    fpu 0 .double vreg2 = vreg3*.retrive(vreg1) + vreg2;//getting alpha*A*x+betta*y
    ar4 = ar4+gr4;
  gr6--;
  if <>0 goto MAIN_LOOP_32_ROWS;

<CASE_AMMOUNT_OF_ROWS_LT_32>
  gr6 = ar6;
  gr6 = gr6<<27;
  gr6 = gr6>>27;
  if =0 delayed goto UPLOAD_THE_RESULT_MAIN_LOOP;
  gr6--;
  vlen = gr6;
  fpu 2 rep vlen vreg0 = [ar1++gr1];//load x 
  gr6++;
  fpu 2 .double vreg0 = vreg0*.retrive(vreg7);//getting alpha*x
  fpu 0 vreg1 = fpu 2 vreg0;//coppy alpha*x
  
  <LOOP_ROW_BY_ROW>
    gr6--;
    ar0 = ar4;
    fpu 0 rep 32 vreg3 = [ar0++gr0];//load the collume of martix A 
    if <>0 delayed goto LOOP_ROW_BY_ROW;
    fpu 0 .double vreg2 = vreg3*.retrive(vreg1) + vreg2;//getting alpha*A*x+betta*y
    ar4 = ar4+gr4;
 ///upload the result
<UPLOAD_THE_RESULT_MAIN_LOOP>
    ar4 = ar0;
    gr4 = -gr4;
    gr1 = -gr1;
    ar1 = ar1+gr1;
    gr5--;
    if <>0 delayed goto MAIN_LOOP;
    ar2 = ar5;
    fpu 0 rep 32 [ar2++gr2] = vreg2;//upload result

 
////////////////////////////////////////////////////////////////////////////////////////////////////REMINDER
<REMAINDER_MAIN>
  gr7;
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  gr6 = ar6;
  ar5 = ar2;
  gr6 = gr6>>5;
  //ar1 = ar3;
  fpu 3 rep vlen vreg0 = [ar2++gr2];//load y
  if =0 delayed goto CASE_AMMOUNT_OF_ROWS_LT_32_REM;
  fpu 3 .double vreg0 = vreg0*.retrive(vreg7);//getting betta*y
  fpu 0 vreg2 = fpu 3 vreg0;//coppy betta*y

<MAIN_LOOP_32_ROWS_REM>
  fpu 2 rep 32 vreg0 = [ar1++gr1];//load x 
  gr3 = true;
  fpu 2 .double vreg0 = vreg0*.retrive(vreg7);//getting alpha*x
  fpu 0 vreg1 = fpu 2 vreg0;//coppy alpha*x
//the loop below is very slow becoze matrix is located in one bank of memorry   
  <LOOP_ROW_BY_ROW_32_REM>
    gr3 = gr3>>1;
    ar0 = ar4;
    fpu 0 rep vlen vreg3 = [ar0++gr0];//load the collume of martix A 
    if <>0 delayed goto LOOP_ROW_BY_ROW_32_REM;
    fpu 0 .double vreg2 = vreg3*.retrive(vreg1) + vreg2;//getting alpha*A*x+betta*y
    ar4 = ar4+gr4;
  gr6--;
  if <>0 goto MAIN_LOOP_32_ROWS_REM;

<CASE_AMMOUNT_OF_ROWS_LT_32_REM>
  gr6 = ar6;
  gr6 = gr6<<27;
  gr6 = gr6>>27;
  if =0 delayed goto UPLOAD_THE_RESULT_MAIN_LOOP_REM;
  gr6--;
  vlen = gr6;
  fpu 2 rep vlen vreg0 = [ar1++gr1];//load x 
  gr6++;
  fpu 2 .double vreg0 = vreg0*.retrive(vreg7);//getting alpha*x
  fpu 0 vreg1 = fpu 2 vreg0;//coppy alpha*x
  vlen = gr7;
  <LOOP_ROW_BY_ROW_REM>
    gr6--;
    ar0 = ar4;
    fpu 0 rep vlen vreg3 = [ar0++gr0];//load the collume of martix A 
    if <>0 delayed goto LOOP_ROW_BY_ROW_REM;
    fpu 0 .double vreg2 = vreg3*.retrive(vreg1) + vreg2;//getting alpha*A*x+betta*y
    ar4 = ar4+gr4;
 ///upload the result
<UPLOAD_THE_RESULT_MAIN_LOOP_REM>
    ar2 = ar5;
    fpu 0 rep vlen [ar2++gr2] = vreg2;//upload result
<END>
pop ar4,gr4;
return;
end "text";