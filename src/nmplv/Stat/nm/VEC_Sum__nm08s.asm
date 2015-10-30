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

extern _VEC_TmpBuffer16_G:long;
extern _VEC_TBL_One_G:long;


extern vec_vsum_data_afifo:label;
begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSum (nm8s *pSrcVec, int nSize, int32b *pnRes) 
//!
//! \perfinclude _nmppsSum__FPciPi.html


global _void._.8.8nmppsSum.1char._.0.9._int.9._int._.0.2 :label;

<_void._.8.8nmppsSum.1char._.0.9._int.9._int._.0.2>
.branch;
	ar5 = sp - 2;
	push ar0,gr0 with gr0=false;
	nb1 = gr0;
	ar0 = _VEC_TBL_One_G;
	sb  = 02020202h;
	rep 8 wfifo=[ar0],ftw;
				 
	push ar5,gr5 with gr0++;		
	push ar6,gr6 with gr0++;		// gr0=2 
	ar0 = [--ar5];					// pSrcVec
	gr5 = [--ar5];					// nSize in 8-bit elements
	ar6 = _VEC_TmpBuffer16_G with gr5>>=3;	// nSize in 64-bit words

	delayed call vec_vsum_data_afifo;
		nul;
		wtw;						

	gr7=[_VEC_TmpBuffer16_G];
	ar6=[--ar5];
	[ar6]=gr7;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv";
