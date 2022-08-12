//------------------------------------------------------------------------
//
//  $Workfile:: Abs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Abs.Asm
//! \author Сергей Мушкаев
//! \brief  Абсолютное значение элементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"

extern _VEC_TBL_Diagonal_FFFFh_G:long;
extern vec_Abs:label;

begin ".text_nmplv"


//! \fn void nmppsAbs_16s(nm16s *pSrcVec, nm16s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAbs_16s.html

global _nmppsAbs_16s:label;
<_nmppsAbs_16s>
.branch;
	ar5 = sp - 2	with gr7=gr5;
	push ar0,gr0	with gr0=false;
	push ar6,gr6	with gr0++;
	
	sb	= 00020002h	with gr0++;
	nb1 = 80008000h	with gr6=gr0;
	ar6 = _VEC_TBL_Diagonal_FFFFh_G;
	rep 4 wfifo=[ar6++],ftw;
	
	ar0 = [--ar5];	// pSrcVec
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize
	
	f1cr= 80008000h;   				
	delayed call  vec_Abs with gr5>>=2;	// nSize in 64-bit longs
		wtw;	
		nul;

	pop ar6,gr6;
	pop ar0,gr0		with gr5=gr7;
	return;
.wait;


end ".text_nmplv";
