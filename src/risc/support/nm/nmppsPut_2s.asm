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

//! \fn void nmppsPut_2s(nm2s *pVec, int nIndex, int2b Val) 
//!
//! \perfinclude _nmppsPut_2s.html

macro SETVAL0()
	gr6 = not(03h<<0);
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL0;

macro SETVAL(sh)
	gr6 = not(03h<<sh) with gr1<<=sh;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL;

global _nmppsPut_2s:label;
<_nmppsPut_2s> 
.branch;
	ar5 = ar7 - 5;
	push ar1,gr1;
	push ar6,gr6;
	gr1 = [ar5++];						// char Element
	gr7 = [ar5++];						// nIndex				
					 with gr6 = gr7>>4;
	ar6 = [ar5++]	 with gr7 <<=28;	// pVec				
	gr7 = [ar6+=gr6] with gr6 = gr7>>25;// Old int  Element
	ar5 = ar6		 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		with gr1<<=30;
		with gr1>>=30;
		nul;

	SETVAL0();
	SETVAL(2);
	SETVAL(4);
	SETVAL(6);
	SETVAL(8);
	SETVAL(10);
	SETVAL(12);
	SETVAL(14);
	SETVAL(16);
	SETVAL(18);
	SETVAL(20);
	SETVAL(22);
	SETVAL(24);
	SETVAL(26);
	SETVAL(28);
	SETVAL(30);
.wait;




end ".text_nmplv";
