///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_dcopy:label;

begin "text"
<_fpu_dcopy>
  gr0 = gr0<<1;
  gr1 = gr1<<1;
  gr7 = gr5<<27;
  gr7 = gr7>>27;//reminder
  gr5 = gr5>>5;//quotient

  if =0 delayed goto REMAINDER with gr7;
<LOOP>
  gr5--;
  if <>0 delayed goto LOOP with gr7;
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 rep 32 [ar1++gr1] = vreg0;

<REMAINDER>
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 rep vlen [ar1++gr1] = vreg0;  
<END>
return;
end "text";