//------------------------------------------------------------------------
//
//  $Workfile:: Cnv32to64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc. 
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Cnv16to64.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

import from macros.mlb;
extern vec_vsum_data_0:label;
data ".data"
    WConvert32to64: long[2*2] =  (1hl,	0hl,	// Extract 1-st byte
								  0hl,	1hl		// Extract 4-rd byte
								 );
end ".data";
begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////


//! \fn void nmppsCnv_32s(nm32s* pSrcVec, nm64s* pDstVec, int nSize)
//!
//! \perfinclude _nmppsCnv__FPiPli_.html


global _void._.8.8nmppsCnv_.1int._.0.9._long._.0.9._int.2 :label;

<_void._.8.8nmppsCnv_.1int._.0.9._long._.0.9._int.2>
.branch;
	delayed goto JumpFromSigned;
		nb1 = 00000000h;

/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCnv_32u(nm32u* pSrcVec, nm64u* pDstVec, int nSize)
//!
//! \perfinclude _nmppsCnv__FPUiPUli_.html


global _void._.8.8nmppsCnv_.1unsigned._int._.0.9._unsigned._long._.0.9._int.2 :label;
<_void._.8.8nmppsCnv_.1unsigned._int._.0.9._unsigned._long._.0.9._int.2>
.branch;
	nb1 = 80000000h;
	<JumpFromSigned>
	ar5 = WConvert32to64 set;
	sb  = 00000002h;
	
	rep 4 wfifo =[ar5++],ftw;

	ar5 = sp - 2;
	push ar0,gr0	with gr0=false;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr0++;		//gr0=2

	ar0 = [--ar5]	with gr6=gr0;	// pSrcVec , gr6=2
	ar6 = [--ar5] ;					// pDstVec
	gr5 = [--ar5] ;					// nSize in 8-bit elements 
	gr7 = ar0		with gr5>>=1;
	ar5 = ar6+gr6	with gr6<<=1;	// gr6=4
		
	delayed call vec_vsum_data_0;
		wtw;
		ftw;		
		
	
	
	ar6 = ar5		with gr6>>=1;	// gr6=2
	ar5 = ar6+gr6	with gr6<<=1;	// gr6=4
	delayed call vec_vsum_data_0;
		ar0 = gr7;
		wtw;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;
.wait;
end ".text_nmplv";
