//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyMatrix64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCopyMatrix64.asm
//! \author Павел Лукашевич
//! \brief  Функции инициализации и копирования для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vClip.h"


extern mtr_CpyCore_nm64:label;
begin ".text_nmplm"

//--------------------------------------------------------------------
//! \fn void nmppmCopy_64s( nm64s* pSrcMtr, int nSrcStride, nm64s* pDstMtr, int nDstStride, int nHeight, int nWidth)
//!
//! \perfinclude _nmppmCopy_64s.html
//--------------------------------------------------------------------

global _nmppmCopy_64u:label;
global _nmppmCopy_64s:label;
<_nmppmCopy_64s>
<_nmppmCopy_64u>
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


	delayed call mtr_CpyCore_nm64 with gr3;
		with gr1<<=1;
		with gr4<<=1;

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