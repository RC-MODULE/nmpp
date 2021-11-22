//------------------------------------------------------------------------
//
//  $Workfile:: Convert32to16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Convert32to16.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vConvert.h"
//
extern vec_Mul2D2W2_AddVr:label;

data ".data_nmplv_L"
	LWConvert32to16: long[4] =(0000000000000001hl,
						0000000000010000hl,
						0000000100000000hl,
						0001000000000000hl);

end ".data_nmplv_L";


data ".data_nmplv_G"
	GWConvert32to16: long[4] =(0000000000000001hl,
						0000000000010000hl,
						0000000100000000hl,
						0001000000000000hl);
end ".data_nmplv_G";

/////////////////////////////////////////////////////////////////////////////////////


begin ".text_nmplv"

//! \fn void nmppsConvert_32s16s(nm32s* pSrcVec, nm16s* pDstVec, int nSize)
//!
//! \perfinclude nmppsConvert_32s16s.html

global _nmppsConvert_32s16s:label;
<_nmppsConvert_32s16s>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	
	gr5 = [--ar5];					// pSrcVec
	gr4 = 80008000h;
	sb  = 00000002h;
	nb1 = gr4;
	ar0 = gr5		with gr5;
	
	if < delayed goto LoadLocalMatrix;
		ar4 = LWConvert32to16 set;
	
	ar4 = GWConvert32to16 set;
	<LoadLocalMatrix>
	ar6 = [--ar5];					// pDstVec
	gr5 = [--ar5];					// nSize 
	ar1 = ar0+gr0	with gr7 = false;
	vr  = gr7		with gr0 = gr1;// gr0=4	
	call vec_Mul2D2W2_AddVr	with gr5>>=2;
		
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;

	return;
.wait;
end ".text_nmplv";
