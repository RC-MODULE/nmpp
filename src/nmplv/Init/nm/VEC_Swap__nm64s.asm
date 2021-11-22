//------------------------------------------------------------------------
//
//  $Workfile:: Swap.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Swap.asm
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_Swap:label;

/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSwap_64s(nm64s *pSrcVec1, nm64s *pSrcVec2, int nSize) 
//!
//! \perfinclude _nmppsSwap_64s.html


global _nmppsSwap_64s:label;
<_nmppsSwap_64s>

.branch;

	ar5 = sp-2		with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar4,gr4	with gr0=gr7;
	push ar5,gr5	with gr1=gr7;
	push ar6,gr6;

	ar0=[--ar5];	//	nm64s*		pSrcVec1,	// input buffer		:long Long[nSize]
	ar1=[--ar5];	//	nm64s*		pSrcVec2,	// output buffer	:long Long[nSize]	
	gr5=[--ar5];	//		int			nSize	// buffer size in 8-bit elemetns	:[0,8,16,24...]
	
	delayed call vec_Swap;
		ar4=ar1	with gr4=gr1;
		ar6=ar0 with gr6=gr0;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv";
