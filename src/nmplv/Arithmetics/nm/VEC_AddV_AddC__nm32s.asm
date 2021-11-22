//------------------------------------------------------------------------
//
//  $Workfile:: AddVVN.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   AddVVN.asm
//! \author Сергей Мушкаев
//! \brief  Функции суммирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------


data ".data_nmplv_G"
	GTmpLong1:long[1];
	GWDiag32: long[2]=(1hl,100000000hl);

end ".data_nmplv_G";

//import from macros.mlb;
extern vec_MulVN_AddVN:label;

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsAdd_AddC (nm32s *pSrcVec1, nm32s *pSrcVec2, int nVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAdd_AddC_32s.html

global _nmppsAdd_AddC_32s:label;
global _nmppsAdd_AddC32s:label;
<_nmppsAdd_AddC_32s>
<_nmppsAdd_AddC32s>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	//nm32s*	pSrcVec1,		// input buffer		:long Local [Size/2]
	ar1 = [--ar5];	//nm32s*	pSrcVec2,		// input buffer		:long Local [Size/2]
	gr7 = [--ar5];	//int	nVal,				// additional constant
	ar6 = [--ar5];	//nm32s*	pDstVec,			// output buffer	:long Global[Size/2]
	gr5 = [--ar5];	//int	nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]

	sb  = 2;
	nb1 = 80000000h with gr5>>=1;			// nSize in 64-bit longs
	ar5 = GWDiag32;
	rep 2 wfifo = [ar5++],ftw;
	wtw;

	vr  = gr7;
	gr0 = 2;
	delayed call vec_MulVN_AddVN;
		gr6 = gr0;
		gr1 = gr0;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;



end ".text_nmplv";
