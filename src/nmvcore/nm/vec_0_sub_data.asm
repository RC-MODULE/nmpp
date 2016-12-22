//------------------------------------------------------------------------
//
//  $Workfile:: 0_sub_d $
//
//  Векторно-матричная библиотека
//
//  Negright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   sub_data.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_NEG_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data = [ar0++gr0] with 0-data;
		rep N [ar6++gr6] = afifo;
		nul;
.endif;
end VEC_NEG_REP;
Neg_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_0_sub_data(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!			 
    //------------------------------------------------------------------------
global vec_0_sub_data :label;
<vec_0_sub_data>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Neg_repN with gr2>>=25;
		ar2 = Neg_rep0 with gr5--;
		
	<next_Neg_rep32>
	if <>0 delayed goto next_Neg_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with 0-data;
		rep 32 [ar6++gr6] = afifo;
	<Neg_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Neg_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_NEG_REP(1);
	VEC_NEG_REP(2);
	VEC_NEG_REP(3);
	VEC_NEG_REP(4);
	VEC_NEG_REP(5);
	VEC_NEG_REP(6);
	VEC_NEG_REP(7);
	VEC_NEG_REP(8);
	VEC_NEG_REP(9);
	VEC_NEG_REP(10);
	VEC_NEG_REP(11);
	VEC_NEG_REP(12);
	VEC_NEG_REP(13);
	VEC_NEG_REP(14);
	VEC_NEG_REP(15);
	VEC_NEG_REP(16);
	VEC_NEG_REP(17);
	VEC_NEG_REP(18);
	VEC_NEG_REP(19);
	VEC_NEG_REP(20);
	VEC_NEG_REP(21);
	VEC_NEG_REP(22);
	VEC_NEG_REP(23);
	VEC_NEG_REP(24);
	VEC_NEG_REP(25);
	VEC_NEG_REP(26);
	VEC_NEG_REP(27);
	VEC_NEG_REP(28);
	VEC_NEG_REP(29);
	VEC_NEG_REP(30);
	VEC_NEG_REP(31);
return;
.wait;



end ".text_nmvcore";
