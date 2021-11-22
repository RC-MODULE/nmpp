//------------------------------------------------------------------------
//
//  $Workfile:: Not.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Not.asm
//! \author Сергей Мушкаев
//! \brief  Логические функции над векторами.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_not_data:label;
begin ".text_nmplv"
///////////////////////////////////////////////////////////
//! \fn void nmppsNot_32u(nm64u* pSrcVec, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsNot_32u.html

global _nmppsNot_32u:label;
<_nmppsNot_32u>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar5,gr5	with gr0=gr7+1;
	push ar6,gr6;

	ar0 = [--ar5];		//	nm64*		pSrcVec,		// Input Buffer					:long Local[nSize]
	ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
	delayed call vec_not_data with gr6=gr0;
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
		with gr5>>=1;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;
end ".text_nmplv";
