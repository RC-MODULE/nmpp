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

//! \fn void nmppsSetInt_16s(nm16s *pVec, int nIndex, int16b Val) 
//!
//! \perfinclude _nmppsSetVal__FPSsii_.html

global _nmppsSetVal__FPSsii_:	label;
global _void._.8.8nmppsSetVal_.1short._.0.9._int.9._int.2 :label;
<_nmppsSetVal__FPSsii_>
<_void._.8.8nmppsSetVal_.1short._.0.9._int.9._int.2>
.branch;
	ar5 = ar7 - 5;
	push ar1,gr1;
	push ar6,gr6;
	gr1 = [ar5++];						// short Element
	gr7 = [ar5++];						// nIndex				
					 with gr6 = gr7>>1;	
	ar6 = [ar5++]	 with gr7 <<=31;	// pVec				
	gr7 = [ar6+=gr6] with gr6 =gr7>>28;	// Old int  Element
	ar5 = ar6		 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		with gr1<<=16;
		with gr1>>=16;
		nul;

	//////////////////////////////////
	gr6 = 0FFFF0000h;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
	
	//////////////////////////////////
	gr6 = 0000FFFFh with gr1 <<=16;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
	
.wait;



end ".text_nmplv";
