//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V08N16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V08N16.asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов
//!
//! \endif
//!
//------------------------------------------------------------------------
import from macros.mlb;


data ".data_nmplv_G"
	GWScalar:long[8]=(0l dup 8);	
end ".data_nmplv_G";
//********** Text   ********************


begin ".text_nmplv"

extern vec_vsum_data_0:label;

//! \fn void nmppsMulC (nm8s *pSrcVec, int16b nVal, nm16s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC_8s.html

global _nmppsMulC_8s:label;
global _nmppsMulC8s:label;
<_nmppsMulC_8s>
<_nmppsMulC8s>
.branch;


	ar5 = sp-2		with gr7 = false;
	push ar0,gr0	with gr0 = gr7+1;
	push ar5,gr5	;
	push ar6,gr6	with gr0++;			// gr0=2;

	ar0 = [--ar5];			// pSrcVec
	push ar0,gr0;
	gr6 = [--ar5];						// Scalar value
	//-- WFIFO init ---------------------------
	ar0 = GWScalar	with gr6 <<=16;
	ar6 = gr7		with gr6 >>=16;
	gr7 = ar0;
	[ar0++gr0]=gr6	with gr6 <<=16;
	[ar0++gr0]=gr6	with gr6 >>=16;
	[ar0++] = ar6,gr6 with gr6<<=16;
	[ar0++] = ar6,gr6 with gr6 = gr0<<1;// gr6=4 
	
	
	nb1 = 80008000h;
	sb  = 02020202h;
	ar0 = gr7;
	rep 8 wfifo=[ar0++],ftw;
	rep 4 wfifo=[--ar0];
	ar0 = gr7;
	rep 4 wfifo=[ar0++];
	//-----------------------------------------
	pop ar0,gr0;
	ar6 = [--ar5];			// pDstVec
    gr5 = [--ar5];			// nSize
	
	push ar0,gr0;
	push ar6,gr6;
	delayed call vec_vsum_data_0 with gr5 >>= 3;
		wtw;
		ftw;

	pop ar6,gr6;
	pop ar0,gr0;
	
	nul;
	wtw;
	delayed call vec_vsum_data_0;
		ar6+=2;

	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
