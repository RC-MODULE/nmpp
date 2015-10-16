//------------------------------------------------------------------------
//
//  $Workfile:: data_xor_ram.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data_xor_ram.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"



macro VEC_XORVN_REP(N)
	delayed return;
		rep N ram = [ar1];
		rep N data = [ar0++gr0] with data xor ram;
		rep N [ar6++gr6] = afifo;
end   VEC_XORVN_REP;

XorVN_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_data_xor_ram(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_data_xor_ram :label;
<vec_data_xor_ram>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto XorVN_repN with gr2>>=25;
		ar2 = XorVN_rep0 with gr5--;
	rep 32 ram = [ar1];
	<next_XorVN_rep32>
	if <>0 delayed goto next_XorVN_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with data xor ram;
		rep 32 [ar6++gr6] = afifo;
	<XorVN_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<XorVN_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_XORVN_REP(1);
	VEC_XORVN_REP(2);
	VEC_XORVN_REP(3);
	VEC_XORVN_REP(4);
	VEC_XORVN_REP(5);
	VEC_XORVN_REP(6);
	VEC_XORVN_REP(7);
	VEC_XORVN_REP(8);
	VEC_XORVN_REP(9);
	VEC_XORVN_REP(10);
	VEC_XORVN_REP(11);
	VEC_XORVN_REP(12);
	VEC_XORVN_REP(13);
	VEC_XORVN_REP(14);
	VEC_XORVN_REP(15);
	VEC_XORVN_REP(16);
	VEC_XORVN_REP(17);
	VEC_XORVN_REP(18);
	VEC_XORVN_REP(19);
	VEC_XORVN_REP(20);
	VEC_XORVN_REP(21);
	VEC_XORVN_REP(22);
	VEC_XORVN_REP(23);
	VEC_XORVN_REP(24);
	VEC_XORVN_REP(25);
	VEC_XORVN_REP(26);
	VEC_XORVN_REP(27);
	VEC_XORVN_REP(28);
	VEC_XORVN_REP(29);
	VEC_XORVN_REP(30);
	VEC_XORVN_REP(31);
return;
.wait;




end ".text_nmvcore";
