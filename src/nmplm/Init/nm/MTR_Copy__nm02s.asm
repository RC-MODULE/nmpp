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
// Copying long submatrix from 4 bit odd position of source matrix
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void nmppmCopy_2u(  nm2s* pSrcMtr, int nSrcStride,  nm2s* pDstMtr, int nDstStride, int nHeight, int nWidth)
//!
//! \perfinclude _nmppmCopy_2u.html
//--------------------------------------------------------------------

global _nmppmCopy_2u:label;
global _nmppmCopy_2s:label;
<_nmppmCopy_2s>
<_nmppmCopy_2u>
.branch;

	ar5 = sp-2		with gr7=false;	

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5];	// nm4s*	SrcMtr,		// Src matrix				:long Local   [nSrcRows*nSrcStride]
	gr1 = [--ar5];	// int		nSrcStride,	// Src matrix Stride		:nSrcStride in elements
	ar6 = [--ar5];	// nm4s*	DstMtr,		// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr4 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows in elements
	gr2 = [--ar5];	// int		nHeight,	// Dst matrix height		:nDstRows in elements
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride in elements =[0,16,32..]



	delayed call mtr_CpyCore_nm64 with gr3>>=5;
		with gr1>>=4;
		with gr4>>=4;


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