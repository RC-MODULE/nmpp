///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////
//the perpose of this function see in nmblas_scnrm2.s file
global _fpu_scnrm2:label;
extern _sqrt:label;

data "data"
  zero_: long = double(0);
end "data";

begin "text"
<_fpu_scnrm2>
  gr5;
  if <= delayed goto END;//case N eqs 0 or less then 0
  ar5 = zero_;
  gr7 = gr5<<27;
  gr7 = gr7>>27;
  //gr0;
  //if <= delayed goto END;//case inc_x eqs 0 or less then 0   
  fpu 0 rep 1 vreg2 = [ar5];  
  gr5 = gr5>>5;
  if =0 delayed goto REMINDER;
  gr0 = gr0<<1;
  gr5--;
 //init 
  if =0 delayed goto UNROULLING;
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .float  vreg1 = vreg0*vreg0;

<LOOP>
  gr5--;
  if <>0 delayed goto LOOP;
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .float vreg1 = vreg0*vreg0+vreg1;

<UNROULLING>
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg0 = .packer;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg0 = .packer;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg0 = .packer;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg0 = .packer;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;
  
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

<REMINDER>
  gr7;
  if =0 delayed goto CALL_SQRT;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 .float vreg0 = vreg0*vreg0;
<LOOP_REMINDER>
  if <>0 delayed goto LOOP_REMINDER;
  fpu 0 .float vreg2 = vreg2 + .retrive(vreg0);
  gr7--;

<CALL_SQRT> 
  fpu 0 .packer = vreg2 with .float .in_low <= .float .in_high;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg2;
  fpu 0 .packer = vreg2 with .double <= .float .in_low;
  ar5 = ar7;
  fpu rep 1 [ar7++] = .packer;
  call _sqrt;
  ar7 = ar5;
  [ar5++] = gr7;
  [ar5] = gr6; 
  ar5--;  
  fpu rep 1 .packer = [ar5] with .float .in_low <= .double;
  fpu rep 1 [ar5] = .packer;
  gr7 = [ar5];
  return;
<END>
  delayed return;
  gr7 = false;
  nop;
end "text";