//------------------------------------------------------------------------
//
//  $Workfile:: ClipExt.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   ClipExt.asm
//! \author Сергей Мушкаев
//! \brief  Функции насышения для различных типов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vClip.h"


data ".data_nmplv_L"
end ".data_nmplv_L";

data ".data_nmplv_G"
	TmpLong3:long[3];
end ".data_nmplv_G";

extern vec_ClipExt :label;

begin ".text_nmplv"





/////////////////////////////////////////////////////////////////////////////////
//
//! \fn void  nmppsClipCC_32s(nm32s30b *pSrcVec, int30b nNegThresh, int30b nPosThresh, nm32s30b *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsClipCC__FPiiiPii_.html

global _void._.8.8nmppsClipCC_.1int._.0.9._int.9._int.9._int._.0.9._int.2 :label;
<_void._.8.8nmppsClipCC_.1int._.0.9._int.9._int.9._int._.0.9._int.2>
.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];//nm32s*	pSrcVec,			// Input vector			:long Global[Size/2]
	gr0 = [--ar5];//int		nNegThresh,	// Upper threshold		:=[0...2^30-1]
	gr1 = [--ar5];//int		nPosThresh	// Lower threshold		:=[-2^30....0]
	ar6 = [--ar5];//nm32s*	pDstVec,			// Output vector		:long Local[Size/2]
	gr5 = [--ar5];//int		nSize,		// nSize of vector 32 bit elements. nSize=[64,128,..,64*k]
	
	ar1 = TmpLong3		with gr5>>=	1;
	nb1 = 080000000h;
	gr7 = 040000000h;
	f1cr= 0C0000000h	with gr0 = gr7+gr0;	// d1=1^30+nNegThresh

	[ar1++]=gr0			with gr7--;
	[ar1++]=gr0			with gr2 = gr7-gr1;	// d3=1^30-1-nPosThresh
	ar2 = ar1			with gr1 = gr2+gr0;	// d2=d1+d3=1^31-1+nNegThresh-nPosThresh;	
		
	[ar1++]=gr1			with gr7=false;	
	[ar1++]=gr1			with gr7++;		
	ar3 = ar1			with gr7++;
	[ar1++]=gr2			with gr0=gr7;		// 2
	[ar1++]=gr2			with gr6=gr7;		// 2
	wtw;
	// [ar1]= 1^30+nNegThresh
	// [ar2]= 1^31-1+nNegThresh-nPosThresh
	// [ar3]= 1^30-1-nPosThresh
	delayed call vec_ClipExt;
		ar1 = TmpLong3;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";

