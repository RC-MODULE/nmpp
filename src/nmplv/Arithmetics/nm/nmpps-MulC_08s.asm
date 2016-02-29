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

begin ".text_nmplv"

extern vec_vsum_data_0:label;

//! \fn void nmppsMulC_8s (nm8s *pSrcVec, int8b nVal, nm8s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC_8s.html

global _nmppsMulC_8s:label;
<_nmppsMulC_8s>
.branch;
	ar5 = sp-2			with gr7 = false;
	push ar0,gr0		with gr0 = gr7+1;
	push ar5,gr5;	
	push ar6,gr6		with gr0++;			// gr0=2;

	ar0 = [--ar5];						// pSrcVec
	gr6 = [--ar5];						// SrcN
	ar6 = gr7			with gr6 = gr6<<24;	// pDstVec
	ar0 = ar7			with gr7 = gr0<< 3;	// gr7=16;
	ar7+= gr7			with gr6 = gr6>>24;	// ar6=0; gr6= N
	[ar0++] = gr6		with gr6 = gr6<<8;
	[ar0++] = gr7;
	[ar0++] = gr6		with gr6 = gr6<<8; 
	[ar0++] = gr7;	
	[ar0++] = gr6		with gr6 = gr6<<8;
	[ar0++] = gr7;	
	[ar0++] = gr6		with gr6 = gr6>>24; 
	[ar0++] = gr7;
	[ar0++] = ar6,gr6	with gr6 = gr6<<8;
	[ar0++] = ar6,gr6	with gr6 = gr6<<8; 
	[ar0++] = ar6,gr6	with gr6 = gr6<<8;
	[ar0++] = ar6,gr6	with gr7 = -gr7; 
	ar7 = ar7+gr7;
	ar0 = ar7;
	nb1 = 80808080h;
	sb  = 02020202h;
	rep 8 wfifo=[ar0++],ftw,wtw;
	ar6 = [--ar5];								// dst
	delayed call vec_vsum_data_0 ;		
		gr5 = [--ar5];							// size
		gr5 = gr5>>3;							// size in 64-bit longs
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
