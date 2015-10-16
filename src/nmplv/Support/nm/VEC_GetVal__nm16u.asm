//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   CharShortAccess.asm
//! \author Сергей Мушкаев
//! \brief  Функции доступа для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vConvert.h"

/////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_GetVal(nm16u* pVec, int nIndex, uint16b &nVal)
//!
//! \perfinclude _VEC_GetVal__FPUsiRUi.html
begin ".text_nmplv"

global _VEC_GetVal__FPUsiRUi:	label;
global _void._.8.8VEC_GetVal.1unsigned._short._.0.9._int.9._unsigned._int._.6.2: label;
<_VEC_GetVal__FPUsiRUi>
<_void._.8.8VEC_GetVal.1unsigned._short._.0.9._int.9._unsigned._int._.6.2>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	ar5 = [--ar5] with gr0 = gr7>>1;
	gr7 = [ar0+=gr0] with gr0=gr7<<31;
	with gr0>>=29;
	gr0++;
	gr0++;

	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;

	delayed return with	gr7<<=16;
		gr7 >>=16;
		[ar5]=gr7;
		nul;
	delayed return with	gr7 >>=16;
		[ar5]=gr7;
		nul;
		nul;
.wait;




end ".text_nmplv";
