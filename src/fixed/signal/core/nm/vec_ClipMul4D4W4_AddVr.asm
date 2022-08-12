//------------------------------------------------------------------------
//
//  $Workfile:: Math_Mul4D4W4.asm $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Mul4D4W4.asm
//! \author Сергей Свечников
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"




begin ".text_nmvcore"

   
import from minrep.mlb;
DEF_MIN_REP();

macro MTR_MUL4D4W4_REP(N)
.if (NMPP_MIN_REP <= N);
		rep N data=[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
 		rep N data=[ar1++gr1],ftw,wtw with vsum ,activate data,afifo;
		delayed return; 
			rep N data=[ar2++gr2],ftw,wtw with vsum ,activate data,afifo;
			rep N data=[ar3++gr3] with vsum ,activate data,afifo;
			rep N [ar6++gr6]=afifo;	
		nul;
		nul;
.endif;
end MTR_MUL4D4W4_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_ClipMul4D4W4_AddVr(nmreg nb1, nmreg sb, nmreg F1CR, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg ar3, nmreg gr3, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_ClipMul4D4W4_AddVr:label;
      <vec_ClipMul4D4W4_AddVr>
.branch;
	Mul4D4W4_AddVr_rep0:label;
	push ar4, gr4;		with gr7=gr5>>5;
	push ar5, gr5		with gr5<<=27;
	ar5 = ar4		with gr7;
	rep 16 wfifo=[ar4++],ftw,wtw;
	if =0 delayed goto Mul4D4W4_AddVr_repN with gr7--;
		ar4 = ar5	with gr5>>=24;
		with gr7;


	
	Next_Mul4D4W4_AddVr_rep32:label;
	gr4 = Next_Mul4D4W4_AddVr_rep32;
<Next_Mul4D4W4_AddVr_rep32>
		rep 32 data =[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
 		rep 32 data =[ar1++gr1],ftw,wtw with vsum ,activate data,afifo;
		rep 32 data =[ar2++gr2],ftw,wtw with vsum ,activate data,afifo;
		rep 16  wfifo=[ar4++],ftw;
	if <>0 delayed  goto gr4 with gr7--; 
		rep 32 data =[ar3++gr3],wtw	    with vsum ,activate data,afifo;
		ar4 = ar5;
		rep 32 [ar6++gr6]=afifo;

	<Mul4D4W4_AddVr_repN>
	ar5 = Mul4D4W4_AddVr_rep0;
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		pop ar4,gr4;
<Mul4D4W4_AddVr_rep0>
		ftw;
		wtw;   // Clear wfifo
		ftw;
		wtw;
	delayed return;	
		ftw;
		wtw;
		nul;
	MTR_MUL4D4W4_REP(1);
	MTR_MUL4D4W4_REP(2);
	MTR_MUL4D4W4_REP(3);
	MTR_MUL4D4W4_REP(4);
	MTR_MUL4D4W4_REP(5);
	MTR_MUL4D4W4_REP(6);
	MTR_MUL4D4W4_REP(7);
	MTR_MUL4D4W4_REP(8);
	MTR_MUL4D4W4_REP(9);
	MTR_MUL4D4W4_REP(10);
	MTR_MUL4D4W4_REP(11);
	MTR_MUL4D4W4_REP(12);
	MTR_MUL4D4W4_REP(13);
	MTR_MUL4D4W4_REP(14);
	MTR_MUL4D4W4_REP(15);
	MTR_MUL4D4W4_REP(16);
	MTR_MUL4D4W4_REP(17);
	MTR_MUL4D4W4_REP(18);
	MTR_MUL4D4W4_REP(19);
	MTR_MUL4D4W4_REP(20);
	MTR_MUL4D4W4_REP(21);
	MTR_MUL4D4W4_REP(22);
	MTR_MUL4D4W4_REP(23);
	MTR_MUL4D4W4_REP(24);
	MTR_MUL4D4W4_REP(25);
	MTR_MUL4D4W4_REP(26);
	MTR_MUL4D4W4_REP(27);
	MTR_MUL4D4W4_REP(28);
	MTR_MUL4D4W4_REP(29);
	MTR_MUL4D4W4_REP(30);
	MTR_MUL4D4W4_REP(31);
.wait;
end ".text_nmvcore";

