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
//! \fn void VEC_Not(nm64u* pSrcVec, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _VEC_Not__FPUlPUli.html

global _VEC_Not__FPUlPUli:	label;
global _void._.8.8VEC_Not.1unsigned._long._.0.9._unsigned._long._.0.9._int.2 :label;
<_VEC_Not__FPUlPUli>
<_void._.8.8VEC_Not.1unsigned._long._.0.9._unsigned._long._.0.9._int.2>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar5,gr5	with gr0=gr7+1;
	push ar6,gr6	with gr1=gr0;

	ar0 = [--ar5];		//	nm64*		pSrcVec,		// Input Buffer					:long Local[nSize]
	delayed call vec_not_data with gr6=gr0;
		ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;
end ".text_nmplv";
