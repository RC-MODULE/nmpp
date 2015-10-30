//------------------------------------------------------------------------
//
//  $Workfile:: SubAbs1.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   SubAbs1.Asm
//! \author Сергей Мушкаев
//! \brief  Функции вычитания для векторов
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_SubAbs1:label;
extern _VEC_TBL_Diagonal_FFh_G:long;
extern _nmppsTmpBuffer16_G_:long;
begin ".text_nmplv"

///////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsAbsDiff1 (nm8s *pSrcVec1, nm8s *pSrcVec2, nm8s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAbsDiff_8s.html

global _nmppsAbsDiff1_8s:label;
global _void._.8.8nmppsAbsDiff1.1char._.0.9._char._.0.9._char._.0.9._int.2 :label;
<_nmppsAbsDiff1_8s>
<_void._.8.8nmppsAbsDiff1.1char._.0.9._char._.0.9._char._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	push ar4,gr4;

	sb	= 02020202h;
	nb1 = 80808080h;
	ar4 = _VEC_TBL_Diagonal_FFh_G;
	rep 8 wfifo=[ar4++],ftw;

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
	f1cr = 80808080h  with gr5>>=3;	// nSize in 64-bit longs
	ar4 = _nmppsTmpBuffer16_G_;
	delayed call vec_SubAbs1;
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
