//------------------------------------------------------------------------
//
//  $Workfile:: Swap.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Split.asm
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования.
//!
//! \endif
//!
//------------------------------------------------------------------------



extern vec_vsum_data_vr:label;
extern vec_ClipMul1D1W_AddClipD:label;

data ".data_nmplv_L"
	Weights:	long[17] = (
		00000000000000000hl,
		00000000000000001hl,
		00000000000000000hl,
		00000000000000100hl,
		00000000000000000hl,
		00000000000010000hl,
		00000000000000000hl,
		00000000001000000hl,
		00000000000000000hl,
		
		00000000100000000hl,
		00000000000000000hl,
		00000010000000000hl,
		00000000000000000hl,
		00001000000000000hl,
		00000000000000000hl,
		00100000000000000hl,
		00000000000000000hl);

end ".data_nmplv_L";


begin ".text_nmplv"




/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSplitTmp_8s(const m8s* src, nm8s* dst1, nm8s* dst2, int size);
//!
//! \perfinclude nmppsSplit_8s.html


global _nmppsSplitTmp_8s:label;
<_nmppsSplitTmp_8s>

.branch;

	ar5 = sp-2		with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar2,gr2    with gr0=gr7<<1;	// gr0 = 4
	push ar3,gr3    with gr1=gr7;		// gr1 = 2
	push ar4,gr4	with gr3=gr6;		// gr3 = 2
	push ar5,gr5;	
	push ar6,gr6    with gr6=gr7;		// gr6 = 2

	nb1 = 080808080h;
	sb  = 02020202h;
	vr  = 0;
	f1cr=0;
	f2cr=0;
	ar4 = Weights+2;
	rep 16 wfifo=[ar4++],ftw,wtw;
	
	gr2=[--ar5];	//	nm8s*		pSrc,			// input buffer		:long Long[nSize]
	ar2=[--ar5];	//	nm8s*		pDstVecEven,	// output buffer	:long Long[nSize]	
	ar3=[--ar5];	//	nm8s*		pDstVecOdd,		// output buffer	:long Long[nSize]	
	gr5=[--ar5];	//	int			nSize			// buffer size in 8-bit elemetns	:[0,8,16,24...]
	ar5=[--ar5]; 	// 	tmp
	
	//------- even bytes extraction --------------------------------------
	delayed call vec_vsum_data_vr with gr5 = gr5>>4;
		ar0 = gr2;	// ar0 = src	; gr0 = 4
		ar6 = ar5;	// ar6 = tmp	; gr6 = 2
	
	ftw,wtw;
	ar6 = ar2 ;		// ar6 = dstEven
	delayed call vec_ClipMul1D1W_AddClipD  with gr7 = gr2 + gr6;
		ar0 = gr7 ;	// ar0 = src+2 	; gr0 = 4
		ar1 = ar5;	// ar1 = tmp	; gr1 = 2
	
	//------- odd byte extraction --------------------------------------
	ar4 = Weights;
	rep 16 wfifo=[ar4++],ftw,wtw;
	delayed call vec_vsum_data_vr;
		ar0 = gr2;	// ar0 = src
		ar6 = ar5;	// ar6 = tmp
	
	ftw,wtw;
	ar6 = ar3;		// ar6 = dstOdd
	delayed call vec_ClipMul1D1W_AddClipD with gr7 = gr2 + gr6;
		ar0 = gr7;	// ar0 = src+2 ; gr0 = 4	
		ar1 = ar5;	// ar1 = tmp

		
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
