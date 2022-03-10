//------------------------------------------------------------------------
//
//  $Workfile:: Math_Add.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Add.asm
//! \author ������ �������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_CMP_NE_V(N)
.if (NMPP_MIN_REP <= N);
	rep N data= [ar0++gr0] with data;
	rep N data= [ar1++gr1] with afifo xor data;
	rep N [ar7],ram = afifo with 0-afifo ;
	delayed return;
		rep N  with activate afifo or activate ram;
		rep N [ar6++gr6] = afifo;
		nul;
	nul;
.endif;
end   VEC_CMP_NE_V;

Cmp_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_CmpNeV(nmreg nb1,nmreg sb, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6 )
    //!
    //------------------------------------------------------------------------

global vec_CmpNeV :label;
<vec_CmpNeV>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Cmp_repN with gr2>>=24;
		ar2 = Cmp_rep0 with gr5--;
	<next_Cmp_rep32>
		rep 32 data= [ar0++gr0] with data;
		rep 32 data= [ar1++gr1] with afifo xor data;
		rep 32 [ar7],ram = afifo with 0-afifo;
	if <>0 delayed goto next_Cmp_rep32 with gr5--;
		rep 32 with  activate afifo or activate ram;
		rep 32 [ar6++gr6] = afifo;
	<Cmp_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Cmp_rep0>
	delayed return;
		nul;
		nul;
		nul;
	nul;
	nul;
	nul;
	nul;
	VEC_CMP_NE_V(1);
	VEC_CMP_NE_V(2);
	VEC_CMP_NE_V(3);
	VEC_CMP_NE_V(4);
	VEC_CMP_NE_V(5);
	VEC_CMP_NE_V(6);
	VEC_CMP_NE_V(7);
	VEC_CMP_NE_V(8);
	VEC_CMP_NE_V(9);
	VEC_CMP_NE_V(10);
	VEC_CMP_NE_V(11);
	VEC_CMP_NE_V(12);
	VEC_CMP_NE_V(13);
	VEC_CMP_NE_V(14);
	VEC_CMP_NE_V(15);
	VEC_CMP_NE_V(16);
	VEC_CMP_NE_V(17);
	VEC_CMP_NE_V(18);
	VEC_CMP_NE_V(19);
	VEC_CMP_NE_V(20);
	VEC_CMP_NE_V(21);
	VEC_CMP_NE_V(22);
	VEC_CMP_NE_V(23);
	VEC_CMP_NE_V(24);
	VEC_CMP_NE_V(25);
	VEC_CMP_NE_V(26);
	VEC_CMP_NE_V(27);
	VEC_CMP_NE_V(28);
	VEC_CMP_NE_V(29);
	VEC_CMP_NE_V(30);
	VEC_CMP_NE_V(31);
return;
.wait;




end ".text_nmvcore";
