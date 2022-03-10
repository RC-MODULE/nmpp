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

macro MUL1D1W_ADD_REP(N)
.if (NMPP_MIN_REP <= N);
		delayed return; 
			rep N ram =[ar1++gr1];
			rep N data=[ar0++gr0]	  with vsum ,activate data,activate ram;
			rep N [ar6++gr6]=afifo;	
.endif;
end MUL1D1W_ADD_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_ClipMul2D2W8_AddVr(nmreg f1cr,nmreg f2cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_ClipMul1D1W_AddClipD:label;
      <vec_ClipMul1D1W_AddClipD>
.branch;
	Next_Mul1D1W8_AddClipD_rep0:label;
	Next_Mul1D1W8_AddClipD_rep32:label;
	push ar5,gr5	with gr7=gr5>>5;
					with gr5<<=27;
					with gr5>>=25;
	ar5 = Next_Mul1D1W8_AddClipD_rep0;
	push ar5,gr5	with gr7;
	if  =0 delayed goto Next_Mul1D1W8_AddClipD_repN with gr7--;
		gr5 = Next_Mul1D1W8_AddClipD_rep32;
		
	<Next_Mul1D1W8_AddClipD_rep32>
	if  <>0 delayed  goto gr5 with gr7--; 
		rep 32 ram =[ar1++gr1];
		rep 32 data =[ar0++gr0]		with vsum ,activate data,activate ram;
		rep 32 [ar6++gr6]=afifo;

	<Next_Mul1D1W8_AddClipD_repN>
	pop ar5,gr5;
	nul;
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Next_Mul1D1W8_AddClipD_rep0>
	delayed return;
		nul;
		nul;
		nul;

	MUL1D1W_ADD_REP(1);
	MUL1D1W_ADD_REP(2);
	MUL1D1W_ADD_REP(3);
	MUL1D1W_ADD_REP(4);
	MUL1D1W_ADD_REP(5);
	MUL1D1W_ADD_REP(6);
	MUL1D1W_ADD_REP(7);
	MUL1D1W_ADD_REP(8);
	MUL1D1W_ADD_REP(9);
	MUL1D1W_ADD_REP(10);
	MUL1D1W_ADD_REP(11);
	MUL1D1W_ADD_REP(12);
	MUL1D1W_ADD_REP(13);
	MUL1D1W_ADD_REP(14);
	MUL1D1W_ADD_REP(15);
	MUL1D1W_ADD_REP(16);
	MUL1D1W_ADD_REP(17);
	MUL1D1W_ADD_REP(18);
	MUL1D1W_ADD_REP(19);
	MUL1D1W_ADD_REP(20);
	MUL1D1W_ADD_REP(21);
	MUL1D1W_ADD_REP(22);
	MUL1D1W_ADD_REP(23);
	MUL1D1W_ADD_REP(24);
	MUL1D1W_ADD_REP(25);
	MUL1D1W_ADD_REP(26);
	MUL1D1W_ADD_REP(27);
	MUL1D1W_ADD_REP(28);
	MUL1D1W_ADD_REP(29);
	MUL1D1W_ADD_REP(30);
	MUL1D1W_ADD_REP(31);
.wait;


end ".text_nmvcore";
