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
extern _VEC_TBL_MinusOne_G:long;
extern _VEC_TmpBuffer16_G:long;
begin ".text_nmplv"

///////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_SubV_Abs (nm64s *pSrcVec1, nm64s *pSrcVec2, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_SubV_Abs__FPlPlPli.html

global _VEC_SubV_Abs__FPlPlPli:label;
global _void._.8.8VEC_SubV_Abs.1long._.0.9._long._.0.9._long._.0.9._int.2 :label;
<_VEC_SubV_Abs__FPlPlPli>
<_void._.8.8VEC_SubV_Abs.1long._.0.9._long._.0.9._long._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	push ar4,gr4;

	sb	= 00000000h;
	nb1 = 00000000h;
	ar4 = _VEC_TBL_MinusOne_G;
	rep 1 wfifo=[ar4++],ftw;

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

	f1crh = 80000000h;
	f1crl = 00000000h;

	ar4 = _VEC_TmpBuffer16_G;
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
