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
//! \file   Cnv32to08.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора. 
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_Mul4D4W2_AddVr:label;

   
import from macros.mlb;
import MULT32 from rtmacro.mlb;

data ".data_nmplv_G"
   G_Matrix: long[8] =  (1hl, 100hl,
                         10000hl, 1000000hl,
                         100000000hl, 10000000000hl,
                         1000000000000hl, 100000000000000hl);
end ".data_nmplv_G";

data ".data_nmplv_L"
   L_Matrix: long[8] =  (1hl, 100hl,
                         10000hl, 1000000hl,
                         100000000hl, 10000000000hl,
                         1000000000000hl, 100000000000000hl);
end ".data_nmplv_L";

begin ".text_nmplv"

//! \fn void nmppsCnv_32s8s(nm32s* pSrcVec, nm8s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCnv_32s8s.html

global _nmppsCnv_32s8s:label;
<_nmppsCnv_32s8s>
.branch;
    ar5 = sp - 2 with gr7 = false;
	push ar0,gr0 with gr7++;
	push ar1,gr1 with gr7++;		//gr7=2
	push ar2,gr2 with gr0 = gr7;
	push ar3,gr3 with gr1 = gr7;
	push ar4,gr4 with gr2 = gr7;
	push ar5,gr5 with gr3 = gr7<<2;
	push ar6,gr6 with gr6 = gr7;
    sb  = gr7;	

	gr4 = 80808080h;
	nb1 = gr4;
	
	gr5 = [--ar5];	// pSrcVec
	ar6 = [--ar5];  // pDstVec
	ar0 = gr5;
	ar1 = ar0+gr0	with gr0=gr7<<2;
	ar2 = ar1+gr1	with gr1=gr7<<2;
	ar3 = ar2+gr2	with gr2=gr7<<2;
    gr5 = [--ar5]	with gr5;

	if < delayed goto LoadLocalMatrix;
		ar4 = L_Matrix;
	
	ar4 = G_Matrix;
	<LoadLocalMatrix>
	
	delayed call vec_Mul4D4W2_AddVr with gr5>>=3;
		gr7= false;
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
