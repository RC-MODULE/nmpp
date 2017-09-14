//------------------------------------------------------------------------
//
//  $Workfile:: Copy.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Copy.asm
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vCopy.h"

extern vec_data:label;


begin ".text_nmplv"
 
		
//! \fn void nmppsCopy_2s(nm2s* pSrcVec, nm2s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCopy_2s.html

global _nmppsCopy_2s:label;
<_nmppsCopy_2s>
.branch;
    ar5 = sp - 2	with gr7=gr5;
	push ar0,gr0	with gr0=false;
	push ar6,gr6	with gr0++;
    ar0 = [--ar5]	with gr0++;		// pSrcVec
	ar6 = [--ar5]	with gr6=gr0;	// pDstVec
	delayed call vec_data;
		gr5 = [--ar5];				// nSize
		gr5>>=5;
	pop ar6,gr6;
	pop ar0,gr0		with gr5=gr7;
	return;
.wait;


end ".text_nmplv";