//------------------------------------------------------------------------
//
//  $Workfile:: Math_Mul2D2W4.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_Mul2D2W4.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"




begin ".text_nmvcore"
import from minrep.mlb;
DEF_MIN_REP();

macro MTR_MUL2D2W4_REP(N)
.if (NMPP_MIN_REP <= N);
		delayed return; 
			rep N data=[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
			rep N data=[ar1++gr1],wtw	  with vsum ,activate data,afifo;
			rep N [ar6++gr6]=afifo;	
.endif;
end MTR_MUL2D2W4_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_Mul2D2W4_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Mul2D2W4_AddVr:label;
      <vec_Mul2D2W4_AddVr>
.branch;
	Mul2D2W4_AddVr_rep0:label;
	push ar5,gr5	with gr7=gr5>>5;
	ar5 = ar4		with gr5<<=27;
	rep 8 wfifo=[ar4++],ftw;
	
	///				with gr5>>=24;
					with gr5>>=24+1;
	ar4 = ar5		with gr7;
	if  =0 delayed goto Mul2D2W4_AddVr_repN with gr7--;
		wtw;
		nul;
		
	<Next_Mul2D2W4_AddVr_rep32>
		rep 32 data =[ar0++gr0],ftw,wtw with vsum , activate data, vr;
		rep 8  wfifo=[ar4++],ftw;
		rep 32 data =[ar1++gr1],wtw		with vsum , activate data, afifo;
	if  <>0 delayed  goto Next_Mul2D2W4_AddVr_rep32 with gr7--; 
		ar4 = ar5;
		rep 32 [ar6++gr6]=afifo;

	<Mul2D2W4_AddVr_repN>
	ar5 = Mul2D2W4_AddVr_rep0;
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Mul2D2W4_AddVr_rep0>
	delayed return;
		ftw;
		wtw;   // Clear wfifo
		nul;
	
	MTR_MUL2D2W4_REP(1);
	MTR_MUL2D2W4_REP(2);
	MTR_MUL2D2W4_REP(3);
	MTR_MUL2D2W4_REP(4);
	MTR_MUL2D2W4_REP(5);
	MTR_MUL2D2W4_REP(6);
	MTR_MUL2D2W4_REP(7);
	MTR_MUL2D2W4_REP(8);
	MTR_MUL2D2W4_REP(9);
	MTR_MUL2D2W4_REP(10);
	MTR_MUL2D2W4_REP(11);
	MTR_MUL2D2W4_REP(12);
	MTR_MUL2D2W4_REP(13);
	MTR_MUL2D2W4_REP(14);
	MTR_MUL2D2W4_REP(15);
	MTR_MUL2D2W4_REP(16);
	MTR_MUL2D2W4_REP(17);
	MTR_MUL2D2W4_REP(18);
	MTR_MUL2D2W4_REP(19);
	MTR_MUL2D2W4_REP(20);
	MTR_MUL2D2W4_REP(21);
	MTR_MUL2D2W4_REP(22);
	MTR_MUL2D2W4_REP(23);
	MTR_MUL2D2W4_REP(24);
	MTR_MUL2D2W4_REP(25);
	MTR_MUL2D2W4_REP(26);
	MTR_MUL2D2W4_REP(27);
	MTR_MUL2D2W4_REP(28);
	MTR_MUL2D2W4_REP(29);
	MTR_MUL2D2W4_REP(30);
	MTR_MUL2D2W4_REP(31);
.wait;


end ".text_nmvcore";
