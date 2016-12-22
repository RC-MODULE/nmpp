//------------------------------------------------------------------------
//
//  $Workfile:: Math_ClipMul2D2W8.asm   $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Mul2D2W8.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------



///import from macros.mlb;

begin ".text_nmvcore"



import from minrep.mlb;
DEF_MIN_REP();

macro MTR_MUL2D2W8_REP(N)
.if (NMPP_MIN_REP <= N);
		delayed return; 
			rep N data=[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
			rep N data=[ar1++gr1],wtw	  with vsum ,activate data,afifo;
			rep N [ar6++gr6]=afifo;	
.endif;
end MTR_MUL2D2W8_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_ClipMul2D2W8_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_ClipMul2D2W8_AddVr:label;
      <vec_ClipMul2D2W8_AddVr>
.branch;
	Mul2D2W8_AddVr_rep0:label;
	Next_Mul2D2W8_AddVr_rep32:label;
	push ar5,gr5	with gr7=gr5>>5;
	ar5 = ar4		with gr5<<=27;
	rep 16 wfifo=[ar4++],ftw;
	///ar4 = ar5		with gr5>>=24;
	ar4 = ar5		with gr5>>=25;
	ar5 = Mul2D2W8_AddVr_rep0;
	push ar5,gr5;
	ar5 = ar4		with gr7;
	gr5 = Next_Mul2D2W8_AddVr_rep32;
	if  =0 delayed goto Mul2D2W8_AddVr_repN with gr7--;
		wtw;	
		nul;

	<Next_Mul2D2W8_AddVr_rep32>
		rep 32 data =[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
		rep 16 wfifo=[ar4++],ftw;
	if  <>0 delayed  goto gr5 with gr7--; 
		rep 32 data =[ar1++gr1],wtw		with vsum ,activate data,afifo;
		ar4 = ar5;
		rep 32 [ar6++gr6]=afifo;

	<Mul2D2W8_AddVr_repN>
	pop ar5,gr5;
	nul;
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Mul2D2W8_AddVr_rep0>
	delayed return;
		ftw;
		wtw;
		nul;

	MTR_MUL2D2W8_REP(1);
	MTR_MUL2D2W8_REP(2);
	MTR_MUL2D2W8_REP(3);
	MTR_MUL2D2W8_REP(4);
	MTR_MUL2D2W8_REP(5);
	MTR_MUL2D2W8_REP(6);
	MTR_MUL2D2W8_REP(7);
	MTR_MUL2D2W8_REP(8);
	MTR_MUL2D2W8_REP(9);
	MTR_MUL2D2W8_REP(10);
	MTR_MUL2D2W8_REP(11);
	MTR_MUL2D2W8_REP(12);
	MTR_MUL2D2W8_REP(13);
	MTR_MUL2D2W8_REP(14);
	MTR_MUL2D2W8_REP(15);
	MTR_MUL2D2W8_REP(16);
	MTR_MUL2D2W8_REP(17);
	MTR_MUL2D2W8_REP(18);
	MTR_MUL2D2W8_REP(19);
	MTR_MUL2D2W8_REP(20);
	MTR_MUL2D2W8_REP(21);
	MTR_MUL2D2W8_REP(22);
	MTR_MUL2D2W8_REP(23);
	MTR_MUL2D2W8_REP(24);
	MTR_MUL2D2W8_REP(25);
	MTR_MUL2D2W8_REP(26);
	MTR_MUL2D2W8_REP(27);
	MTR_MUL2D2W8_REP(28);
	MTR_MUL2D2W8_REP(29);
	MTR_MUL2D2W8_REP(30);
	MTR_MUL2D2W8_REP(31);
.wait;


end ".text_nmvcore";
