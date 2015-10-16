//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/07/13 14:19:56 $
//
//! \if file_doc
//!
//! \file   
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
extern vec_MaxVal:label;


begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////


//! \fn void VEC_MaxVal (nm64s63b *pSrcVec, int nSize, int64b &nMaxValue) 
//!
//! \perfinclude _VEC_MaxVal__FPliRl.html

global _VEC_MaxVal__FPliRl :label;
global _void._.8.8VEC_MaxVal.1long._.0.9._int.9._long._.6.2 :label;
<_VEC_MaxVal__FPliRl>
<_void._.8.8VEC_MaxVal.1long._.0.9._int.9._long._.6.2>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec (nSize in 64-bit longs)
	ar6 = [--ar5];									// Pointer to Maximum
	
	gr0 = 2;
	gr4 = 0h;									
	nb1 = gr4;
	f1crh= 80000000h;
	f1crl= 00000000h;
	wtw;
	
	delayed call vec_MaxVal;
		ar4= _VEC_TmpBuffer64_G;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar0,gr0;
	
return;
.wait;






	

end ".text_nmplv";
