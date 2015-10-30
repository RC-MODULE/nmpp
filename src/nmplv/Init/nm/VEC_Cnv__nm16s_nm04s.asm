//------------------------------------------------------------------------
//
//  $Workfile:: Cnv32to08.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Cnv32to04.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора. 
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_ClipMul4D4W4_AddVr:label;
extern _VEC_TBL_Diagonal_1h_G:long[16];
extern _VEC_TBL_Diagonal_1h_L:long[16];

begin ".text_nmplv"

//! \fn void nmppsCnv_16s(nm16s* pSrcVec, nm4s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCnv_32s.html


global _void._.8.8nmppsCnv_.1short._.0.9._class._nm4s._.0.9._int.2 :label;
<_void._.8.8nmppsCnv_.1short._.0.9._class._nm4s._.0.9._int.2>
.branch;
    ar5 = sp - 2 with gr7 = false;
	push ar0,gr0 with gr7++;
	push ar1,gr1 with gr7++;		//gr7=2
	push ar2,gr2 with gr0 = gr7;
	push ar3,gr3 with gr1 = gr7;
	push ar4,gr4 with gr2 = gr7;
	push ar5,gr5 with gr3 = gr7<<2;
	push ar6,gr6 with gr6 = gr7;
    sb  = 000020002h;
	gr4 = 088888888h;
    nb1 = gr4;
	
	gr5 = [--ar5];	// pSrcVec
	ar6 = [--ar5];  // pDstVec
	ar0 = gr5;
	ar1 = ar0+gr0	with gr0=gr7<<2;
	ar2 = ar1+gr1	with gr1=gr7<<2;
	ar3 = ar2+gr2	with gr2=gr7<<2;
    gr5 = [--ar5]	with gr5; //nSize

	if < delayed goto LoadLocalMatrix with gr7=false;
		ar4 = _VEC_TBL_Diagonal_1h_L;
	
	ar4 = _VEC_TBL_Diagonal_1h_G;
	<LoadLocalMatrix>

	delayed call vec_ClipMul4D4W4_AddVr with gr5>>=4;
		f1cr=gr7;
		vr = gr7;
		
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
