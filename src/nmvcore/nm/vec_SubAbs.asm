//------------------------------------------------------------------------
//
//  $Workfile:: Math_SubAbs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_SubAbs.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


macro VEC_SUB_ABS_REP(N)
		rep N data=[ar0++gr0]	with data;
		rep N data=[ar1++gr1]	with afifo-data;
	delayed return;
		rep N [ar4],ram =afifo	with activate afifo;
		rep N					with vsum afifo,ram,ram;			
		rep N [ar6++gr6]= afifo;
	nul;nul;
end   VEC_SUB_ABS_REP;

SubAbs_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_SubAbs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_SubAbs :label;
<vec_SubAbs>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto SubAbs_repN with gr2>>=24;
		ar2 = SubAbs_rep0 with gr5--;
	<next_SubAbs_rep32>
		rep 32 data=[ar0++gr0]	with data;
		rep 32 data=[ar1++gr1]	with afifo-data;
		rep 32 [ar4],ram =afifo	with activate afifo;
		rep 32					with vsum afifo,ram,ram;			
	if <>0 delayed  goto next_SubAbs_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6]= afifo;
	<SubAbs_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<SubAbs_rep0>
	delayed return;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	VEC_SUB_ABS_REP(1);
	VEC_SUB_ABS_REP(2);
	VEC_SUB_ABS_REP(3);
	VEC_SUB_ABS_REP(4);
	VEC_SUB_ABS_REP(5);
	VEC_SUB_ABS_REP(6);
	VEC_SUB_ABS_REP(7);
	VEC_SUB_ABS_REP(8);
	VEC_SUB_ABS_REP(9);
	VEC_SUB_ABS_REP(10);
	VEC_SUB_ABS_REP(11);
	VEC_SUB_ABS_REP(12);
	VEC_SUB_ABS_REP(13);
	VEC_SUB_ABS_REP(14);
	VEC_SUB_ABS_REP(15);
	VEC_SUB_ABS_REP(16);
	VEC_SUB_ABS_REP(17);
	VEC_SUB_ABS_REP(18);
	VEC_SUB_ABS_REP(19);
	VEC_SUB_ABS_REP(20);
	VEC_SUB_ABS_REP(21);
	VEC_SUB_ABS_REP(22);
	VEC_SUB_ABS_REP(23);
	VEC_SUB_ABS_REP(24);
	VEC_SUB_ABS_REP(25);
	VEC_SUB_ABS_REP(26);
	VEC_SUB_ABS_REP(27);
	VEC_SUB_ABS_REP(28);
	VEC_SUB_ABS_REP(29);
	VEC_SUB_ABS_REP(30);
	VEC_SUB_ABS_REP(31);
return;
.wait;




end ".text_nmvcore";
