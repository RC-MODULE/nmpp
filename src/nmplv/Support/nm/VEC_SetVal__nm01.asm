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

macro SETVAL0()
	gr6 = not(01h);
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL0;

macro SETVAL(sh)
	gr6 = not(01h<<sh) with gr1 <<= sh;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL;

/////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsPut_1 (nm1 *pVec, int nIndex, int1b Val) 
//!
//! \perfinclude _nmppsPut_1.html




global nmppsPut_1:	label;
<nmppsPut_1> 

.branch;
	ar5 = ar7 - 5;
	push ar1,gr1;
	push ar6,gr6;
	gr1 = [ar5++];						// char Element
	gr7 = [ar5++];						// nIndex				
					 with gr6 = gr7>>5;
	ar6 = [ar5++]	 with gr7 <<=27;	// pVec				
	gr7 = [ar6+=gr6] with gr6 = gr7>>24;// Old int  Element
	ar5 = ar6		 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		with gr1<<=31;
		with gr1>>=31;
		nul;

	SETVAL0();
	SETVAL(1);
	SETVAL(2);
	SETVAL(3);
	SETVAL(4);
	SETVAL(5);
	SETVAL(6);
	SETVAL(7);
	SETVAL(8);
	SETVAL(9);
	SETVAL(10);
	SETVAL(11);
	SETVAL(12);
	SETVAL(13);
	SETVAL(14);
	SETVAL(15);
	SETVAL(16);
	SETVAL(17);
	SETVAL(18);
	SETVAL(19);
	SETVAL(20);
	SETVAL(21);
	SETVAL(22);
	SETVAL(23);
	SETVAL(24);
	SETVAL(25);
	SETVAL(26);
	SETVAL(27);
	SETVAL(28);
	SETVAL(29);
	SETVAL(30);
	SETVAL(31);
	
.wait;




end ".text_nmplv";
