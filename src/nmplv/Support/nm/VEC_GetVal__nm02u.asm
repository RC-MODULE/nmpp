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

//! \fn void nmppsGet_2u(nm2u *pVec, int nIndex, uint2b& nVal) 
//!
//! \perfinclude _nmppsGetVal__F4nm2uPiRUi_.html

macro EXTRACT(n)
	delayed return with	gr7<<=n;
		gr7 >>=30;
		[ar5]=gr7;
		nul;
end EXTRACT;

global _nmppsGetVal__F4nm2uPiRUi_:	label;
global _void._.8.8nmppsGetVal_.1class._nm2u._.0.9._int.9._unsigned._int._.6.2 :label;
<_nmppsGetVal__F4nm2uPiRUi_>
<_void._.8.8nmppsGetVal_.1class._nm2u._.0.9._int.9._unsigned._int._.6.2>

.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	ar5 = [--ar5] with gr0 = gr7>>4;
	gr7 = [ar0+=gr0] with gr0=gr7<<28;
	with gr0>>=26;
	gr0++;
	gr0++;
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;
	EXTRACT(30);
	EXTRACT(28);
	EXTRACT(26);
	EXTRACT(24);
	EXTRACT(22);
	EXTRACT(20);
	EXTRACT(18);
	EXTRACT(16);
	EXTRACT(14);
	EXTRACT(12);
	EXTRACT(10);	
	EXTRACT(8);	
	EXTRACT(6);
	EXTRACT(4);
	EXTRACT(2);
	delayed return with	gr7;
		gr7 >>=30;
		[ar5]=gr7;
		nul;	
	
.wait;




end ".text_nmplv";
