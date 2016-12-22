//------------------------------------------------------------------------
//
//  $Workfile:: Math_Sub.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_Sub.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();


macro VEC_SUB_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data = [ar0++gr0] with data;
		rep N data = [ar1++gr1] with afifo - data;
		rep N [ar6++gr6] = afifo;
.endif;
end   VEC_SUB_REP;

Sub_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Sub(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Sub :label;
<vec_Sub>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Sub_repN with gr2>>=25;
		ar2 = Sub_rep0 with gr5--;
	next_Sub_rep32:label;
	ar5 = next_Sub_rep32;
	<next_Sub_rep32>
	if <>0 delayed goto ar5 with gr5--;	
		rep 32 data = [ar0++gr0] with data;
		rep 32 data = [ar1++gr1] with afifo - data;
		rep 32 [ar6++gr6] = afifo;
	<Sub_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Sub_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_SUB_REP(1);
	VEC_SUB_REP(2);
	VEC_SUB_REP(3);
	VEC_SUB_REP(4);
	VEC_SUB_REP(5);
	VEC_SUB_REP(6);
	VEC_SUB_REP(7);
	VEC_SUB_REP(8);
	VEC_SUB_REP(9);
	VEC_SUB_REP(10);
	VEC_SUB_REP(11);
	VEC_SUB_REP(12);
	VEC_SUB_REP(13);
	VEC_SUB_REP(14);
	VEC_SUB_REP(15);
	VEC_SUB_REP(16);
	VEC_SUB_REP(17);
	VEC_SUB_REP(18);
	VEC_SUB_REP(19);
	VEC_SUB_REP(20);
	VEC_SUB_REP(21);
	VEC_SUB_REP(22);
	VEC_SUB_REP(23);
	VEC_SUB_REP(24);
	VEC_SUB_REP(25);
	VEC_SUB_REP(26);
	VEC_SUB_REP(27);
	VEC_SUB_REP(28);
	VEC_SUB_REP(29);
	VEC_SUB_REP(30);
	VEC_SUB_REP(31);
return;
.wait;




end ".text_nmvcore";
