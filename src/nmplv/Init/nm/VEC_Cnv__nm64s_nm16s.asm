//------------------------------------------------------------------------
//
//  $Workfile:: Convert16to08.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Convert16to08.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif 
//!
//------------------------------------------------------------------------
//#include "vConvert.h"


extern vec_ClipMul4D4W1_AddVr:label;
extern _VEC_TBL_Diagonal_0001h_G:long[16];
extern _VEC_TBL_Diagonal_0001h_L:long[16];

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsConvert_64s(nm64s* pSrcVec, nm16s* pDstVec, int nSize)
//!
//! \perfinclude _nmppsConvert_64s.html


global _nmppsConvert_64s:label;
<_nmppsConvert_64s>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar2,gr2	;
	push ar3,gr3	;
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr3=gr7<<2;// gr3=8;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	
	gr5 = [--ar5];					// pSrcVec
	gr4 = 80008000h;
	sb  = 0;
	f1cr= 0;
	nb1 = gr4;
	ar0 = gr5		with gr5;
	
	if < delayed goto LoadLocalMatrix;
		ar4 = _VEC_TBL_Diagonal_0001h_L;
	
	ar4 = _VEC_TBL_Diagonal_0001h_G;
	<LoadLocalMatrix>
	ar1 = ar0+gr0 with gr1=gr0;
	ar2 = ar1+gr1 with gr2=gr0;
	ar3 = ar2+gr2 with gr6=gr0;
	ar6 = [--ar5] with gr1=gr3;		// pDstVec
	gr5 = [--ar5] with gr2=gr3;		// nSize 
	gr0 = gr3;
	delayed call vec_ClipMul4D4W1_AddVr with gr5>>=2;
		with gr7 = false;
		vr  = gr7;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";
