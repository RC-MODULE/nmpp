//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulNM_AddVsVc.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulNM_AddVsVc.asm
//! \author Сергей Мушкаев
//! \brief  <Краткое описание файла.>
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vClip.h"
extern 	LWSum2CharBuffers: long[8*16];
extern 	GWSum2CharBuffers: long[8*16];

import from macros.mlb;

data ".data_nmplm_G"
	GWScalar:long[2]=(0l,0l);
end ".data_nmplm_G";


extern vec_MulVN_AddVN:label;

begin ".text_nmplm"

//--------------------------------------------------------------------
//! \fn void MTR_MulC_AddVsVc(int MulN, nm32s* pSrcMtr, nm32s* pSrcVecStr, nm32s* pSrcVecCol, nm32s* pDstMtr, int nHeight, int nWidth);
//!
//! \perfinclude _MTR_MulC_AddVsVc__FiPiPiPiPiii.html
//--------------------------------------------------------------------
global _MTR_MulC_AddVsVc__FiPiPiPiPiii:label;
global _void._.8.8MTR_MulC_AddVsVc.1int.9._int._.0.9._int._.0.9._int._.0.9._int._.0.9._int.9._int.2 :label;
<_MTR_MulC_AddVsVc__FiPiPiPiPiii>
<_void._.8.8MTR_MulC_AddVsVc.1int.9._int._.0.9._int._.0.9._int._.0.9._int._.0.9._int.9._int.2>
.branch;
	ar5 = sp-2		with gr7=false;	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	gr5 = [--ar5];	//			int			MulN,
	//-- WFIFO init ---------------------------
	ar0 = GWScalar;
	[ar0++] = gr5;
	[ar0++] = gr7;
	[ar0++] = gr7;
	[ar0++] = gr5;
	ar0-=4;
	gr7 = 80000000h;
	sb  = 2;
	nb1 = gr7;
	rep 2 wfifo=[ar0++],ftw;
	//-----------------------------------------
	ar0 = [--ar5];	//			nm32s*		SrcMtr,
	ar3 = [--ar5];	//			nm32s*		SrcVecStr,
	ar2 = [--ar5];	//			nm32s*		SrcVecCol,
	ar6 = [--ar5];	//			nm32s*		DstMtr,
	gr3 = [--ar5];	//			int			nHeight,
	gr5	= [--ar5];	//			int			nWidth);

	gr0 = 2		with gr5 >>= 1;
	gr6 = 2;	
	gr1 = 2;
	ar1 = ar3;
	WTW_REG(gr7);
	
	<Next_MulString>
	gr7 = [ar2++];
	vr = gr7;
	call vec_MulVN_AddVN;
	
	with gr3--;
	if <>0 delayed goto Next_MulString;
		ar1=ar3;
		nul;
	

	
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

