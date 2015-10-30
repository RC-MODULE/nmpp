//------------------------------------------------------------------------
//
//  $Workfile:: And.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   And.asm
//! \author Сергей Мушкаев
//! \brief  Логические функции над векторами.
//!
//! \endif
//!
//------------------------------------------------------------------------



extern vec_data_and_ram:label;
begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsAndC_64u(nm64u* pSrcVec, nm64u* pnVal, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsAndC__FPUlPUlPUli_.html


global _void._.8.8nmppsAndC_.1unsigned._long._.0.9._unsigned._long._.0.9._unsigned._long._.0.9._int.2 :label;

<_void._.8.8nmppsAndC_.1unsigned._long._.0.9._unsigned._long._.0.9._unsigned._long._.0.9._int.2>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	with gr6=gr7;

	ar0 = [--ar5];		//	nm64*		pSrcVec,		// Input Buffer					:long Local[nSize]
	ar1 = [--ar5];		//	nm64*		SrcN,		// Input Buffer					:long Local[1]
	delayed call vec_data_and_ram;
		ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;
end ".text_nmplv";
