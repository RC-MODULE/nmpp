//------------------------------------------------------------------------
//
//  $Workfile:: Math_Abs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Abs.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------




begin ".text_nmvcore"

//extern _VEC_TBL_Diagonal_FFh_G:long;
//extern _VEC_TBL_Diagonal_FFFFh_G:long;
//extern _VEC_TBL_Diagonal_FFFFFFFFh_G:long;
//extern _nmppsTmpBuffer64_G_:long;
import from minrep.mlb;
DEF_MIN_REP();


macro VEC_ABS_REP(N)
.if (NMPP_MIN_REP<=N);
	delayed return;
		rep N data,ram =[ar0++gr0]	with activate data;
		rep N					with vsum afifo,ram,ram;			
		rep N [ar6++gr6]= afifo;
.endif;
end   VEC_ABS_REP;

Abs_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Abs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Abs :label;
<vec_Abs>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Abs_repN with gr2>>=25;
	
	ar2 = Abs_rep0 with gr5--;
	<next_Abs_rep32>	
		rep 32 data,ram =[ar0++gr0]	with activate data;
		rep 32					with vsum afifo,ram,ram;			
	if <>0 delayed  goto next_Abs_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6]= afifo;
	<Abs_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Abs_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_ABS_REP(1);
	VEC_ABS_REP(2);
	VEC_ABS_REP(3);
	VEC_ABS_REP(4);
	VEC_ABS_REP(5);
	VEC_ABS_REP(6);
	VEC_ABS_REP(7);
	VEC_ABS_REP(8);
	VEC_ABS_REP(9);
	VEC_ABS_REP(10);
	VEC_ABS_REP(11);
	VEC_ABS_REP(12);
	VEC_ABS_REP(13);
	VEC_ABS_REP(14);
	VEC_ABS_REP(15);
	VEC_ABS_REP(16);
	VEC_ABS_REP(17);
	VEC_ABS_REP(18);
	VEC_ABS_REP(19);
	VEC_ABS_REP(20);
	VEC_ABS_REP(21);
	VEC_ABS_REP(22);
	VEC_ABS_REP(23);
	VEC_ABS_REP(24);
	VEC_ABS_REP(25);
	VEC_ABS_REP(26);
	VEC_ABS_REP(27);
	VEC_ABS_REP(28);
	VEC_ABS_REP(29);
	VEC_ABS_REP(30);
	VEC_ABS_REP(31);
return;
.wait;




end ".text_nmvcore";
