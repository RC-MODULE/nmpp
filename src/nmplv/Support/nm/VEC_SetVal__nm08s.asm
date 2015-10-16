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

//! \fn void VEC_SetVal (nm8s *pVec, int nIndex, int8b Val) 
//!
//! \perfinclude _VEC_SetVal__FPcii.html

global _VEC_SetVal__FPcii:	label;
global _void._.8.8VEC_SetVal.1char._.0.9._int.9._int.2 :label;
<_VEC_SetVal__FPcii> 
<_void._.8.8VEC_SetVal.1char._.0.9._int.9._int.2>
.branch;
	ar5 = ar7 - 5;
	push ar1,gr1;
	push ar6,gr6;
	gr1 = [ar5++];						// char Element
	gr7 = [ar5++];						// nIndex				
					 with gr6 = gr7>>2;
	ar6 = [ar5++]	 with gr7 <<=30;	// pVec				
	gr7 = [ar6+=gr6] with gr6 = gr7>>27;// Old int  Element
	ar5 = ar6		 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		with gr1<<=24;
		with gr1>>=24;
		nul;

	//////////////////////////////////
	gr6 = 0FFFFFF00h;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
	
	//////////////////////////////////
	gr6 = 0FFFF00FFh with gr1 <<=8;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
	
	//////////////////////////////////
	gr6 = 0FF00FFFFh with gr1 <<=16;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
	
	//////////////////////////////////
	gr6 = 000FFFFFFh with gr1 <<=24;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
.wait;




end ".text_nmplv";
