///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

//the purpose of this function see in nmblas_idamax.s file
 global _fpu_idamax:label;

data "data"
  init_index : long[32] = (double(0),double(1),double(2),double(3),double(4),double(5),double(6),double(7),double(8),double(9),double(10),double(11),
    double(12),double(13),double(14),double(15),double(16),double(17),double(18),double(19),double(20),double(21),double(22),double(23),double(24),
    double(25),double(26),double(27),double(28),double(29),double(30),double(31));
  init_offset : long = double(32);
  min_infinity : long = (0fff0000000000000hl);
end "data";

nobits "nobits"
  .align; 
  buff : long[32];
end "nobits";


begin "text"
<_fpu_idamax>
  gr5;
  if <= delayed goto END;
////init of mask   
  gr7 = false;
  sir = gr7;
  fp1_lmask = sir;
  fp1_hmask = sir;
//////  
  gr0 = gr0 << 1;
  gr7 = gr5 >> 1;
  if =0 delayed goto CASE_AMMOUNT_EQS_1;

  gr7 = gr5 << 27;
  gr7 = gr7 >> 27;
  gr5 = gr5 >> 5;
  
  ar5 = init_index;
  fpu 0 rep 32 vreg0 = [ar5++];//load initial value of indexes
  fpu 0 vreg1 = vreg0;
  ar5 = init_offset;
  if =0  delayed goto CASE_WITHOUT_QUTIENT;
  fpu 0 rep 1 vreg7 = [ar5];//load 32 to add with farter indexses 
  nop;

///init

  fpu 1 rep 32 vreg0 = [ar0++gr0];//load x0
  fpu 1 .double vreg0 = /vreg0/;
  gr5--;
  if =0 goto REMINDER;
 <LOOP> 
  fpu 1 rep 32 vreg1 = [ar0++gr0];//load x1
  fpu 1 .double vreg1 = /vreg1/; 
  fpu 0 .double vreg1 = vreg1 + .retrive(vreg7);
  fpu 1 .double vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg0 = mask ? vreg1:vreg0; 
  fp0_lmask = fp1_lmask;
  gr5--;
  if <>0 delayed goto LOOP;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg0 = mask ? vreg1:vreg0;

<REMINDER>
  gr7;
  if =0 delayed goto WRAP_UP;
  gr7--;
  vlen = gr7;
  
  ar5 = min_infinity;
  fpu 1 rep 32 vreg7 = [ar5];//load -infinity
  ar5 = buff;
////aligting
  fpu 0 rep vlen vreg6 = [ar0++gr0];//load x
  fpu 0 .double vreg6 = /vreg6/;
  fpu 1 rep 32 [ar5++] = vreg7;//upload - infinity
  ar5 = buff;
  fpu 0 rep vlen [ar5++] = vreg6;//upload x

  ar5 = buff;
  fpu 1 rep 32 vreg1 = [ar5++];//alighted reminder of x 

  fpu 0 .double vreg1 = vreg1 + .retrive(vreg7);
  fpu 1 .double vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg0 = mask ? vreg1:vreg0; 

  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg0 = mask ? vreg1:vreg0;

<WRAP_UP>

/////16
  fpu 1 .packer = vreg0 with .fixed_64 <= .fixed_64;
  fpu 1 rep 16 vreg1 = .packer;
  fpu 1 rep 16 vreg2 = .packer;
  fpu 0 .packer = vreg0 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 rep 16 vreg2 = .packer;

  fpu 1 .double vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg1 = mask ? vreg2:vreg1;

/////8
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 8 vreg1 = .packer;
  fpu 1 rep 8 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 rep 8 vreg2 = .packer;

  fpu 1 .double vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg1 = mask ? vreg2:vreg1;
/////4  
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 4 vreg1 = .packer;
  fpu 1 rep 4 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 rep 4 vreg2 = .packer;

  fpu 1 .double vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg1 = mask ? vreg2:vreg1;
/////2
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 2 vreg1 = .packer;
  fpu 1 rep 2 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 rep 2 vreg2 = .packer;
  fpu 1 .double vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .double vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg1 = mask ? vreg2:vreg1; 
/////1
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 1 vreg1 = .packer;
  fpu 1 rep 1 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 rep 1 vreg2 = .packer;

  fpu 1 .double vreg2-vreg1,set mask if >;
  fpu 1 .double vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg1 = mask ? vreg2:vreg1;
  
  fpu 0 .packer = vreg1 with .fixed_32 .in_low <= .double;
  ar5 = buff;
  fpu rep 1 [ar5] = .packer;
  gr7 = [ar5];
<END>
  return;
<CASE_WITHOUT_QUTIENT>
  gr7;
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  ar5 = min_infinity;
  fpu 1 rep 32 vreg7 = [ar5];//load -infinity
  fpu 1  vreg0 = vreg7;
  ar5 = buff;
////aligting
  fpu 0 rep vlen vreg7 = [ar0++gr0];//load x
  fpu 0 .double vreg7 = /vreg7/;
  fpu 1 rep 32 [ar5++] = vreg7;//upload - infinity
  ar5 = buff;
  fpu 0 rep vlen [ar5++] = vreg7;//upload x
  
  
  ar5 = buff;
  fpu 1 rep 32 vreg1 = [ar5++];//alighted reminder of x 

  fpu 0 .double vreg2 = vreg0;
  fpu 1 .double vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
////
  fpu 1 .double vreg0 = mask ? vreg1:vreg0; 
  fp0_lmask = fp1_lmask;
  delayed goto WRAP_UP;
  fp0_hmask = fp1_hmask;
  fpu 0 .double vreg0 = mask ? vreg2:vreg0;

<CASE_AMMOUNT_EQS_1>
  delayed return;
  gr7 = false;
  nop;  
end "text";