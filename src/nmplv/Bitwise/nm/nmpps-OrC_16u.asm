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



extern vec_data_or_ram:label;
begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsOrC_16u(nm16u* pSrcVec, uint16b nVal, nm16u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsOrC_16u.html


global _nmppsOrC_16u:label;

<_nmppsOrC_16u>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	;

	ar0 = [--ar5];		//	nm64*		pSrcVec,		// Input Buffer					:long Local[nSize]
	gr6 = [--ar5];
	gr7 = gr6<<16;
	gr6 = gr7>>16;
	gr6 = gr6 or gr7;
	ar6 = gr6;
	ar1 = ar7;
	
	push ar6,gr6 	with gr6=gr0;
	ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
	delayed call vec_data_or_ram;
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
		with gr5>>=2;
	pop ar6,gr6;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;
end ".text_nmplv";
