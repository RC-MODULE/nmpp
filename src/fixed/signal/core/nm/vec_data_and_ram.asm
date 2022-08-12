//------------------------------------------------------------------------
//
//  $Workfile:: data_and_ram.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data_and_ram.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_ANDVN_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N ram  = [ar1];
		rep N data = [ar0++gr0] with data and ram;
		rep N [ar6++gr6] = afifo;
.endif;
end   VEC_ANDVN_REP;

AndVN_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_data_and_ram(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6);
    //!
    //------------------------------------------------------------------------

//global vec_AndVN :label;
//<vec_AndVN>
global vec_data_and_ram:label;
<vec_data_and_ram>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto AndVN_repN with gr2>>=25;
		ar2 = AndVN_rep0 with gr5--;
	rep 32 ram = [ar1];
	<next_AndVN_rep32>
	if <>0 delayed goto next_AndVN_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with data and ram;
		rep 32 [ar6++gr6] = afifo;
	<AndVN_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<AndVN_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_ANDVN_REP(1);
	VEC_ANDVN_REP(2);
	VEC_ANDVN_REP(3);
	VEC_ANDVN_REP(4);
	VEC_ANDVN_REP(5);
	VEC_ANDVN_REP(6);
	VEC_ANDVN_REP(7);
	VEC_ANDVN_REP(8);
	VEC_ANDVN_REP(9);
	VEC_ANDVN_REP(10);
	VEC_ANDVN_REP(11);
	VEC_ANDVN_REP(12);
	VEC_ANDVN_REP(13);
	VEC_ANDVN_REP(14);
	VEC_ANDVN_REP(15);
	VEC_ANDVN_REP(16);
	VEC_ANDVN_REP(17);
	VEC_ANDVN_REP(18);
	VEC_ANDVN_REP(19);
	VEC_ANDVN_REP(20);
	VEC_ANDVN_REP(21);
	VEC_ANDVN_REP(22);
	VEC_ANDVN_REP(23);
	VEC_ANDVN_REP(24);
	VEC_ANDVN_REP(25);
	VEC_ANDVN_REP(26);
	VEC_ANDVN_REP(27);
	VEC_ANDVN_REP(28);
	VEC_ANDVN_REP(29);
	VEC_ANDVN_REP(30);
	VEC_ANDVN_REP(31);
return;
.wait;




end ".text_nmvcore";
