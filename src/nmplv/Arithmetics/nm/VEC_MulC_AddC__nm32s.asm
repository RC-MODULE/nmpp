//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V32N32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V32N32.asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//import from macros.mlb;

extern vec_vsum_data_0	:label;
extern vec_vsum_data_vr	:label;
extern vec_MulVN_AddVN	:label;
extern _nmppsTmpBuffer16_G_:long[16];

begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMulC_AddC (nm32s *pSrcVec, int nMulVal, int nAddVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC_AddC_32s.html

global _nmppsMulC_AddC_32s:label;
global _nmppsMulC_AddC32s:label;
<_nmppsMulC_AddC_32s>
<_nmppsMulC_AddC32s>

.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5]	with gr0=false;		// pSrcVec
	gr5 = [--ar5]	with gr7 = false;	// MulN 

	//-- WFIFO init ---------------------------
	ar6 = _nmppsTmpBuffer16_G_;
	[ar6++] = gr5;
	[ar6++] = gr7;
	[ar6++] = gr7;
	[ar6++] = gr5;
	ar6-=4;
	nb1 = 80000000h;
	sb  = 2;
	rep 2 wfifo=[ar6++],ftw;
	//-----------------------------------------

	gr5 = [--ar5]	with gr0++;			// AddN
	vr	= gr5		with gr0++;
	ar6 = [--ar5]	with gr6=gr0;		// pDstVec
    gr5 = [--ar5];						// nSize
	
	delayed call vec_vsum_data_vr with gr5 >>=1;
		nul;
		wtw;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;



.wait;

end ".text_nmplv";
