//------------------------------------------------------------------------
//
//  $Workfile:: Neg_8s $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Neg_8s.Asm
//! \author ������ �������
//! \brief  ��������� ����� ��������� ������� �� ���������������.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"


extern vec_0_sub_data:label;

begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsNeg (nm32s *pSrcVec, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsNeg_32s.html

global _nmppsNeg_32s:label;
<_nmppsNeg_32s>
.branch;
	ar5 = sp - 2	with gr7=gr5;
	push ar0,gr0	with gr0=false;
	push ar6,gr6	with gr0++;
	
	
	nb1 = 80000000h	with gr0++;
	
	ar0 = [--ar5]with gr6=gr0;	// pSrcVec
	ar6 = [--ar5];				// pDstVec
	gr5 = [--ar5];	// nSize
						
	delayed call  vec_0_sub_data with gr5>>=1;	// nSize in 64-bit longs
		wtw;
		nul;
	
	pop ar6,gr6;
	pop ar0,gr0		with gr5=gr7;
	return;
.wait;




end ".text_nmplv";
