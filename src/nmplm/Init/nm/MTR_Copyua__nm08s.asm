//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyDsp08.asm   $
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

extern mtr_CopyDspCore:label;

data ".data_nmplm_G"

	vec_Zero:long = 00000000000000000hl;

end ".data_nmplm_G";

begin ".text_nmplm"

//--------------------------------------------------------------------
//! \fn void MTR_Copyua(  nm8s* pSrcMtr, int nSrcStride, int nSrcOffset, nm8s* pDstMtr,  int nDstStride,int nHeight, int nWidth)
//!
//! \perfinclude _MTR_Copyua__FPciiPciii.html
//--------------------------------------------------------------------

global _MTR_Copyua__FPciiPciii:label;
global _void._.8.8MTR_Copyua.1char._.0.9._int.9._int.9._char._.0.9._int.9._int.9._int.2 :label;
<_MTR_Copyua__FPciiPciii>
<_void._.8.8MTR_Copyua.1char._.0.9._int.9._int.9._char._.0.9._int.9._int.9._int.2>
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
	gr4 = [--ar5];	// int		nSrcOffset
	ar6 = [--ar5];	// nm8s*	DstMtr,			// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr6 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows=[0,1,2,3,...]
	gr2 = [--ar5];	// int		nHeight,		// Dst matrix height		:nDstRows=[0,1,2,3,...]
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride =[0,8,16,24..]

	with gr1 = gr4>>3;
	with gr1 = gr1<<1;

	ar1 = ar0		with gr4 = gr4<<29;
	ar0 = ar1 + gr1	with gr4 = gr4>>28;

	vr = [vec_Zero];

	sb	= 02020202h;
	gr7 = 80808080h;

	delayed call mtr_CopyDspCore with gr3>>=3;
		with gr0>>=2;
		with gr6>>=2;


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