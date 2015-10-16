//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
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
extern vec_MaxVal_v8nm8s:label;
extern vec_MaxVal:label;


begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_MaxVal (nm8s *pSrcVec, int nSize, int8b &nMaxValue) 
//!
//! \perfinclude _VEC_MaxVal__FPciRi.html


global _VEC_MaxVal__FPciRi :label;
global _void._.8.8VEC_MaxVal.1char._.0.9._int.9._int._.6.2 :label;
<_VEC_MaxVal__FPciRi>
<_void._.8.8VEC_MaxVal.1char._.0.9._int.9._int._.6.2>
.branch;
	ar5=sp-2;
	PUSH_REGS();
	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec
	gr6 = [--ar5];									// Pointer to Maximum
	
	gr0 =2 with gr5 >>=3;							// nSize in 64-bit longs
	gr4 =80808080h;
	nb1 =gr4;
	f1cr=gr4;
	wtw;
	
	ar4 = _VEC_TmpBuffer64_G;
	delayed call vec_MaxVal;
		ar6=_VEC_TmpBuffer16_G;
	
	delayed call vec_MaxVal_v8nm8s;
		ar0=ar6;
		nul;

	[gr6]=gr7;							
	POP_REGS();
return;
.wait;


	

end ".text_nmplv";
