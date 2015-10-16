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
import from macros.mlb;

extern vec_vsum_data_0	:label;
extern vec_vsum_data_vr	:label;
extern vec_MulVN_AddVN	:label;
extern _VEC_TmpBuffer16_G:long[16];

begin ".text_nmplv"




/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void VEC_MulC_AddV_AddC (nm32s *pSrcVec1, int nMulVal, nm32s *pSrcVec2, int nAddVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_MulC_AddV_AddC__FPiiPiiPii.html

global _VEC_MulC_AddV_AddC__FPiiPiiPii:label;
global _void._.8.8VEC_MulC_AddV_AddC.1int._.0.9._int.9._int._.0.9._int.9._int._.0.9._int.2 :label;
<_VEC_MulC_AddV_AddC__FPiiPiiPii>
<_void._.8.8VEC_MulC_AddV_AddC.1int._.0.9._int.9._int._.0.9._int.9._int._.0.9._int.2>

.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];			// pSrcVec1
	gr5 = [--ar5];			// MulN 
	gr7 = false;
	//-- WFIFO init ---------------------------
	ar6 = _VEC_TmpBuffer16_G;
	[ar6++] = gr5;
	[ar6++] = gr7;
	[ar6++] = gr7;
	[ar6++] = gr5;
	ar6-=4;
	gr7 = 80000000h;
	sb  = 2;
	nb1 = gr7;
	rep 2 wfifo=[ar6++],ftw;
	//-----------------------------------------
	ar1 = [--ar5];			// pSrcVec2
 	gr5 = [--ar5];			// AddN
	vr	= gr5;
	ar6 = [--ar5];			// pDstVec
	gr5 = [--ar5];			// nSize
	gr0 = 2		with gr5 >>= 1;
	gr6 = 2;	
	gr1 = 2;
	delayed call vec_MulVN_AddVN;
	WTW_REG(gr7);
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
