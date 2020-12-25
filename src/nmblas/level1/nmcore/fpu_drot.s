///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////
global _fpu_drot : label;

begin "text"
<_fpu_drot> 
  push ar3,gr3;
  push ar4,gr4 with gr5;
  if <= delayed goto END;
  ar4 = ar1 with gr0 = gr0<<1;
  ar3 = ar0 with gr1 = gr1<<1;
  gr3 = gr0;
  gr4 = gr1;
  gr7 = gr5<<27;
  gr7 = gr7>>27;
  gr5 = gr5>>5; 

  fpu 1 vreg7 = fpu 0 vreg7;
  fpu 2 vreg7 = fpu 0 vreg7;
  fpu 3 vreg7 = fpu 0 vreg7;
  fpu 1 vreg6 = fpu 0 vreg6;
  if =0 delayed goto REMAINDER with gr7;
  fpu 2 vreg6 = fpu 0 vreg6;
  fpu 3 vreg6 = fpu 0 vreg6;

<LOOP>
  gr5--;
  fpu 0 rep 32 vreg0 = [ar1++gr1];//load y
  fpu 0 .double vreg1 = vreg0*.retrive(vreg6);//sy
  fpu 1 rep 32 vreg0 = [ar0++gr0];//load x
  fpu 1 .double vreg1 = vreg0*.retrive(vreg7);//cx
  fpu 2 vreg0 = fpu 0 vreg1;//copy sy to add
  fpu 2 vreg1 = fpu 1 vreg1;//copy cx to add
  fpu 2 .double vreg3 = vreg0 + vreg1;//result of x = cx + sy
  
  fpu 3 vreg0 = fpu 1 vreg0;
  fpu 3 .double vreg1 = -vreg0*.retrive(vreg6);//-sx
  fpu 0 vreg2 = fpu 3 vreg1;
  fpu 0 .double vreg3 = vreg0*.retrive(vreg7) + vreg2;// result of  y = cy - sx   
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
  fpu 3 .double vreg1 = -vreg0*.retrive(vreg6);//-sx
  fpu 0 vreg2 = fpu 3 vreg1;
  fpu 0 .double vreg3 = vreg0*.retrive(vreg7) + vreg2;// result of  y = cy - sx   
  fpu 0 rep vlen [ar4++gr4] = vreg3;//y
  fpu 2 rep vlen [ar3++gr3] = vreg3;//x

<END>
  pop ar4,gr4;
  pop ar3,gr3;
  return;
end "text";