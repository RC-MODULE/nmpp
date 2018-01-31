///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////
//the purpose of this function see in nmblals_dnrm2.s file 
global _fpu_dnrm2:label;
extern _sqrt:label;

data "data"
  _zero : long = double(0);
end "data";

begin "text"
<_fpu_dnrm2>
  gr5;
  if <= delayed goto END;
  gr7 = false;
  gr6 = false;
  gr7 = gr5<<27;
  gr7 = gr7>>27;
  gr0 = gr0<<1;
  gr5 = gr5>>5;

  ar5 = _zero;
  if =0 delayed goto REMINDER;
  fpu 0 rep 1 vreg2 = [ar5];//init for reminder case 
  gr5--;
  if =0 delayed goto WRAP_UP;
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x 
  fpu 0 .double vreg0 = vreg0*vreg0;//accum

<LOOP>
  gr5--;
  if <>0 delayed goto LOOP;
  fpu 0 rep 32 vreg1 = [ar0++gr0];
  fpu 0 .double vreg0 = vreg1*vreg1 + vreg0;

<WRAP_UP>
  fpu 0 .packer = vreg0 with .fixed_64 <= .fixed_64;
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
  if =0 delayed goto CALL_SQRT;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 .double vreg0 = vreg0*vreg0;
<LOOP_REMINDER>
  if <>0 delayed goto LOOP_REMINDER;
  fpu 0 .double vreg2 = vreg2 + .retrive(vreg0);
  gr7--;

<CALL_SQRT>
  
  fpu 0 rep 1 [ar7++] = vreg2;
  call _sqrt;
  //gr6 = [--ar7];
  //gr7 = [--ar7];
  ar7 = ar7-2;
<END>
  return;
end "text";