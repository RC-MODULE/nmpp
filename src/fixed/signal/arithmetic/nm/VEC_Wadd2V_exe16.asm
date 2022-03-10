//------------------------------------------------------------------------
//
//  $Workfile:: nmppsWadd2V_exe16_.asm             $
//
//  <nmplv>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   nmppsWadd2V_exe16_.asm
//! \author ������ ���������
//! \brief  <���������� ����� ���� �������� ���� nm16s>
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_Mul2D2W4_AddVr:label;
// void nmppsWeightedSum_Exe_16s32s(nm16s* pSrcVec1,nm16s* pSrcVec2, S_nmppsWeightedSum* kerW, nm32s* pDstVec, int nSize);
global _nmppsWeightedSum_Exe_16s32s:label;
<_nmppsWeightedSum_Exe_16s32s>
	ar5=ar7-2;
	push ar0,gr0; 
	push ar1,gr1;  
	push ar2,gr2; 
	push ar4,gr4; 
	push ar6,gr6;
	ar0=[--ar5]with gr4=false;  // pSrcVec1
	f1cr = gr4;
	ar1=[--ar5]with gr0=gr4+1;  // pSrcVec2
	ar4=[--ar5]with gr0<<=1;    // kerW
	ar6=[--ar5]with gr1=gr0;    // pDstVec
	push ar5,gr5;
	gr5=[--ar5]with gr6=gr0<<1; // nSize, gr6=4
	vr=gr4 with gr5>>=2;
	gr4=80000000h;// 2x32 on Y Vport
	nb1=gr4;
	ar5=ar6; 
	ar2=ar0; 
	gr2=ar1; 
	
	sb=20002h; // 4x16 on X Vport
	delayed call vec_Mul2D2W4_AddVr;
		ar4=ar4+4;	

	ar6=ar5+2; ar0=ar2; ar1=gr2;
	delayed call vec_Mul2D2W4_AddVr;
		ar4=ar4-4;
		
	pop ar5,gr5;
	pop ar6,gr6;
	pop ar4,gr4; 
	pop ar2,gr2;
	pop ar1,gr1; 
	pop ar0,gr0;
	return;

///==========================================

end ".text_nmplv";
