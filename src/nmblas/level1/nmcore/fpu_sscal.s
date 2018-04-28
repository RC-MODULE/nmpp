///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

//the purpose of this function see in nmblas_sscal.s file
global _fpu_sscal:label;

nobits "nobits"
  buff : long;
end "nobits";

begin "text"
<_fpu_sscal>
  
  gr5;
  if <= delayed goto END;
  ar5 = buff;
  
  [ar5++] = gr1;//load alpha 
  [ar5++] = gr1;

  fpu 0 rep 1 vreg1 = [--ar5];

  gr7 = gr5<<26;
  gr7 = gr7>>26;

  gr5 = gr5>>6;

  if =0 delayed goto REMAINDER;
  gr0 = gr0 << 1; 

<LOOP>
  ar5 = ar0;
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x
  fpu 0 .float vreg0 = vreg0*.retrive(vreg1);//x = alpha*x
  gr5--;
  if <>0 delayed goto LOOP;
  ar0  = ar5;
  fpu 0 rep 32 [ar0++gr0] = vreg0;//

<REMAINDER>
  
  gr5 = gr7>>1;
  if =0 delayed goto THE_LAST_ELEMENT;
  ar5 = ar0;
  gr5--;
  vlen = gr5;
  
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 .float vreg0 = vreg0*.retrive(vreg1);
  ar0 = ar5;
  fpu 0 rep vlen [ar0++gr0] = vreg0;

<THE_LAST_ELEMENT>
  gr5 = gr7<<31;
  if =0 delayed goto END;
  ar5 = ar0;
  fpu 0 rep 1  vreg0 = [ar0++gr0];
  fpu 0 .float vreg0 = vreg0*.retrive(vreg1);
  gr5 = buff;
  fpu 0 rep 1 [gr5] = vreg0;
  gr7 = [gr5];
  ar0 = ar5;
  [ar0++gr0] = gr7;

<END>
  return; 
end "text";