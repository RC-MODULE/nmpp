//the purpose of the code below see in nmblas_isamax.s file 
global _fpu_isamax:label;

data "data"
  init_index : word[64] = (float(0),float(1),float(2),float(3),float(4),float(5),float(6),float(7),float(8),float(9),float(10),float(11),
    float(12),float(13),float(14),float(15),float(16),float(17),float(18),float(19),float(20),float(21),float(22),float(23),float(24),
    float(25),float(26),float(27),float(28),float(29),float(30),float(31),float(32),float(33),float(34),float(35),float(36),float(37),float(38)
    ,float(39),float(40),float(41),float(42),float(43),float(44),float(45),float(46),float(47),float(48),float(49),float(50),float(51),float(52)
    ,float(53),float(54),float(55),float(56),float(57),float(58),float(59),float(60),float(61),float(62),float(63));
  init_offset : word[2] = (float(64),float(64));
  min_infinity : word[2] = ((0ff800000h),(0ff800000h));
end "data";

nobits "nobits"
  buff : long[32];
end "nobits";


begin "text"
<_fpu_isamax>
  gr5;
  if <= delayed goto END;
///init of mask   
  gr7 = false;
  sir = gr7;
  fp1_lmask = sir;
  fp1_hmask = sir;
//////  
  gr0 = gr0 << 1;
  gr7 = gr5 >> 1;
  if =0 delayed goto CASE_AMMOUNT_EQS_1;

  gr7 = gr5 << 26;
  gr7 = gr7 >> 26;
  gr5 = gr5 >> 6;
  
  ar5 = init_index;
  fpu 0 rep 32 vreg0 = [ar5++];//load initial value of indexes
  fpu 0 vreg1 = vreg0;
  ar5 = init_offset;
  if =0  delayed goto CASE_WITHOUT_QUTIENT;
  fpu 0 rep 1 vreg7 = [ar5];//load 64 to add with farter indexses 
  nop;

///init
  fpu 1 rep 32 vreg0 = [ar0++gr0];//load x0
  fpu 1 .float vreg0 = /vreg0/;
  gr5--;
  if =0 goto REMAINDER;
 <LOOP> 
  fpu 1 rep 32 vreg1 = [ar0++gr0];//load x1
  fpu 1 .float vreg1 = /vreg1/; 
  fpu 0 .float vreg1 = vreg1 + .retrive(vreg7);
  fpu 1 .float vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////
  fpu 1 .float vreg0 = mask ? vreg1:vreg0; 

  fp0_lmask = fp1_lmask;
  gr5--;
  if <>0 delayed goto LOOP;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg0 = mask ? vreg1:vreg0;


<REMAINDER>
  gr7;
  if =0 delayed goto WRAP_UP;
  gr5 = gr7>>1;
  gr5--;
  vlen = gr5;
  
  ar5 = min_infinity;
  fpu 1 rep 32 vreg7 = [ar5];//load -infinity
  ar5 = buff;
  fpu 1 rep 32 [ar5++] = vreg7;//upload - infinity
  gr5 = gr7>>1;
  if =0 delayed goto CASE_REMIDER_EQ_ONE;
  ar5 = buff;
  nop;
////aligting
  fpu 0 rep vlen vreg6 = [ar0++gr0];//load x
  fpu 0 .float vreg6 = /vreg6/;
  //ar5 = buff;
  fpu 0 rep vlen [ar5++] = vreg6;//upload x
<CASE_REMIDER_EQ_ONE>  
  gr5 = gr7 << 31;
  if =0 goto PASS_THE_LAST_ELEMENT;
  gr7 = [ar0++gr0];//load the last element
  gr7 = gr7<<1;
  gr7 = gr7>>1;
  [ar5] = gr7;//put it in the alight buffer  

<PASS_THE_LAST_ELEMENT>
  ar5 = buff;
  fpu 1 rep 32 vreg1 = [ar5++];//alighted reminder of x 

  fpu 0 .float vreg1 = vreg1 + .retrive(vreg7);
  fpu 1 .float vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .float vreg0 = mask ? vreg1:vreg0; 
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg0 = mask ? vreg1:vreg0;

<WRAP_UP>
/////16
  fpu 1 .packer = vreg0 with .fixed_64 <= .fixed_64;
  fpu 1 rep 16 vreg1 = .packer;
  fpu 1 rep 16 vreg2 = .packer;
  fpu 0 .packer = vreg0 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 rep 16 vreg2 = .packer;
  fpu 1 .float vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask  = fp1_lmask;
/////  
  fpu 1 .float vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1;
/////8
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 8 vreg1 = .packer;
  fpu 1 rep 8 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 rep 8 vreg2 = .packer;

  fpu 1 .float vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .float vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1;
/////4  
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 4 vreg1 = .packer;
  fpu 1 rep 4 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 rep 4 vreg2 = .packer;
  fpu 1 .float vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .float vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1;
/////2
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 2 vreg1 = .packer;
  fpu 1 rep 2 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 rep 2 vreg2 = .packer;
  fpu 1 .float vreg2-vreg1,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
/////  
  fpu 1 .float vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1; 
/////1
  fpu 1 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 1 rep 1 vreg1 = .packer;
  fpu 1 rep 1 vreg2 = .packer;
  fpu 0 .packer = vreg1 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 rep 1 vreg2 = .packer;
  fpu 1 .float vreg2-vreg1,set mask if >;
  
  fpu 1 .float vreg1 = mask ? vreg2:vreg1;
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1;
////0
  fpu 1 vreg2 = vreg1;
  fpu 1 .packer = vreg1 with .float .in_low <= .float .in_high;
  fpu 1 rep 1 vreg1 = .packer;
  fpu 1 .packer = vreg2 with .float .in_low <= .float .in_low; 
  fpu 1 rep 1 vreg2 = .packer;
  fpu 0 vreg2 = vreg1;
  fpu 0 .packer = vreg1 with .float .in_low <= .float .in_high;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 .packer = vreg2 with .float .in_low <= .float .in_low; 
  fpu 0 rep 1 vreg2 = .packer;
  fpu 1 .float vreg2-vreg1,set mask if >;
  
  fp0_lmask = fp1_lmask;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg1 = mask ? vreg2:vreg1;
  fpu 0 .packer = vreg1 with .fixed_32 .in_low <= .float .in_low;
  ar5 = buff;
  fpu rep 1 [ar5] = .packer;
  gr7 = [ar5];

<END>
  return;
<CASE_WITHOUT_QUTIENT>
  gr7;
  if =0 delayed goto END;
  gr5 = gr7>>1;
  gr5--;
  vlen = gr5;
  ar5 = min_infinity;
  fpu 1 rep 32 vreg7 = [ar5];//load -infinity
  fpu 1  vreg0 = vreg7;
  ar5 = buff;
////aligting
  fpu 0 rep vlen vreg7 = [ar0++gr0];//load x
  fpu 0 .float vreg7 = /vreg7/;
  fpu 1 rep 32 [ar5++] = vreg7;//upload - infinity
  ar5 = buff;
  fpu 0 rep vlen [ar5++] = vreg7;//upload x
  
  gr5 = gr7 << 31;
  if =0 goto PASS_THE_LAST_ELEMENT2;
  gr7 = [ar0++gr0];//load the last element
  gr7 = gr7 << 1;
  gr7 = gr7 >> 1;
  [ar5] = gr7;//put it in the alight buffer  

<PASS_THE_LAST_ELEMENT2>
  ar5 = buff;
  fpu 1 rep 32 vreg1 = [ar5++];//alighted reminder of x 

  fpu 0 .float vreg2 = vreg0;
  fpu 1 .float vreg1-vreg0,set mask if >;
/////hardware bug in 6407 the last element of mask does not work propraetry
  fp1_lmask = fp1_lmask;
///// 
  fpu 1 .float vreg0 = mask ? vreg1:vreg0; 

  fp0_lmask = fp1_lmask;
  delayed goto WRAP_UP;
  fp0_hmask = fp1_hmask;
  fpu 0 .float vreg0 = mask ? vreg2:vreg0;
  return;
<CASE_AMMOUNT_EQS_1>
  delayed return;
  gr7 = false;
  nop;  
end "text";