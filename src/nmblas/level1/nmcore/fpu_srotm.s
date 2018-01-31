///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_srotm:label;

data "data"
  params_testers:word[4]=(3f800000h,00000000h,0bf800000h,0c0000000h); 
end "data";

nobits "nobits"
  buff:long[2];
end "nobits";

begin "text"
<_fpu_srotm>
///init
  gr5;
  if <= goto CASE_N_IS_0_OR_NEGATIVE;
  push ar3,gr3 with gr0 = gr0<<1;
  push ar4,gr4 with gr1 = gr1<<1; 
  push ar6,gr6;
  gr3 = gr0;
  gr4 = gr1;

////param processing
  ar5 = params_testers;
  gr7 = [ar2++];//load flag
  gr6 = [ar5++];//load 1 to cmp with flag
  gr6 = gr6 xor gr7;
  if =0 delayed goto CASE_FLAG_EQS_1;
  gr6 = [ar5++];
  gr6 = gr6 xor gr7;
  if =0 delayed goto CASE_FLAG_EQS_0;
  gr6 = [ar5++];
  gr6 = gr6 xor gr7;
  if =0 goto CASE_FLAG_EQS_MIN_1;
//case param is -2  
  delayed goto END;

////x_______Y
///h21______h12
///h11_______h22
///pay attension order elements in mem is flag 11 21 12 22
///h11 h12
///h21 h22

<CASE_FLAG_EQS_1>
//h12 = 1 
//h21 = -1
  gr7 = [ar2++];//load h11
  ar5 = buff;
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 0 rep 1 vreg7 = [--ar5];//load h11
  
  gr7 = [params_testers[0]];//load 1 into h12 
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 1 rep 1 vreg6 = [--ar5];//load h12

  gr7 = [params_testers[2]];//load -1 into h21
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 3 rep 1 vreg6 = [--ar5];//load h12

  ar2 = ar2+2;
  gr7 = [ar2];//load h22
  [ar5++] = gr7;
  delayed goto COUNT;
  [ar5++] = gr7;
  fpu 1 rep 1 vreg7 = [--ar5];

<CASE_FLAG_EQS_0>
//h11 = 1
//h22 = 1
  ar5 = buff;
  gr7 = [params_testers[0]];//load 1
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 0 rep 1 vreg7 = [--ar5];//load 1 into h11
  fpu 1 rep 1 vreg7 = [ar5];//loaf 1 into h22
  ar2++;//point to h21
  gr7 = [ar2++];//point into h12 load h21
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 3 rep 1 vreg6 = [--ar5];//load h21
  gr7 = [ar2];//load h12
  [ar5++] = gr7;
  delayed goto COUNT;
  [ar5++] = gr7;
  fpu 1 rep 1 vreg6 = [--ar5];//h12

<CASE_FLAG_EQS_MIN_1>
  ar5 = buff;
  gr7 = [ar2++];//load h11
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 0 rep 1 vreg7 = [--ar5];
  gr7 = [ar2++];//load h21
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 3 rep 1 vreg6 = [--ar5];
  gr7 = [ar2++];//load h12
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 1 rep 1 vreg6 = [--ar5];
  gr7 = [ar2];//load h22
  [ar5++] = gr7;
  [ar5++] = gr7;
  fpu 1 rep 1 vreg7 = [--ar5];
  
<COUNT>
  gr7 = gr5<<26;
  gr7 = gr7>>26;
  gr5 = gr5>>6;
  if =0 delayed goto REMINDER;
  ar3 = ar0;
  ar4 = ar1;

<LOOP>

  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x
  fpu 0 .float vreg1 = vreg0*.retrive(vreg7);//h11*x
  fpu 1 rep 32 vreg0 = [ar1++gr1];//load y
  fpu 1 .float vreg1 = vreg0*.retrive(vreg6);//h12*y
  
  fpu 2 vreg0 = fpu 0 vreg1;//coppy h11*x
  fpu 2 vreg1 = fpu 1 vreg1;//coppy h12*y
  fpu 2 .float vreg2 = vreg0 + vreg1;//result x = h11*x+h12*y
  gr5--;
  fpu 2 rep 32 [ar3++gr3] = vreg2;//upload resilt x
  
  fpu 3 vreg0 = fpu 0 vreg0;//coppy x
  fpu 3 .float vreg1 = vreg0*.retrive(vreg6);//h21*x
  fpu 1 vreg2 = fpu 3 vreg1;
  if <>0 delayed goto LOOP;
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7)+vreg2;//h22*y+h21*x;
  fpu 1 rep 32 [ar4++gr4] = vreg2;//upload result y 

<REMINDER>
  gr7;
  if =0 delayed goto END;
  gr5 = gr7>>1;
  if =0 delayed goto THE_LAST_ELEMENT;
  gr5--;
  vlen = gr5;
  
  fpu 0 rep vlen vreg0 = [ar0++gr0];//load x
  fpu 0 .float vreg1 = vreg0*.retrive(vreg7);//
  fpu 1 rep vlen vreg0 = [ar1++gr1];//load y
  fpu 1 .float vreg1 = vreg0*.retrive(vreg6);//
  
  fpu 2 vreg0 = fpu 0 vreg1;
  fpu 2 vreg1 = fpu 1 vreg1;
  fpu 2 .float vreg2 = vreg0 + vreg1;
  gr5--;
  
  fpu 3 vreg0 = fpu 0 vreg0;//coppy x
  fpu 3 .float vreg1 = vreg0*.retrive(vreg6);
  fpu 1 vreg2 = fpu 3 vreg1;
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7)+vreg2;
  
  fpu 2 rep vlen [ar3++gr3] = vreg2;//upload resilt x
  fpu 1 rep vlen [ar4++gr4] = vreg2;//upload result y 

<THE_LAST_ELEMENT>  
  gr5 = gr7<<31;
  if =0 delayed goto END;
  fpu 0 vreg6 = fpu 1 vreg6;  
  fpu 0 rep 1 vreg0 = [ar0++gr0];//load x 
  fpu 0 rep 1 vreg1 = [ar1++gr1];//load y
  fpu 0 .float vreg2 = vreg0*.retrive(vreg7);//h11x
  fpu 0 .float vreg3 = vreg1*.retrive(vreg6) + vreg2;//h11x + h12y
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg3;
  gr7 = [ar5];
  [ar3++gr3] = gr7;//upload x
  fpu 0 vreg6 = fpu 3 vreg6;
  fpu 0 vreg7 = fpu 1 vreg7;
  fpu 0 .float vreg4 = vreg0*.retrive(vreg6);//h21x
  fpu 0 .float vreg5 = vreg1*.retrive(vreg7) + vreg4;//h21x + h22y
  fpu 0 rep 1 [ar5] = vreg5;
  gr7 = [ar5];
  [ar4++gr4] = gr7;

<END>
  pop ar6,gr6;
  pop ar4,gr4;
  pop ar3,gr3;
<CASE_N_IS_0_OR_NEGATIVE>
  return;
end "text";

 //[ar5++] = gr2;//upload c multiplier
  //[ar5++] = gr2;
  //[ar5++] = ar2;//upload s multiplier
  //[ar5++] = ar2;
  //ar5 = buff;
  //fpu 0 rep 1 vreg7 = [ar5++];//load c
  //fpu 0 rep 1 vreg6 = [ar5++];//laod s
  //fpu 1 vreg6 = fpu 0 vreg6;//coppy s
  //if =0 delayed goto REMINDER with gr7;
  //fpu 3 vreg6 = fpu 0 vreg6;//coppy s
  //fpu 1 vreg7 = fpu 0 vreg7;//coppy c