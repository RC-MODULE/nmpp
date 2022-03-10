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

//void nmppsDecimate_16s(nm16s* pSrc, int startPos, int step, nm16s* pDst, int nSize);
extern vec_ClipMul4D4W4_AddVr:label;

data ".data_nmplv"
	weights: long[64] = (0000000000000001hl,0hl,0hl,0hl,
						 0000000000010000hl,0hl,0hl,0hl,						 
						 0000000100000000hl,0hl,0hl,0hl,						 
						 0001000000000000hl,0hl,0hl,0hl,
						 
						 0hl,0000000000000001hl,0hl,0hl,
						 0hl,0000000000010000hl,0hl,0hl,
						 0hl,0000000100000000hl,0hl,0hl,						 
						 0hl,0001000000000000hl,0hl,0hl,
						 
						 0hl,0hl,0000000000000001hl,0hl,
						 0hl,0hl,0000000000010000hl,0hl,						 
						 0hl,0hl,0000000100000000hl,0hl,
						 0hl,0hl,0001000000000000hl,0hl,
						 
						 0hl,0hl,0hl,0000000000000001hl,
						 0hl,0hl,0hl,0000000000010000hl,						 
						 0hl,0hl,0hl,0000000100000000hl,						 
						 0hl,0hl,0hl,0001000000000000hl);
end ".data_nmplv";

global _nmppsDecimate_16s: label;
begin ".text_nmplv"
<_nmppsDecimate_16s>
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
	ar6 = [--ar5]	with gr0 >>=1;
	gr5 = [--ar5]	with gr4 <<=5;
		
	nb1 = 80008000h	with gr5>>=2; 
	sb  = 20002h;
	f1cr = 80008000h;
	wtw;
	
	ar4 = weights with gr1 = gr0;
	ar1 = ar0 + gr0 	with gr2 = gr1;
	ar2 = ar1 + gr1 	with gr3 = gr2<<2;	
	delayed call vec_ClipMul4D4W4_AddVr	with gr0<<=2;
		ar3 = ar2 + gr2 with gr1<<=2;
		ar4 += gr4		with gr2<<=2;
	
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;
end ".text_nmplv";
