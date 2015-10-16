//------------------------------------------------------------------------
//
//  $Workfile:: Math_ClipExt.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_ClipExt.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vClip.h"



begin ".text_nmvcore"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Register interface function of clipping of vectors with dc offset
// Bit capacity of vector and activate parameters
// are determined by current states of nb1 and f1cr registers before the function call.

macro VEC_CLIP_EXT_REP(N)
		rep N ram  = [ar1];
		rep N data = [ar0++gr0] with  data-ram;
	delayed return;
		rep N data = [ar2]		with activate afifo+data;
		rep N data = [ar3]		with activate afifo-data;
		rep N [ar6++gr6] = afifo;
	nul;
	nul;
end VEC_CLIP_EXT_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_ClipExt(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg ar2, nmreg ar3, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_ClipExt:label;
<vec_ClipExt>	
.branch;
	ClipExt_rep0:label;
	push ar4,gr4 with gr4=gr5<<27;
	push ar5,gr5 with gr5>>=5;
	if =0 delayed goto ClipExt_repN with gr4>>=24;
		ar4 = ClipExt_rep0 with gr5--;
	rep 32 ram=[ar1];
	<next_ClipExt_rep32>
		rep 32 data = [ar0++gr0]	with  data-ram;
		rep 32 data = [ar2]			with activate afifo+data;
	if <>0 delayed goto next_ClipExt_rep32 with gr5--;
		rep 32 data = [ar3]			with activate afifo-data;
		rep 32 [ar6++gr6] = afifo;
	
	<ClipExt_repN>
	ar4+=gr4;
	delayed goto ar4; 
		pop ar5,gr5;
		pop ar4,gr4;
	<ClipExt_rep0>
	delayed return; 
		nul;
		nul;
		nul;
	nul;
	nul;
	nul;
	nul;
	VEC_CLIP_EXT_REP(1);
	VEC_CLIP_EXT_REP(2);
	VEC_CLIP_EXT_REP(3);
	VEC_CLIP_EXT_REP(4);
	VEC_CLIP_EXT_REP(5);
	VEC_CLIP_EXT_REP(6);
	VEC_CLIP_EXT_REP(7);
	VEC_CLIP_EXT_REP(8);
	VEC_CLIP_EXT_REP(9);
	VEC_CLIP_EXT_REP(10);
	VEC_CLIP_EXT_REP(11);
	VEC_CLIP_EXT_REP(12);
	VEC_CLIP_EXT_REP(13);
	VEC_CLIP_EXT_REP(14);
	VEC_CLIP_EXT_REP(15);
	VEC_CLIP_EXT_REP(16);
	VEC_CLIP_EXT_REP(17);
	VEC_CLIP_EXT_REP(18);
	VEC_CLIP_EXT_REP(19);
	VEC_CLIP_EXT_REP(20);
	VEC_CLIP_EXT_REP(21);
	VEC_CLIP_EXT_REP(22);
	VEC_CLIP_EXT_REP(23);
	VEC_CLIP_EXT_REP(24);
	VEC_CLIP_EXT_REP(25);
	VEC_CLIP_EXT_REP(26);
	VEC_CLIP_EXT_REP(27);
	VEC_CLIP_EXT_REP(28);
	VEC_CLIP_EXT_REP(29);
	VEC_CLIP_EXT_REP(30);
	VEC_CLIP_EXT_REP(31);
.wait;




end ".text_nmvcore";

