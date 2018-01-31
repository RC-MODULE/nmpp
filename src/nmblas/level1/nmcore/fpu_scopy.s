///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

//the perpose of this function see in mnblas_scopy.s file
global _fpu_scopy:label;

begin "text"
<_fpu_scopy>
  //push ar4,gr4;
  gr5;
  if <= delayed goto END;//case inc_y is negative
  gr0 = gr0+gr0;
  gr1 = gr1+gr1;
  gr7 = gr5 << 26;//reminder
  gr7 = gr7 >> 26;
  gr5 = gr5 >> 6;//there is a quotient there
  if =0 delayed goto REMINDER; 

<LOOP>
  gr5--;
  if <>0 delayed goto LOOP;  
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x into fpu
  fpu 0 rep 32 [ar1++gr1] = vreg0;//upload x into y

<REMINDER>
  gr5 = gr7>>1;
  if =0 delayed goto REMINDER_THE_LAST; 
  gr5--;
  vlen = gr5;
  fpu 0 rep vlen vreg0 = [ar0++gr0];//load x into fpu
  fpu 0 rep vlen [ar1++gr1] = vreg0;

<REMINDER_THE_LAST>
  gr7 = gr7<<31;
  if =0 goto END;
  gr7 = [ar0];//load the last x
  [ar1] = gr7;//upload the last x into y

<END>  
  //pop ar4,gr4;
  return;
end "text";