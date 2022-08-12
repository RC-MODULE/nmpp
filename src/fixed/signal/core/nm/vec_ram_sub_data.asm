//------------------------------------------------------------------------
//
//  $Workfile:: ram_sub_data.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   ram_sub_data.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_SUBNV_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N ram=[ar1];
		rep N data = [ar0++gr0] with ram-data;
		rep N [ar6++gr6] = afifo;
.endif;
end VEC_SUBNV_REP;

SubNV_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_ram_sub_data(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_ram_sub_data :label;
<vec_ram_sub_data>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto SubNV_repN with gr2>>=25;
		ar2 = SubNV_rep0 with gr5--;
	rep 32 ram=[ar1];
	<next_SubNV_rep32>
	if <>0 delayed goto next_SubNV_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with ram-data;
		rep 32 [ar6++gr6] = afifo;
	<SubNV_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<SubNV_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_SUBNV_REP(1);
	VEC_SUBNV_REP(2);
	VEC_SUBNV_REP(3);
	VEC_SUBNV_REP(4);
	VEC_SUBNV_REP(5);
	VEC_SUBNV_REP(6);
	VEC_SUBNV_REP(7);
	VEC_SUBNV_REP(8);
	VEC_SUBNV_REP(9);
	VEC_SUBNV_REP(10);
	VEC_SUBNV_REP(11);
	VEC_SUBNV_REP(12);
	VEC_SUBNV_REP(13);
	VEC_SUBNV_REP(14);
	VEC_SUBNV_REP(15);
	VEC_SUBNV_REP(16);
	VEC_SUBNV_REP(17);
	VEC_SUBNV_REP(18);
	VEC_SUBNV_REP(19);
	VEC_SUBNV_REP(20);
	VEC_SUBNV_REP(21);
	VEC_SUBNV_REP(22);
	VEC_SUBNV_REP(23);
	VEC_SUBNV_REP(24);
	VEC_SUBNV_REP(25);
	VEC_SUBNV_REP(26);
	VEC_SUBNV_REP(27);
	VEC_SUBNV_REP(28);
	VEC_SUBNV_REP(29);
	VEC_SUBNV_REP(30);
	VEC_SUBNV_REP(31);
return;
.wait;




end ".text_nmvcore";
