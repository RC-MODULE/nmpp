//------------------------------------------------------------------------
//
//  $Workfile:: Mul_2V8toW16_shift.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Mul_2V8toW16_shift.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"
import from minrep.mlb;
DEF_MIN_REP();

macro VEC_MUL_2V8toW16_SHIFT_REP(N)
.if (NMPP_MIN_REP <= N);
		rep N ram = [ar3];
		rep N data=[ar0++gr0],ftw,wtw with vsum ,data,0;
 		delayed return; 
 			rep N data=[ar1++gr1]	  with vsum ,data,afifo;
			rep N wtw with mask ram,shift afifo,0;
			rep N [ar6++gr6]=afifo;	
		
		nul;
		nul;
.endif;
end   VEC_MUL_2V8toW16_SHIFT_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_MUL_2V8toW16_shift(nmreg nb1, nmreg sb, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr4, nmreg ar5, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_MUL_2V8toW16_shift:label;
<vec_MUL_2V8toW16_shift>
.branch;
MUL_2V8toW16_SHIFT_rep0:label;
	push ar2,gr2 	with gr2 = gr5<<27;
	push ar4,gr4	with gr2>>=23+1;
	ar4 = ar5	with gr5>>=5; 
	rep 16 wfifo=[ar4++],ftw,wtw;

	ar2 = MUL_2V8toW16_SHIFT_rep0 with gr5;
	
	if <= delayed goto end_MUL_2V8toW16_SHIFT_rep32 with gr5--;
		ar4 = ar5;
		ar2+=gr2 ;

	rep 32 ram = [ar3];
////////////////////////////////////////////////////////////////////////
<MUL_2V8toW16_SHIFT_rep32>
		rep 32 data =[ar0++gr0],ftw,wtw with vsum ,data,0;
		rep 16  wfifo=[ar4++],ftw;
		rep 32 data =[ar1++gr1]		with vsum ,data,afifo;
		rep 32 wtw with mask ram,shift afifo,0;
	if  <>0 delayed  goto MUL_2V8toW16_SHIFT_rep32 with gr5--; 
		ar4 = ar5;
		rep 32 [ar6++gr6]=afifo;
<end_MUL_2V8toW16_SHIFT_rep32>
////////////////////////////////////////////////////////////////////////
	delayed goto ar2; 
		pop ar4,gr4;
		pop ar2,gr2;
////////////////////////////////////////////////////////////////////////
	<MUL_2V8toW16_SHIFT_rep0>
	delayed return;
		ftw;   // Set empty wfifo
		wtw;
		nul;
	.repeat 4;
		nul;
	.endrepeat;
	VEC_MUL_2V8toW16_SHIFT_REP(1);
	VEC_MUL_2V8toW16_SHIFT_REP(2);
	VEC_MUL_2V8toW16_SHIFT_REP(3);
	VEC_MUL_2V8toW16_SHIFT_REP(4);
	VEC_MUL_2V8toW16_SHIFT_REP(5);
	VEC_MUL_2V8toW16_SHIFT_REP(6);
	VEC_MUL_2V8toW16_SHIFT_REP(7);
	VEC_MUL_2V8toW16_SHIFT_REP(8);
	VEC_MUL_2V8toW16_SHIFT_REP(9);
	VEC_MUL_2V8toW16_SHIFT_REP(10);
	VEC_MUL_2V8toW16_SHIFT_REP(11);
	VEC_MUL_2V8toW16_SHIFT_REP(12);
	VEC_MUL_2V8toW16_SHIFT_REP(13);
	VEC_MUL_2V8toW16_SHIFT_REP(14);
	VEC_MUL_2V8toW16_SHIFT_REP(15);
	VEC_MUL_2V8toW16_SHIFT_REP(16);
	VEC_MUL_2V8toW16_SHIFT_REP(17);
	VEC_MUL_2V8toW16_SHIFT_REP(18);
	VEC_MUL_2V8toW16_SHIFT_REP(19);
	VEC_MUL_2V8toW16_SHIFT_REP(20);
	VEC_MUL_2V8toW16_SHIFT_REP(21);
	VEC_MUL_2V8toW16_SHIFT_REP(22);
	VEC_MUL_2V8toW16_SHIFT_REP(23);
	VEC_MUL_2V8toW16_SHIFT_REP(24);
	VEC_MUL_2V8toW16_SHIFT_REP(25);
	VEC_MUL_2V8toW16_SHIFT_REP(26);
	VEC_MUL_2V8toW16_SHIFT_REP(27);
	VEC_MUL_2V8toW16_SHIFT_REP(28);
	VEC_MUL_2V8toW16_SHIFT_REP(29);
	VEC_MUL_2V8toW16_SHIFT_REP(30);
	VEC_MUL_2V8toW16_SHIFT_REP(31);	
//////////////////////////////////////////////////////////////////////////////////
.wait;
end ".text_nmvcore";
