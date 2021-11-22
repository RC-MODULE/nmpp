//------------------------------------------------------------------------
//
//  $Workfile:: data.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_COPY_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data = [ar0++gr0] with data;
		rep N [ar6++gr6] = afifo;
		nul;
.endif;
end VEC_COPY_REP;

Copy_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_data(nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_data :label;
<vec_data>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Copy_repN with gr2>>=25;
		ar2 = Copy_rep0 with gr5--;
	<next_Copy_rep32>
	if <>0 delayed goto next_Copy_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with data;
		rep 32 [ar6++gr6] = afifo;
	<Copy_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Copy_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_COPY_REP(1);
	VEC_COPY_REP(2);
	VEC_COPY_REP(3);
	VEC_COPY_REP(4);
	VEC_COPY_REP(5);
	VEC_COPY_REP(6);
	VEC_COPY_REP(7);
	VEC_COPY_REP(8);
	VEC_COPY_REP(9);
	VEC_COPY_REP(10);
	VEC_COPY_REP(11);
	VEC_COPY_REP(12);
	VEC_COPY_REP(13);
	VEC_COPY_REP(14);
	VEC_COPY_REP(15);
	VEC_COPY_REP(16);
	VEC_COPY_REP(17);
	VEC_COPY_REP(18);
	VEC_COPY_REP(19);
	VEC_COPY_REP(20);
	VEC_COPY_REP(21);
	VEC_COPY_REP(22);
	VEC_COPY_REP(23);
	VEC_COPY_REP(24);
	VEC_COPY_REP(25);
	VEC_COPY_REP(26);
	VEC_COPY_REP(27);
	VEC_COPY_REP(28);
	VEC_COPY_REP(29);
	VEC_COPY_REP(30);
	VEC_COPY_REP(31);
return;
.wait;



end ".text_nmvcore";
