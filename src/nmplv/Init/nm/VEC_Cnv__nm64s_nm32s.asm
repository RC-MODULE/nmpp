//------------------------------------------------------------------------
//
//  $Workfile:: Cnv16to08.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Cnv16to08.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif 
//!
//------------------------------------------------------------------------
//#include "vConvert.h"


extern vec_Mul2D2W1_AddVr:label;
extern _VEC_TBL_Diagonal_00000001h_G:long[2];
extern _VEC_TBL_Diagonal_00000001h_L:long[2];

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCnv_64s(nm64s* pSrcVec, nm32s* pDstVec, int nSize)
//!
//! \perfinclude _nmppsCnv_64s.html


global _void._.8.8nmppsCnv_.1long._.0.9._int._.0.9._int.2 :label;
<_void._.8.8nmppsCnv_.1long._.0.9._int._.0.9._int.2>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	
	gr5 = [--ar5];					// pSrcVec
	gr4 = 80000000h;
	sb  = 00000000h;
	nb1 = gr4;
	ar0 = gr5		with gr5;
	
	if < delayed goto LoadLocalMatrix;
		ar4 = _VEC_TBL_Diagonal_00000001h_L;
	
	ar4 = _VEC_TBL_Diagonal_00000001h_G;
	<LoadLocalMatrix>
	ar6 = [--ar5];					// pDstVec
	gr5 = [--ar5];					// nSize 
	delayed call vec_Mul2D2W1_AddVr with gr5>>=1;
		ar1 = ar0+gr0	with gr7 = false;
		vr  = gr7		with gr0 = gr1;// gr0=4	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";
