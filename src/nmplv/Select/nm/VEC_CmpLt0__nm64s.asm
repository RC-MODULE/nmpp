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
//! \author Сергей Мушкаев
//! \brief  Пороговые функции над векторами.
//!
//! \endif
//!
//------------------------------------------------------------------------
    
data ".data_nmplv_L"
	i64la:	long = 8000000000000000hl;
end ".data_nmplv_L";

extern vec_activate_data:label;
begin ".text_nmplv"
///////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCmpLt0_64s(nm64s* pSrcVec, nm64s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCmpLt0_64s.html

global _nmppsCmpLt0_64s:	label;
global _nmppsCmpLt0_64s:label;
<_nmppsCmpLt0_64s>
	ar5 = ar7 - 2	with gr7 = false;
	push ar0,gr0	with gr7++;
	push ar5,gr5	with gr7++;
	push ar6,gr6;
	ar0 = [--ar5]	with gr0 = gr7;	// pSrcVec,		
	ar6 = [--ar5]	with gr6 = gr7;	// pDstVec,		
	gr5 = [--ar5];					// nSize		
	delayed call vec_activate_data;
		f1cr = [i64la]	with gr7++;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
