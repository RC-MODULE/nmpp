//------------------------------------------------------------------------
//
//  $Workfile:: QuickSort.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   nmppsDecimate.asm
//! \author Иван Жиленков
//! \brief  
//!
//! \endif
//!
//------------------------------------------------------------------------
//void vec_ClipMul4D4W4_AddVr(nmreg nb1, 
//								nmreg sb, 
//								nmreg F1CR, 
//								nmreg vr, 
//								nmreg ar0, nmreg gr0, 
//								nmreg ar1, nmreg gr1, 
//								nmreg ar2, nmreg gr2, 
//								nmreg ar3, nmreg gr3, 
//								nmreg ar4, nmreg gr4, 
//								nmreg gr5, 
//								nmreg ar6, nmreg gr6)

//void nmppsDecimate_32s(nm32s* pSrc, int startPos, int step, nm32s* pDst, int nSize);
extern vec_Mul2D2W2_AddVr:label;

data ".data_nmplv"
	weights: long[8] = (0000000000000001hl,0hl,						 
						 0000000100000000hl,0hl,
						 
						 0hl,0000000000000001hl,
						 0hl,0000000100000000hl);
end ".data_nmplv";

global _nmppsDecimate_32s: label;
begin ".text_nmplv"
<_nmppsDecimate_32s>
	ar5 = sp - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	
	ar0 = [--ar5]	with gr6 = false;
	vr = gr6;		//vr = 0
	gr4 = [--ar5]	with gr6++;
	gr0 = [--ar5]	with gr6++;
	ar6 = [--ar5];
	gr5 = [--ar5]	with gr4 <<=3;
		
	nb1 = 80000000h	with gr5>>=1; 
	sb  = 2h;
	wtw;
	
	ar4 = weights;
	delayed call vec_Mul2D2W2_AddVr;
		ar1 = ar0 + gr0 	with gr0<<=1;
		ar4 += gr4			with gr1 = gr0;
	
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;
end ".text_nmplv";
