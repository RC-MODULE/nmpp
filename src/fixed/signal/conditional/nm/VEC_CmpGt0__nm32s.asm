//------------------------------------------------------------------------
//
//  $Workfile:: Activate.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   Activate.asm
//! \author Иван Жиленков
//! \brief  Пороговые функции над векторами.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_CmpGtC:label;
begin ".text_nmplv"

///////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsCmpGt0_32s(nm32s* pSrcVec, nm32s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCmpGt0_32s.html

global _nmppsCmpGt0_32s:label;
<_nmppsCmpGt0_32s>

	ar5 = ar7 - 2	with gr7 = false;
	push ar0,gr0	with gr7++;
	push ar1,gr1;
	push ar5,gr5	with gr7++;
	push ar6,gr6;
	ar0 = [--ar5]	with gr0 = gr7;	// pSrcVec,		
	ar6 = [--ar5]	with gr6 = gr7;	// pDstVec,		
	gr5 = [--ar5];					// nSize
	gr7 = 80000000h;
	nb1 = gr7;
	f1cr = gr7;
	wtw;
	
	ar5 = ar7	with gr1 = false;
	ar1 = gr1;
	push ar1,gr1;
	ar1 = ar5;
	
	call vec_CmpGtC	with gr5>>=1;
	
	pop ar1,gr1;	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
