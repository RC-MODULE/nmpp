//------------------------------------------------------------------------
//
//  $Workfile:: Mask.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Mask.asm
//! \author ������ �������
//! \brief  ���������� ������� ��� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------


//********** Local  ********************
data ".data_nmplv_L"
end ".data_nmplv_L";
//********** Global ********************
data ".data_nmplv_G"
end ".data_nmplv_G";
//********** Text   ********************

extern vec_Mask:label;

begin ".text_nmplv"
///////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMaskV_64u(nm64u* pSrcVec1, nm64u* pSrcVec2, nm64u* pSrcVec3, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsMaskV_64u.html

global _nmppsMaskV__FPUlPUlPUlPUli_ :label;
global _nmppsMaskV_64u:label;
<_nmppsMaskV_64u>
.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	push ar1,gr1	with gr0++;
	push ar2,gr2	with gr0++;
	push ar5,gr5	with gr1=gr0;
	push ar6,gr6	with gr2=gr0;

	ar0 = [--ar5]	with gr6=gr0;		// pSrcVec1
	ar1 = [--ar5];						// pSrcVec2
	ar2 = [--ar5];						// SrcVec3 Mask
	
	delayed call vec_Mask; 
		ar6 = [--ar5];						// pDstVec
		gr5 = [--ar5];						// nSize 
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

return;
.wait;


end ".text_nmplv";
