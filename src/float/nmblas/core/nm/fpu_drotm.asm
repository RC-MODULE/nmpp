///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_drotm : label;

data "data"
  cofficients:long[4] = (double(-1),double(1));
  param_test:word[2] = (0bff00000h,3ff00000h);//-1 1 0
end "data";


begin "text"
<_fpu_drotm> 
  push ar3,gr3;
  push ar4,gr4 with gr5;
  if <= delayed goto END;
  ar4 = ar1 with gr0 = gr0<<1;
  ar3 = ar0 with gr1 = gr1<<1;
  gr7 = gr5<<27;
  gr7 = gr7>>27;
/////deffining of param 
  //orrder of hes in mem are h11 h21 h12 h22
  //fpu 0 rep 1 vreg0 = [ar6++];//load flag
  gr3 = [ar6++];
  gr4 = [ar6++];  
  gr3 = gr3 or gr4;
  fpu 1 rep 1 vreg7 = [ar6++];//load h11
  fpu 3 rep 1 vreg6 = [ar6++];//load h21
  fpu 0 rep 1 vreg6 = [ar6++];//load h12
  fpu 0 rep 1 vreg7 = [ar6++];//load h22
  ar5 = cofficients;
  fpu 0 rep 1 vreg2 = [ar5++];//load -1 
  fpu 0 rep 1 vreg3 = [ar5++];//load 1

//tst is the flag -1 or not   
  ar5 = param_test;
  gr4 = [ar5++];//load -1 to cmp
  gr4 = gr3 xor gr4;
  if =0 delayed goto COUNT; 
//tst is the flag 1 or not;  
  gr4 = [ar5++];//load 1 to cmp
  gr4 = gr3 xor gr4;
  if <>0 goto L1;
  delayed goto COUNT;
  fpu 0 vreg6 = vreg3;//coppy 1 into plase of h12
  fpu 3 vreg6 = fpu 0 vreg2;//coppy -1 into plase of h21
<L1>
//tst is the flag 0 or not 
  gr4 = false;//load 0 to cmp
  gr4 = gr3 xor gr4;
  if =0 delayed goto COUNT;
  fpu 1 vreg7 = fpu 0 vreg3;//coppy 1 into plase of h11
  fpu 0 vreg7 = fpu 0 vreg3;//coppy 1 into plase of h22
//case the flag eqs -2 or undefined
  delayed goto END;

  
<COUNT>
  gr5 = gr5>>5; 
  if =0 delayed goto REMAINDER with gr7;
  gr3 = gr0;
  gr4 = gr1;
<LOOP>
  gr5--;
  fpu 0 rep 32 vreg0 = [ar1++gr1];//load y
  fpu 0 .double vreg1 = vreg0*.retrive(vreg6);//sy//h12y
  fpu 1 rep 32 vreg0 = [ar0++gr0];//load x
  fpu 1 .double vreg1 = vreg0*.retrive(vreg7);//cx//h11
  fpu 2 vreg0 = fpu 0 vreg1;//copy sy to add
  fpu 2 vreg1 = fpu 1 vreg1;//copy cx to add
  fpu 2 .double vreg3 = vreg0 + vreg1;//result of x = cx + sy//x = h11x + h12y
  
  fpu 3 vreg0 = fpu 1 vreg0;
  fpu 3 .double vreg1 = vreg0*.retrive(vreg6);//sx//h21x
  fpu 0 vreg2 = fpu 3 vreg1;
  fpu 0 .double vreg3 = vreg0*.retrive(vreg7) + vreg2;// result of  y = cy - sx//y = h21x + h22y   
  if <>0 delayed goto LOOP with gr7;
  fpu 0 rep 32 [ar4++gr4] = vreg3;//y
  fpu 2 rep 32 [ar3++gr3] = vreg3;//x

<REMAINDER>  
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg0 = [ar1++gr1];//load y
  fpu 0 .double vreg1 = vreg0*.retrive(vreg6);//sy
  fpu 1 rep vlen vreg0 = [ar0++gr0];//load x
  fpu 1 .double vreg1 = vreg0*.retrive(vreg7);//cx
  fpu 2 vreg0 = fpu 0 vreg1;//copy sy to add
  fpu 2 vreg1 = fpu 1 vreg1;//copy cx to add
  fpu 2 .double vreg3 = vreg0 + vreg1;//result of x = cx + sy
  
  fpu 3 vreg0 = fpu 1 vreg0;
  fpu 3 .double vreg1 = vreg0*.retrive(vreg6);//sx
  fpu 0 vreg2 = fpu 3 vreg1;
  fpu 0 .double vreg3 = vreg0*.retrive(vreg7) + vreg2;// result of  y = cy - sx   
  fpu 0 rep vlen [ar4++gr4] = vreg3;//y
  fpu 2 rep vlen [ar3++gr3] = vreg3;//x

<END>
  pop ar4,gr4;
  pop ar3,gr3;
  return;
end "text";

