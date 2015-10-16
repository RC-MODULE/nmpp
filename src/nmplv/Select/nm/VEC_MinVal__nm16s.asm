//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   GetMax.asm
//! \author Сергей Мушкаев
//! \brief  Статистические функции.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vMinMax.h"
import from macros.mlb;
extern	_VEC_TmpBuffer64_G: long;
extern	_VEC_TmpBuffer16_G: long;
extern vec_MinVal_v4nm16s:label;
extern vec_MinVal:label;




begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void VEC_MinVal (nm16s *pSrcVec, int nSize, int16b &nMinValue) 
//!
//! \perfinclude _VEC_MinVal__FPSsiRi.html

global _VEC_MinVal__FPSsiRi :label;
global _void._.8.8VEC_MinVal.1short._.0.9._int.9._int._.6.2 :label;
<_VEC_MinVal__FPSsiRi>
<_void._.8.8VEC_MinVal.1short._.0.9._int.9._int._.6.2>
.branch;
	ar5=sp-2;
	PUSH_REGS();
	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec
	gr6 = [--ar5];									// Pointer to Minimum
	
	gr0=2 with gr5 >>=2;							// nSize in 64-bit longs
	gr4 =80008000h;
	nb1 =gr4;
	f1cr=gr4;
	wtw;
	ar4 = _VEC_TmpBuffer64_G;
	delayed call vec_MinVal;
		ar6=_VEC_TmpBuffer16_G;								// 4xMinimum

	delayed call vec_MinVal_v4nm16s;
		ar0=ar6;
		nul;

	[gr6]=gr7;
	POP_REGS();
return;
.wait;




	

end ".text_nmplv";
