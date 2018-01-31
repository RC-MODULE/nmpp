///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_srot:label;

nobits "nobits"
  buff:long[2];
end "nobits";

begin "text"
<_fpu_srot>
  gr5;
  if <= delayed goto CASE_N_IS_0_OR_NEGATIVE;
  gr7 = gr5<<26;
  gr7 = gr7>>26;
  push ar3,gr3 with gr0 = gr0<<1;
  push ar4,gr4 with gr1 = gr1<<1; 
  ar3 = ar0;
  ar4 = ar1;
  gr3 = gr0;
  gr4 = gr1;
  ar5 = buff with gr5 = gr5>>6;

  [ar5++] = gr2;//upload c multiplier
  [ar5++] = gr2;
  [ar5++] = ar2;//upload s multiplier
  [ar5++] = ar2;
  ar5 = buff;
  fpu 0 rep 1 vreg7 = [ar5++];//load c
  fpu 0 rep 1 vreg6 = [ar5++];//laod s
  fpu 1 vreg6 = fpu 0 vreg6;//coppy s
  if =0 delayed goto REMINDER with gr7;
  fpu 3 vreg6 = fpu 0 vreg6;//coppy s
  fpu 1 vreg7 = fpu 0 vreg7;//coppy c

<LOOP>

  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x
  fpu 0 .float vreg1 = vreg0*.retrive(vreg7);//cx
  fpu 1 rep 32 vreg0 = [ar1++gr1];//load y
  fpu 1 .float vreg1 = vreg0*.retrive(vreg6);//sy
  
  fpu 2 vreg0 = fpu 0 vreg1;//coppy cx
  fpu 2 vreg1 = fpu 1 vreg1;//coppy sy
  fpu 2 .float vreg2 = vreg0 + vreg1;//result x = cx+sy
  gr5--;
  fpu 2 rep 32 [ar3++gr3] = vreg2;//upload resilt x
  
  fpu 3 vreg0 = fpu 0 vreg0;//coppy x
  fpu 3 .float vreg1 = -vreg0*.retrive(vreg6);//-sx
  fpu 1 vreg2 = fpu 3 vreg1;
  if <>0 delayed goto LOOP;
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7)+vreg2;//cy-sx;
  fpu 1 rep 32 [ar4++gr4] = vreg2;//upload result y 

<REMINDER>
  gr7;
  if =0 delayed goto END;
  gr5 = gr7>>1;
  if =0 delayed goto THE_LAST_ELEMENT;
  gr5--;
  vlen = gr5;
  
  fpu 0 rep vlen vreg0 = [ar0++gr0];//load x
  fpu 0 .float vreg1 = vreg0*.retrive(vreg7);//cx
  fpu 1 rep vlen vreg0 = [ar1++gr1];//load y
  fpu 1 .float vreg1 = vreg0*.retrive(vreg6);//sy
  
  fpu 2 vreg0 = fpu 0 vreg1;//coppy cx
  fpu 2 vreg1 = fpu 1 vreg1;//coppy sy
  fpu 2 .float vreg2 = vreg0 + vreg1;//result x = cx+sy
  gr5--;
  
  fpu 3 vreg0 = fpu 0 vreg0;//coppy x
  fpu 3 .float vreg1 = -vreg0*.retrive(vreg6);//-sx
  fpu 1 vreg2 = fpu 3 vreg1;
  fpu 1 .float vreg2 = vreg0*.retrive(vreg7)+vreg2;//cy-sx;
  
  fpu 2 rep vlen [ar3++gr3] = vreg2;//upload resilt x
  fpu 1 rep vlen [ar4++gr4] = vreg2;//upload result y 

<THE_LAST_ELEMENT>  
  gr5 = gr7<<31;
  if =0 delayed goto END;
  fpu 0 rep 1 vreg0 = [ar0++gr0];//load x 
  fpu 0 rep 1 vreg1 = [ar1++gr1];//load y
  fpu 0 .float vreg2 = vreg0*.retrive(vreg7);//cx
  fpu 0 .float vreg3 = vreg1*.retrive(vreg6) + vreg2;//result x = cx+sy;
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg3;
  gr7 = [ar5];
  [ar3++gr3] = gr7;//upload x
  fpu 0 .float vreg4 = -vreg0*.retrive(vreg6);//-sy
  fpu 0 .float vreg5 = vreg1*.retrive(vreg7) + vreg4;
  fpu 0 rep 1 [ar5] = vreg5;
  gr7 = [ar5];
  [ar4++gr4] = gr7;

<END>
  pop ar4,gr4;
  pop ar3,gr3;
<CASE_N_IS_0_OR_NEGATIVE>
  return;
end "text";