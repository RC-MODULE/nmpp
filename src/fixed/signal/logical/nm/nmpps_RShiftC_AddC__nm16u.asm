//------------------------------------------------------------------------
//
//  $Workfile:: RSH16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   RSH16AddC.asm
//! \author S. Mushkaev
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vShift.h"

extern vec_vsum_shift_data_vr:label;
extern vec_vsum_data_vr:label;
extern _VEC_TBL_BackTriangle_nm16_G:long;
extern _VEC_TBL_Diagonal_0001h_G:long;
extern _VEC_TBL_Diagonal_0001h_Interlace_G:long;
extern _VEC_TBL_SB_Split_nm16s:	long;
extern _VEC_TBL_NB_Split_nm16s:	long;


begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsRShiftC_AddC_16u(nm16u *pSrcVec,  int nShift, uint16b nAddVal,  nm16u *pDstVec, int nSize);
//!
//! \perfinclude _nmppsRShiftC_AddC_16u.html
global _nmppsRShiftC_AddC_16u:label;
<_nmppsRShiftC_AddC_16u>
.branch;
	ar5 = sp - 2;
	push ar0,gr0;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5]; // nm16u *pSrcVec,
	gr0 = [--ar5]; // int nShift, 
	gr5 = [--ar5]; // int nAddVal, 
	
	// Set vr
	ar6 = _VEC_TBL_BackTriangle_nm16_G with gr6=gr0<<1;
	gr7 = [ar6+=gr6];							// Load mask for vr
	gr5 = gr5 and not gr7;
	gr7 = gr5 << 16;
	gr5 = gr7 >> 16;
	gr7 = gr7 or gr5;
	vr  = gr7;

	// Set nb1
	ar6 = _VEC_TBL_NB_Split_nm16s with gr6=gr0<<1;
	nb1 = [ar6+=gr6];

	// Set sb
	ar6 = _VEC_TBL_SB_Split_nm16s with gr6=gr0>>1;
	gr6<<=1;
	sb = [ar6+=gr6];

	// Set wfifo
	with gr7=gr0-1;  // if (nShift>1)
	if >  delayed goto LoadWfifo8 	with gr0<<=31; // Load 8 rows into matrix
		nul;
		nul;
	<LoadWfifo4>
	ar6 = _VEC_TBL_Diagonal_0001h_G;
	delayed goto Start_RightShift;
		rep 4 wfifo=[ar6++],ftw;
		nul;

	<LoadWfifo8>
	ar6 = _VEC_TBL_Diagonal_0001h_Interlace_G;
	rep 8 wfifo=[ar6++],ftw;

	// Start shift
	<Start_RightShift>
	// if (nShift&1==0)
	if =0 delayed goto Even_RightShift with gr0=false;
		ar6 = [--ar5]	with gr0++; // nm16u *pDstVec,
		gr5 = [--ar5]	with gr0++; // int nSize

	<Odd_RightShift>
	delayed call vec_vsum_shift_data_vr with gr5>>=2;
		wtw;
		gr6 = gr0;
	goto End_RightShift;
	
	<Even_RightShift>
	delayed call vec_vsum_data_vr with gr5>>=2;
		wtw;
		gr6 = gr0;

	<End_RightShift>


	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;
.wait; 
end ".text_nmplv";




