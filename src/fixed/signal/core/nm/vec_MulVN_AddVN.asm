//------------------------------------------------------------------------
//
//  $Workfile:: Math_MulVN_AddVN.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_MulVN_AddVN.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();
     
macro VEC_MUL_VN_ADD_VN_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data=[ar0++gr0]	with vsum , data,vr;
		rep N data=[ar1++gr1]	with afifo+data;
		rep N [ar6++gr6]=afifo;
.endif;
end VEC_MUL_VN_ADD_VN_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_MulVN_AddVN(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

<vec_MulVN_AddVN>
global vec_MulVN_AddVN:label;
.branch;
	MulVN_AddVN_rep0:label;
	push ar2,gr2 with gr2=gr5<<27;
	push ar5,gr5 with gr5>>=5;
	if =0 delayed goto MulVN_AddVN_repN with gr2>>=25;
		ar2 = MulVN_AddVN_rep0 with gr5--;
	
	<Next_MulVN_AddVN_rep32>
		rep 32 data = [ar0++gr0]	with vsum , data, vr;
		rep 32 data = [ar1++gr1]	with afifo+data;
	if <>0 delayed goto Next_MulVN_AddVN_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6]=afifo;
	<MulVN_AddVN_repN>
	ar2+=gr2;
	delayed goto ar2 ; 
		pop ar5,gr5;
		pop ar2,gr2;
	<MulVN_AddVN_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_MUL_VN_ADD_VN_REP(1);
	VEC_MUL_VN_ADD_VN_REP(2);
	VEC_MUL_VN_ADD_VN_REP(3);
	VEC_MUL_VN_ADD_VN_REP(4);
	VEC_MUL_VN_ADD_VN_REP(5);
	VEC_MUL_VN_ADD_VN_REP(6);
	VEC_MUL_VN_ADD_VN_REP(7);
	VEC_MUL_VN_ADD_VN_REP(8);
	VEC_MUL_VN_ADD_VN_REP(9);
	VEC_MUL_VN_ADD_VN_REP(10);
	VEC_MUL_VN_ADD_VN_REP(11);
	VEC_MUL_VN_ADD_VN_REP(12);
	VEC_MUL_VN_ADD_VN_REP(13);
	VEC_MUL_VN_ADD_VN_REP(14);
	VEC_MUL_VN_ADD_VN_REP(15);
	VEC_MUL_VN_ADD_VN_REP(16);
	VEC_MUL_VN_ADD_VN_REP(17);
	VEC_MUL_VN_ADD_VN_REP(18);
	VEC_MUL_VN_ADD_VN_REP(19);
	VEC_MUL_VN_ADD_VN_REP(20);
	VEC_MUL_VN_ADD_VN_REP(21);
	VEC_MUL_VN_ADD_VN_REP(22);
	VEC_MUL_VN_ADD_VN_REP(23);
	VEC_MUL_VN_ADD_VN_REP(24);
	VEC_MUL_VN_ADD_VN_REP(25);
	VEC_MUL_VN_ADD_VN_REP(26);
	VEC_MUL_VN_ADD_VN_REP(27);
	VEC_MUL_VN_ADD_VN_REP(28);
	VEC_MUL_VN_ADD_VN_REP(29);
	VEC_MUL_VN_ADD_VN_REP(30);
	VEC_MUL_VN_ADD_VN_REP(31);
return;
.wait;


end ".text_nmvcore";
