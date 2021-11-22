//------------------------------------------------------------------------
//
//  $Workfile:: Sum.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   Sum.Asm
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"
extern _VEC_TBL_One_G:long;


extern vec_vsum_data_afifo:label;
begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSum (nm32s *pSrcVec, int nSize, int64b *pnRes) 
//!
//! \perfinclude _nmppsSum_32s.html


global _nmppsSum_32s:label;

<_nmppsSum_32s>
.branch;
	ar5 = sp - 2;
	push ar0,gr0 with gr0=false;
	nb1 = gr0;
	ar0 = _VEC_TBL_One_G;
	sb  = 00000002h;
	rep 2 wfifo=[ar0],ftw;
				 
	push ar5,gr5 with gr0++;		
	push ar6,gr6 with gr0++;		// gr0=2 
	ar0 = [--ar5];					// pSrcVec
	gr5 = [--ar5];					// nSize in 32-bit elements
	ar6 = [--ar5]	with gr5>>=1;	// nSize in 64-bit words

	delayed call vec_vsum_data_afifo;
		gr7=ar6;
		wtw;						

	pop ar6,gr6;
	pop ar5,gr5 with gr6=gr7+1;
	pop ar0,gr0;
	return;

.wait;







end ".text_nmplv";
