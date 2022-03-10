//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyMatrix08.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCopyMatrix08.asm
//! \author ����� ���������
//! \brief  ������� ������������� � ����������� ��� ������.
//!
//! \endif
//!
//------------------------------------------------------------------------



extern mtr_CpyCore_nm64:label;
begin ".text_nmplm"

//--------------------------------------------------------------------
//! \fn void _nmppmCopy_1(  nm1* pSrcMtr, int nSrcStride,  nm1* pDstMtr, int nDstStride, int nHeight, int nWidth)
//!
//! \perfinclude _nmppmCopy_1.html
//--------------------------------------------------------------------
global _void._.8.8nmppmCopy_1.1class._s_nm1._.0.9._int.9._class._s_nm1._.0.9._int.9._int.9._int.2: label;
global _nmppmCopy_1:label;
<_void._.8.8nmppmCopy_1.1class._s_nm1._.0.9._int.9._class._s_nm1._.0.9._int.9._int.9._int.2>
<_nmppmCopy_1>
.branch;

	ar5 = sp-2		with gr7=false;	

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5];	// nm1*	SrcMtr,			// Src matrix				:long Local   [nSrcRows*nSrcStride]
	gr1 = [--ar5];	// int		nSrcStride,	// Src matrix Stride		:nSrcStride in elements
	ar6 = [--ar5];	// nm1*	DstMtr,			// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr4 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows in elements
	gr2 = [--ar5];	// int		nHeight,	// Dst matrix height		:nDstRows in elements
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride in elements =[0,64,128..]



	delayed call mtr_CpyCore_nm64 with gr3>>=6;
		with gr1>>=5;
		with gr4>>=5;


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