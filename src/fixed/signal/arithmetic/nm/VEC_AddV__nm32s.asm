//------------------------------------------------------------------------
//
//  $Workfile:: Add.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Add.Asm
//! \author ������ �������
//! \brief  ������� ������������ ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"



extern vec_Add:label;
begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsAdd (nm32s *pSrcVec1, nm32s *pSrcVec2, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAdd_32s.html


global _nmppsAdd_32s:label;
<_nmppsAdd_32s>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++;
	push ar5,gr5 with gr0++;		// gr0=2 
	push ar6,gr6 with gr1=gr0;
	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 16-bit elements
	
	nb1 = 80000000h with gr5>>=1;	// nSize in 32-bit words
	delayed call vec_Add with gr1=gr0;
		wtw;						
		gr6=gr0;					// gr6=2
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;





end ".text_nmplv";
