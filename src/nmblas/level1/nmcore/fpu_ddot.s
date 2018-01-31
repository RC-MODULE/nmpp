///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////
/////purpose of the function see in nmblas_ddot.s file

global _fpu_ddot:label;

data "data"
  zero_: long = double(0);
end "data";

nobits "nobits"
  buff : long;
end "nobits";

begin "text"

<_fpu_ddot>
  gr5;
  if <= delayed goto END_N_LE_ZERO;
  gr0 = gr0 + gr0;//offsets mmlt 2
  gr1 = gr1 + gr1;

  gr7 = gr5<<27;
  gr7 = gr7>>27;
  ar5 = zero_;
  gr5 = gr5>>5;

  if =0 delayed goto REMINDER;
  fpu 0 rep 1 vreg2 = [ar5];
  //initialisation to apply mulltiply accomulate ferter
  gr5--;
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x
  if =0 delayed goto UNROULING;
  fpu 0 rep 32 vreg1 = [ar1++gr1];//load y 
  fpu 0 .double vreg2 = vreg0*vreg1;

<LOOP>
  gr5--;
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  if <>0 delayed goto LOOP;
  fpu 0 rep 32 vreg1 = [ar1++gr1];
  fpu 0 .double vreg2 = vreg0*vreg1 + vreg2;//accomulator  

<UNROULING>
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg0 = .packer;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg0 = .packer;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg0 = .packer;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg0 = .packer;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

<REMINDER>  
  gr7;
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 rep vlen vreg1 = [ar1++gr1];
  fpu 0 .double vreg0 = vreg0*vreg1;
<LOOP_REMINDER>
  if <>0 delayed goto LOOP_REMINDER;
  fpu 0 .double vreg2 = vreg2 + .retrive(vreg0); 
  gr7--; 

<END>   
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg2;
  delayed return;
  gr7 = [ar5++];
  gr6 = [ar5];  
<END_N_LE_ZERO>
  delayed return;
  gr7 = false;
  gr6 = false;
end "text";
