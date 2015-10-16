//------------------------------------------------------------------------
//
//  $Workfile:: Math_SubVN_Abs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_SubVN_Abs.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"


//extern _VEC_TBL_Diagonal_FFh_G:long;
//extern _VEC_TBL_Diagonal_FFFFh_G:long;
//extern _VEC_TBL_Diagonal_FFFFFFFFh_G:long;
extern _VEC_TmpBuffer64_G:long;


begin ".text_nmvcore"


macro VEC_SUBVN_ABS_REP(N)
	rep N data=[ar1]		with data;
	rep N data=[ar0++gr0]	with afifo-data;
	rep N [ar2],ram =afifo	with activate afifo;
	pop ar2,gr2;
	delayed return;
		rep N				with vsum afifo,ram,ram;
		rep N [ar6++gr6]=afifo;
		nul;
end VEC_SUBVN_ABS_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_SubVN_Abs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

<vec_SubVN_Abs>
global vec_SubVN_Abs:label;
.branch;
	SubVN_Abs_rep0:label;
	push ar2,gr2 with gr2=gr5<<26;	// %64
	push ar5,gr5 with gr5>>=6;		// /64

	ar5=_VEC_TmpBuffer64_G;
	if =0 delayed goto SubVN_Abs_rep32 with gr2>>=26;	//%64
		ar2 = ar5 with gr5--;
		nul;

	rep 32 ram=[ar1];
	<Next_SubVN_Abs_rep64>
		rep 32 data=[ar0++gr0]	with ram-data;
		rep 32 [ar2++] = afifo	with activate afifo;
		rep 32 data=[ar5++]		with vsum afifo,data,data;
		rep 32 [ar6++gr6]=afifo;

		rep 32 data=[ar0++gr0]	with ram-data;
		rep 32 [--ar2] = afifo	with activate afifo;
	if <>0 delayed  goto Next_SubVN_Abs_rep64 with gr5--;
		rep 32 data=[--ar5]		with vsum afifo,data,data;
		rep 32 [ar6++gr6]=afifo;

	<SubVN_Abs_rep32>
	gr5 = gr2>>5;
	if =0 delayed goto SubVN_Abs_repN	with gr2 = gr2<<27;
		ar2 = SubVN_Abs_rep0			with gr2>>=24;

	rep 32 data=[ar1]		 with data;
	rep 32 data=[ar0++gr0]   with afifo-data;
	rep 32 [ar5],ram = afifo with activate afifo;
	rep 32					 with vsum afifo,ram,ram;
	rep 32 [ar6++gr6]=afifo;
	
	<SubVN_Abs_repN>
	ar2+= gr2;
	delayed goto ar2;
		ar2 = ar5;
		pop ar5,gr5;
	<SubVN_Abs_rep0>
	pop ar2,gr2;
	delayed return;
		nul;
		nul;
	nul;
	nul;
	nul;
	nul;
	VEC_SUBVN_ABS_REP(1);
	VEC_SUBVN_ABS_REP(2);
	VEC_SUBVN_ABS_REP(3);
	VEC_SUBVN_ABS_REP(4);
	VEC_SUBVN_ABS_REP(5);
	VEC_SUBVN_ABS_REP(6);
	VEC_SUBVN_ABS_REP(7);
	VEC_SUBVN_ABS_REP(8);
	VEC_SUBVN_ABS_REP(9);
	VEC_SUBVN_ABS_REP(10);
	VEC_SUBVN_ABS_REP(11);
	VEC_SUBVN_ABS_REP(12);
	VEC_SUBVN_ABS_REP(13);
	VEC_SUBVN_ABS_REP(14);
	VEC_SUBVN_ABS_REP(15);
	VEC_SUBVN_ABS_REP(16);
	VEC_SUBVN_ABS_REP(17);
	VEC_SUBVN_ABS_REP(18);
	VEC_SUBVN_ABS_REP(19);
	VEC_SUBVN_ABS_REP(20);
	VEC_SUBVN_ABS_REP(21);
	VEC_SUBVN_ABS_REP(22);
	VEC_SUBVN_ABS_REP(23);
	VEC_SUBVN_ABS_REP(24);
	VEC_SUBVN_ABS_REP(25);
	VEC_SUBVN_ABS_REP(26);
	VEC_SUBVN_ABS_REP(27);
	VEC_SUBVN_ABS_REP(28);
	VEC_SUBVN_ABS_REP(29);
	VEC_SUBVN_ABS_REP(30);
	VEC_SUBVN_ABS_REP(31);
.wait;


end ".text_nmvcore";
