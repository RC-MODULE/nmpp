//------------------------------------------------------------------------
//
//  $Workfile:: Add_VV_shift.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Add_VV_shift.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_ADD_VV_SHIFT_REP(N)
.if (NMPP_MIN_REP <= N);
	rep N ram = [ar4];
	rep N data = [ar0++gr0] with data + 0;
	rep N data = [ar1++gr1] with data + afifo;
	rep N with mask ram,shift afifo,0;
	delayed return;
		rep N [ar6++gr6] = afifo;
		nul;
		nul;
.endif;
end   VEC_ADD_VV_SHIFT_REP;


    //------------------------------------------------------------------------
    //! \fn void vec_Add_VV_shift(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Add_VV_shift:label;
<vec_Add_VV_shift>
.branch;
ADD_VV_SHIFT_rep0:label;

	ar2 = ADD_VV_SHIFT_rep0 with gr2 = gr5<<27;
	with gr2>>=24;
	ar2+=gr2 with gr5>>=5;

	if <= delayed goto end_ADD_VV_SHIFT_rep32 with gr5--;
		nul;
		nul;
	rep 32 ram = [ar4];
////////////////////////////////////////////////////////////////////////
<ADD_VV_SHIFT_rep32>
	rep 32 data = [ar0++gr0] with data + 0;
	rep 32 data = [ar1++gr1] with data + afifo;
	if > delayed goto ADD_VV_SHIFT_rep32 with gr5--;
		rep 32 with mask ram,shift afifo,0;
		rep 32 [ar6++gr6] = afifo;
<end_ADD_VV_SHIFT_rep32>
////////////////////////////////////////////////////////////////////////
	delayed goto ar2; 
		nul;
		nul;
////////////////////////////////////////////////////////////////////////
	<ADD_VV_SHIFT_rep0>
	delayed return;
		.repeat 7;
			nul;
		.endrepeat;
	VEC_ADD_VV_SHIFT_REP(1);
	VEC_ADD_VV_SHIFT_REP(2);
	VEC_ADD_VV_SHIFT_REP(3);
	VEC_ADD_VV_SHIFT_REP(4);
	VEC_ADD_VV_SHIFT_REP(5);
	VEC_ADD_VV_SHIFT_REP(6);
	VEC_ADD_VV_SHIFT_REP(7);
	VEC_ADD_VV_SHIFT_REP(8);
	VEC_ADD_VV_SHIFT_REP(9);
	VEC_ADD_VV_SHIFT_REP(10);
	VEC_ADD_VV_SHIFT_REP(11);
	VEC_ADD_VV_SHIFT_REP(12);
	VEC_ADD_VV_SHIFT_REP(13);
	VEC_ADD_VV_SHIFT_REP(14);
	VEC_ADD_VV_SHIFT_REP(15);
	VEC_ADD_VV_SHIFT_REP(16);
	VEC_ADD_VV_SHIFT_REP(17);
	VEC_ADD_VV_SHIFT_REP(18);
	VEC_ADD_VV_SHIFT_REP(19);
	VEC_ADD_VV_SHIFT_REP(20);
	VEC_ADD_VV_SHIFT_REP(21);
	VEC_ADD_VV_SHIFT_REP(22);
	VEC_ADD_VV_SHIFT_REP(23);
	VEC_ADD_VV_SHIFT_REP(24);
	VEC_ADD_VV_SHIFT_REP(25);
	VEC_ADD_VV_SHIFT_REP(26);
	VEC_ADD_VV_SHIFT_REP(27);
	VEC_ADD_VV_SHIFT_REP(28);
	VEC_ADD_VV_SHIFT_REP(29);
	VEC_ADD_VV_SHIFT_REP(30);
	VEC_ADD_VV_SHIFT_REP(31);	
//////////////////////////////////////////////////////////////////////////////////
.wait;
end ".text_nmvcore";
