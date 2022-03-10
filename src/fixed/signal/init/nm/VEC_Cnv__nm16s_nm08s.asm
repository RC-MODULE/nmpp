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


extern vec_Mul2D2W4_AddVr:label;

data ".data_nmplv_L"
	LWConvert16to8:  long[8] = ( 0000000000000001hl, 0000000000000100hl,
                       0000000000010000hl, 0000000001000000hl,
                       0000000100000000hl, 0000010000000000hl,
                       0001000000000000hl, 0100000000000000hl);


end ".data_nmplv_L";


data ".data_nmplv_G"
	GWConvert16to8:  long[8] = ( 0000000000000001hl, 0000000000000100hl,
                       0000000000010000hl, 0000000001000000hl,
                       0000000100000000hl, 0000010000000000hl,
                       0001000000000000hl, 0100000000000000hl);

end ".data_nmplv_G";
begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsConvert_16s8s(nm16s* pSrcVec, nm8s* pDstVec, int nSize)
//!
//! \perfinclude nmppsConvert_16s8s.html


global _nmppsConvert_16s8s:label;
<_nmppsConvert_16s8s>
.branch;
	ar5 = sp - 2	with gr7=false;
	f1cr = gr7;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	
	gr5 = [--ar5];					// pSrcVec
	gr4 = 80808080h;
	sb  = 00020002h;
	nb1 = gr4;
	ar0 = gr5		with gr5;
	
	if < delayed goto LoadLocalMatrix;
		ar4 = LWConvert16to8;
	
	ar4 = GWConvert16to8;
	<LoadLocalMatrix>
	ar6 = [--ar5];					// pDstVec
	gr5 = [--ar5];					// nSize 
	ar1 = ar0+gr0	with gr7 = false;
	vr  = gr7		with gr0 = gr1;// gr0=4	
	call vec_Mul2D2W4_AddVr	with gr5>>=3;
		
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";
