//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyAtoU08.asm  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCopyDsp08.asm
//! \author Павел Лукашевич
//! \brief  Функции инициализации и копирования для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------


import from macros.mlb;
extern mtr_CopyDspCore:label;
extern mtr_CopyAtoU_Core:label;

data ".data_nmplm_G"

	vec_Zero:long = 00000000000000000hl;
	 nDstOffset:long = 00000000000000000hl;

end ".data_nmplm_G";

begin ".text_nmplm"


//--------------------------------------------------------------------
//! \fn void nmppmCopyau_8s(  nm8s* pSrcMtr, int nSrcStride, nm8s* pDstMtr,  int nDstStride, int nDstOffset, int nHeight, int nWidth)
//!
//! \perfinclude _nmppmCopyau_8s.html
//--------------------------------------------------------------------

global _nmppmCopyau_8s:label;
global _nmppmCopyau_8u:label;
<_nmppmCopyau_8s>
<_nmppmCopyau_8u>
.branch;

	ar5 = sp-2;	

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5];	// nm8s*	SrcMtr,			// Src matrix				:long Local   [nSrcRows*nSrcStride]
	gr0 = [--ar5];	// int		nSrcStride,	// Src matrix Stride		:nSrcStride=[0,1,2,3....]
	ar6 = [--ar5];	// nm8s*	DstMtr,			// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr6 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows=[0,1,2,3,...]
	gr4 = [--ar5];	// int		nDstOffset
	gr2 = [--ar5];	// int		nHeight,		// Dst matrix height		:nDstRows=[0,1,2,3,...]
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride =[0,8,16,24..]

	with gr5 = gr4>>3;
	with gr5 = gr5<<1;

	ar5 = ar6		with gr4 = gr4<<29;//Dst address modification
	ar6 = ar5 + gr5	with gr4 = gr4>>28;

	vr = [vec_Zero];
	[nDstOffset] = gr4;

	sb	= 02020202h;
	gr7 = 80808080h;

	//Border Processing
	delayed call mtr_CopyAtoU_Core with gr3>>=3;
		with gr0>>=2;
		with gr6>>=2;

	//Other Data Processing
	ar6 += 2 with gr3--;
	gr4 = [nDstOffset];
	gr1 = 8 with gr4>>=1;

	ar1 = ar0 with gr4 = gr1 - gr4;
	with gr1 = gr4>>3;
	
	delayed call mtr_CopyDspCore with gr1 = gr1<<1;
		ar0 = ar1 + gr1 with gr4 = gr4<<29;
		with gr4 = gr4>>28;
		

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

return;
.wait;
end ".text_nmplm";