//------------------------------------------------------------------------
//
//  $Workfile:: Log_Mask.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Log_Mask.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();


macro VEC_MASK_REP(N)
.if (NMPP_MIN_REP <= N);
	rep N ram =[ar0++gr0];								// Read pSrcVec1
	rep N data=[ar1++gr1]	with data;					// Read pSrcVec2
	delayed return;
		rep N data=[ar2++gr2]	with mask data,ram,afifo;	// Read SrcVec3(Mask)
		rep N [ar6++gr6]=afifo;								// Write pDstVec
		nul;
	nul;
	nul;
.endif;
end   VEC_MASK_REP;

Mask_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Mask(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Mask :label;
<vec_Mask>
.branch;
	push ar4,gr4 with gr4=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Mask_repN with gr4>>=24;
		ar4 = Mask_rep0 with gr5--;
	<next_Mask_rep32>
		rep 32 ram =[ar0++gr0];								// Read pSrcVec1
		rep 32 data=[ar1++gr1]	with data;					// Read pSrcVec2
	if <>0 delayed goto next_Mask_rep32 with gr5--;
		rep 32 data=[ar2++gr2]	with mask data,ram,afifo;	// Read SrcVec3(Mask)
		rep 32 [ar6++gr6]=afifo;							// Write pDstVec

	<Mask_repN>
	ar4+=gr4;
	delayed goto ar4; 
		pop ar5,gr5;
		pop ar4,gr4;
	<Mask_rep0>
	delayed return;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	VEC_MASK_REP(1);
	VEC_MASK_REP(2);
	VEC_MASK_REP(3);
	VEC_MASK_REP(4);
	VEC_MASK_REP(5);
	VEC_MASK_REP(6);
	VEC_MASK_REP(7);
	VEC_MASK_REP(8);
	VEC_MASK_REP(9);
	VEC_MASK_REP(10);
	VEC_MASK_REP(11);
	VEC_MASK_REP(12);
	VEC_MASK_REP(13);
	VEC_MASK_REP(14);
	VEC_MASK_REP(15);
	VEC_MASK_REP(16);
	VEC_MASK_REP(17);
	VEC_MASK_REP(18);
	VEC_MASK_REP(19);
	VEC_MASK_REP(20);
	VEC_MASK_REP(21);
	VEC_MASK_REP(22);
	VEC_MASK_REP(23);
	VEC_MASK_REP(24);
	VEC_MASK_REP(25);
	VEC_MASK_REP(26);
	VEC_MASK_REP(27);
	VEC_MASK_REP(28);
	VEC_MASK_REP(29);
	VEC_MASK_REP(30);
	VEC_MASK_REP(31);
return;
.wait;





end ".text_nmvcore";
