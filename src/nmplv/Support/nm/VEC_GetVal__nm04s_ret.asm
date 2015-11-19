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

begin ".text_nmplv"

//! \fn int4b nmppsGet_4s(nm4s *pVec, int nIndex) 
//!
//! \perfinclude _nmppsGet_4s.html

macro EXTRACT(n)
	delayed return with	gr7<<=n;
		gr7 A>>=28;
		nul;
		nul;
end EXTRACT;

global _nmppsGet_4s:	label;
<_nmppsGet_4s>

.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	gr0 = gr7>>3;
	gr7 = [ar0+=gr0] with gr0=gr7<<29;
	with gr0>>=27;
	gr0++;
	gr0++;
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;
	EXTRACT(28);
	EXTRACT(24);
	EXTRACT(20);
	EXTRACT(16);
	EXTRACT(12);	
	EXTRACT(8);	
	EXTRACT(4);
	delayed return with	gr7;
		gr7 A>>=28;
		nul;
		nul;	
	
.wait;




end ".text_nmplv";
