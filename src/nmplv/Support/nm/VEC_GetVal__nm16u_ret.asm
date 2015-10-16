//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
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

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////

//! \fn uint16u VEC_GetVal (nm16u *pVec, int nIndex) 
//!
//! \perfinclude _VEC_GetVal__FPUsi.html

global _VEC_GetVal__FPUsi:	label;
global _unsigned._int._.8.8VEC_GetVal.1unsigned._short._.0.9._int.2 :label;
<_VEC_GetVal__FPUsi>
<_unsigned._int._.8.8VEC_GetVal.1unsigned._short._.0.9._int.2>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	gr0 = gr7>>1;
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
		nul;
		nul;
	delayed return with	gr7 >>=16;
		nul;
		nul;
		nul;
.wait;



end ".text_nmplv";
