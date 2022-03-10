//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V32N32.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V32N32.asm
//! \author ������ �������
//! \brief  ������� ��������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------
import from macros.mlb;

extern vec_vsum_data_0	:label;
extern vec_vsum_data_vr	:label;
extern vec_MulVN_AddVN	:label;
extern _nmppsTmpBuffer16_G_:long[16];

begin ".text_nmplv"




/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMulC_AddV_AddC (nm32s *pSrcVec1, int nMulVal, nm32s *pSrcVec2, int nAddVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC_AddV_AddC_32s.html

global _nmppsMulC_AddV_AddC_32s:label;
global _nmppsMulC_AddV_AddC32s:label;
<_nmppsMulC_AddV_AddC_32s>
<_nmppsMulC_AddV_AddC32s>

.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];			// pSrcVec1
	gr5 = [--ar5];			// MulN 
	gr7 = false;
	//-- WFIFO init ---------------------------
	ar6 = _nmppsTmpBuffer16_G_;
	[ar6++] = gr5;
	[ar6++] = gr7;
	[ar6++] = gr7;
	[ar6++] = gr5;
	ar6-=4;
	gr7 = 80000000h;
	sb  = 2;
	nb1 = gr7;
	rep 2 wfifo=[ar6++],ftw;
	//-----------------------------------------
	ar1 = [--ar5];			// pSrcVec2
 	gr5 = [--ar5];			// AddN
	vr	= gr5;
	ar6 = [--ar5];			// pDstVec
	gr5 = [--ar5];			// nSize
	gr0 = 2		with gr5 >>= 1;
	delayed call vec_MulVN_AddVN;
		gr6 = gr0 with gr1=gr0;	
		wtw;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
