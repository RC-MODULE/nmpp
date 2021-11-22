//------------------------------------------------------------------------
//
//  $Workfile:: SubAbs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   SubAbs.Asm
//! \author Сергей Мушкаев
//! \brief  Функции вычитания для векторов
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_SubAbs:label;
extern _VEC_TBL_Diagonal_FFFFh_G:long;
extern _nmppsTmpBuffer16_G_:long;
begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsAbsDiff (nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAbsDiff_16s.html

global _nmppsAbsDiff_16s:label;
<_nmppsAbsDiff_16s>
.branch;
	ar5 = sp - 2;

	push ar4,gr4;

	sb	= 00020002h;
	nb1 = 80008000h;
	ar4 = _VEC_TBL_Diagonal_FFFFh_G;
	rep 4 wfifo=[ar4++],ftw;

	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff1
	ar1 = [--ar5];	// SrcBuff2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize
	gr0 = 2;
	gr1 = 2;
	gr6 = 2;
	f1cr = 80008000h  with gr5>>=2;	// nSize in 64-bit longs
	ar4 = _nmppsTmpBuffer16_G_;
	delayed call vec_SubAbs;
		nul;
		wtw;
		
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
	pop ar4,gr4;
	return;
.wait;


end ".text_nmplv";
