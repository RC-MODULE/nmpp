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

//! \fn uint8u nmppsGet_8u(nm8u *pVec, int nIndex) 
//!
//! \perfinclude _nmppsGetVal__FPUci_.html

global _nmppsGetVal__FPUci_:	label;
global _unsigned._int._.8.8nmppsGetVal_.1unsigned._char._.0.9._int.2 :label;
<_nmppsGetVal__FPUci_>
<_unsigned._int._.8.8nmppsGetVal_.1unsigned._char._.0.9._int.2>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	gr0 = gr7>>2;
	gr7 = [ar0+=gr0] with gr0=gr7<<30;
	with gr0>>=28;
	gr0++;
	gr0++;
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;

	delayed return with	gr7<<=24;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7<<=16;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7<<=8;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7 >>=24;
		nul;
		nul;
		nul;
.wait;




end ".text_nmplv";
