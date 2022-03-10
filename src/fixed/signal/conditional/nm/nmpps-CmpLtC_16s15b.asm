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
//! \fn void nmppsCmpLtC_16s15b (nm16s *pSrcVec, int16b nVal, nm16s *pDstVec, int nSize) 
//!
//! \perfinclude nmppsCmpLtC_16s15b.html

global _nmppsCmpLtC_16s15b:label;
<_nmppsCmpLtC_16s15b>
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

	
	nb1 = 80008000h with gr5>>=2;	// nSize in 64-bit longs
	wtw;
	gr0 <<=16;
	
	gr7 = gr0 >> 16;
	gr1 = gr7 or gr0;
	ar1  = gr1;
	ar5 = ar7;
	push ar1,gr1;
	ar1 = ar5;
	gr0 = 2;
	f1cr = 0FFFEFFFEh;
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
