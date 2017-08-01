//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyMatrix08.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCopyMatrix08.asm
//! \author Павел Лукашевич
//! \brief  Функции инициализации и копирования для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------



extern mtr_CpyCore_nm64:label;
begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////
// Copying long submatrix from 8 bit odd position of source matrix
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void MTR_Copy(  nm8s* pSrcMtr, int nSrcStride,  nm8s* pDstMtr, int nDstStride, int nHeight, int nWidth)
//!
//! \perfinclude _MTR_Copy__FPciPciii.html
//--------------------------------------------------------------------

global _MTR_Copy__FPciPciii:label;
//global _void._.8.8MTR_Copy.1char._.0.9._int.9._char._.0.9._int.9._int.9._int.2 :label;
global _void._.8.8MTR_Copy_8s.1signed._char._.0.9._int.9._signed._char._.0.9._int.9._int.9._int.2 :label;
<_MTR_Copy__FPciPciii>
//<_void._.8.8MTR_Copy.1char._.0.9._int.9._char._.0.9._int.9._int.9._int.2>
<_void._.8.8MTR_Copy_8s.1signed._char._.0.9._int.9._signed._char._.0.9._int.9._int.9._int.2>
.branch;

	ar5 = sp-2		with gr7=false;	

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5];	// nm8s*	SrcMtr,			// Src matrix				:long Local   [nSrcRows*nSrcStride]
	gr1 = [--ar5];	// int		nSrcStride,	// Src matrix Stride		:nSrcStride=[0,1,2,3....]
	ar6 = [--ar5];	// nm8s*	DstMtr,			// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr4 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows=[0,1,2,3,...]
	gr2 = [--ar5];	// int		nHeight,		// Dst matrix height		:nDstRows=[0,1,2,3,...]
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride =[0,8,16,24..]



	delayed call mtr_CpyCore_nm64 with gr3>>=3;
		with gr1>>=2;
		with gr4>>=2;


	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

return;
/////////////////////////////////////////////////////////////////////////////////
.wait;
end ".text_nmplm";