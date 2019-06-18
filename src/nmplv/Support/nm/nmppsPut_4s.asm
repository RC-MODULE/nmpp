//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   CharShortAccess.asm
//! \author ������ �������
//! \brief  ������� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

begin ".text_nmplv"

macro SETVAL0()
	gr6 = not(0Fh<<0);
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL0;

macro SETVAL(sh)
	gr6 = not(0Fh<<sh) with gr1 <<=sh;
	pop ar6,gr6 with gr7 = gr7 and gr6;
	pop ar1,gr1 with gr7 = gr7 or  gr1;
	delayed return;
		[ar5]=gr7;
		nul;
		nul;
end SETVAL;

/////////////////////////////////////////////////////////////////////////////////


//! \fn void nmppsPut_4s(nm4s *pVec, int nIndex, int4b Val) 
//!
//! \perfinclude _nmppsPut_4s.html



global _nmppsPut_4s:	label;
global _nmppsPut_4u:	label;
<_nmppsPut_4s> 
<_nmppsPut_4u> 
.branch;
	ar5 = ar7 - 5;
	push ar1,gr1;
	push ar6,gr6;
	gr1 = [ar5++];						// char Element
	gr7 = [ar5++];						// nIndex				
					 with gr6 = gr7>>3;
	ar6 = [ar5++]	 with gr7 <<=29;	// pVec				
	gr7 = [ar6+=gr6] with gr6 = gr7>>26;// Old int  Element
	ar5 = ar6		 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		with gr1<<=28;
		with gr1>>=28;
		nul;

	SETVAL0();
	SETVAL(4);
	SETVAL(8);
	SETVAL(12);
	SETVAL(16);
	SETVAL(20);
	SETVAL(24);
	SETVAL(28);
.wait;




end ".text_nmplv";
