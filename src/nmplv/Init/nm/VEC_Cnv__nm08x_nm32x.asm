//------------------------------------------------------------------------
//
//  $Workfile:: Cnv08to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Cnv08to32.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h" 

extern vec_vsum_data_0:label;

data ".data"
    WConvert8to32: long[8*4] =  (			1hl, 100000000hl, 0hl dup 6,	// Extract 0,1-st byte
								 0hl dup 2,	1hl, 100000000hl, 0hl dup 4,	// Extract 2,3-rd byte
								 0hl dup 4,	1hl, 100000000hl, 0hl dup 2,	// Extract 4,5-th byte
								 0hl dup 6,	1hl, 100000000hl	     		// Extract 6,7-rd byte);
								 );
end ".data";


begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCnv_8s(nm8s* pSrcVec, nm32s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCnv__FPcPii_.html


global _void._.8.8nmppsCnv_.1char._.0.9._int._.0.9._int.2 :label;
<_nmppsCnv__FPcPii_>
<_void._.8.8nmppsCnv_.1char._.0.9._int._.0.9._int.2>
.branch;
   	delayed goto JumpFromSigned;
		nb1 = 80000000h;

/////////////////////////////////////////////////////////////////////////////////

		

//! \fn void nmppsCnv_8u(nm8u* pSrcVec, nm32u* pDstVec, int nSize)
//!
//! \perfinclude _nmppsCnv__FPUcPUii_.html

global _nmppsCnv__FPUcPUii_:label;
global _void._.8.8nmppsCnv_.1unsigned._char._.0.9._unsigned._int._.0.9._int.2 :label;
<_nmppsCnv__FPUcPUii_>
<_void._.8.8nmppsCnv_.1unsigned._char._.0.9._unsigned._int._.0.9._int.2>
.branch;
	nb1 = 80808080h;
	<JumpFromSigned>
	ar5 = WConvert8to32;
	sb  = 02020202h;
	rep 32 wfifo =[ar5++],ftw;

	ar5 = sp - 2;
	push ar0,gr0	with gr0=false;
	push ar5,gr5	with gr0++;	
	push ar6,gr6	with gr0++;		//gr0=2

	ar0 = [--ar5]	with gr6=gr0;	// pSrcVec , gr6=2
	ar6 = [--ar5] ;					// pDstVec
	gr5 = [--ar5] ;					// nSize in 8-bit elements 
	gr7 = ar0		with gr5>>=3;
	ar5 = ar6+gr6	with gr6<<=2;	// gr6=8
		
	delayed call vec_vsum_data_0;
		wtw;
		ftw;		
		
	ar6 = ar5		with gr6>>=2;	// gr6=2
	ar5 = ar6+gr6	with gr6<<=2;	// gr6=8
	ar0 = gr7;
	delayed call vec_vsum_data_0;
		wtw;
		ftw;
		

	ar6 = ar5		with gr6>>=2;	// gr6=2
	ar5 = ar6+gr6	with gr6<<=2;	// gr6=8
	ar0 = gr7;
	delayed call vec_vsum_data_0;
		wtw;
		ftw;

	ar6 = ar5		with gr6>>=2;	// gr6=2
	ar5 = ar6+gr6	with gr6<<=2;	// gr6=8
	delayed call vec_vsum_data_0;
		ar0 = gr7;
		wtw;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	
	return;
.wait;
end ".text_nmplv";
