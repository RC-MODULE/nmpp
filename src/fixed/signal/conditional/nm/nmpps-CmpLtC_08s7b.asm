//------------------------------------------------------------------------
//
//  $Workfile:: AddVN.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   AddVN.asm
//! \author ������ �������
//! \brief  ������� ������������ ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_CmpLtC:label;

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsCmpLtC_8s7b (nm8s7b *pSrcVec, int8b nVal, nm8s7b *pDstVec, int nSize) 
//!
//! \perfinclude nmppsCmpLtC_8s7b.html

global _nmppsCmpLtC_8s7b:label;
<_nmppsCmpLtC_8s7b>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff
	gr0 = [--ar5];	// nVal
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	
	nb1 = 80808080h with gr5>>=3;	// nSize in 64-bit longs
	wtw;
	gr0 <<=24;
	gr0 >>=24;
	gr7 = gr0 << 8;
	gr7 = gr7 or gr0;
	gr0 = gr7 << 16;
	gr1 = gr7 or gr0;
	ar1 = gr1;
	ar5 = ar7;
	push ar1,gr1;
	ar1 = ar5;
	gr0 = 2;
	f1cr = 0FEFEFEFEh;
	delayed call vec_CmpLtC;
		gr6 = 2;
	
	pop ar1,gr1; 
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;

return with gr7=false;
.wait;



end ".text_nmplv";
