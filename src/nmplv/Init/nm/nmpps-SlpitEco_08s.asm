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



extern vec_vsum_data_0:label;
extern vec_data_add_afifo:label;
extern vec_Mul2D2W8_AddVr:label;

data ".GlobalSRAM"
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

end ".GlobalSRAM";


begin ".text_nmplv"




/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSplit_8s(nm8s* src, nm8s* dst1, nm8s* dst2, int size);
//!
//! \perfinclude nmppsSplit_8s.html


global _nmppsSplitEco_8s:label;
<_nmppsSplitEco_8s>

.branch;

	ar5 = sp-2		with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar2,gr2    with gr0=gr7<<1;	// gr0 = 4
	push ar3,gr3    with gr1=gr7<<1;	// gr1 = 4
	push ar4,gr4	with gr3=gr6;		// gr3 = 2
	push ar5,gr5;	
	push ar6,gr6    with gr6=gr7;		// gr6 = 2

	ar3=[--ar5];	//	nm8s*		pSrc,			// input buffer		:long Long[nSize]
	ar6=[--ar5];	//	nm8s*		pDstVecEven,	// output buffer	:long Long[nSize]	
	ar2=[--ar5];	//	nm8s*		pDstVecOdd,		// output buffer	:long Long[nSize]	
	gr5=[--ar5];	//	int			nSize			// buffer size in 8-bit elemetns	:[0,8,16,24...]
	
	nb1 = 080808080h;
	sb  = 02020202h;
	vr  = 0;
	ar4 = Weights+2;
	delayed call vec_Mul2D2W8_AddVr with gr5 = gr5>>4;
		ar0 = ar3;
		ar1 = ar3+gr3;
	
	ar6 = ar2;
	ar4 = Weights;
	delayed call vec_Mul2D2W8_AddVr;
		ar0 = ar3;
		ar1 = ar3+gr3;

		
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
