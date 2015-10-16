//------------------------------------------------------------------------
//
//  $Workfile:: data_sub_ram.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data_sub_ram.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"



macro VEC_SUBVN_REP(N)
	delayed return;
		rep N ram=[ar1];
		rep N data = [ar0++gr0] with data-ram;
		rep N [ar6++gr6] = afifo;
end VEC_SUBVN_REP;

SubVN_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_data_sub_ram(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_data_sub_ram :label;
<vec_data_sub_ram>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto SubVN_repN with gr2>>=25;
		ar2 = SubVN_rep0 with gr5--;
	rep 32 ram=[ar1];
	<next_SubVN_rep32>
	if <>0 delayed goto next_SubVN_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with data-ram;
		rep 32 [ar6++gr6] = afifo;
	<SubVN_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<SubVN_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_SUBVN_REP(1);
	VEC_SUBVN_REP(2);
	VEC_SUBVN_REP(3);
	VEC_SUBVN_REP(4);
	VEC_SUBVN_REP(5);
	VEC_SUBVN_REP(6);
	VEC_SUBVN_REP(7);
	VEC_SUBVN_REP(8);
	VEC_SUBVN_REP(9);
	VEC_SUBVN_REP(10);
	VEC_SUBVN_REP(11);
	VEC_SUBVN_REP(12);
	VEC_SUBVN_REP(13);
	VEC_SUBVN_REP(14);
	VEC_SUBVN_REP(15);
	VEC_SUBVN_REP(16);
	VEC_SUBVN_REP(17);
	VEC_SUBVN_REP(18);
	VEC_SUBVN_REP(19);
	VEC_SUBVN_REP(20);
	VEC_SUBVN_REP(21);
	VEC_SUBVN_REP(22);
	VEC_SUBVN_REP(23);
	VEC_SUBVN_REP(24);
	VEC_SUBVN_REP(25);
	VEC_SUBVN_REP(26);
	VEC_SUBVN_REP(27);
	VEC_SUBVN_REP(28);
	VEC_SUBVN_REP(29);
	VEC_SUBVN_REP(30);
	VEC_SUBVN_REP(31);
return;
.wait;




end ".text_nmvcore";
