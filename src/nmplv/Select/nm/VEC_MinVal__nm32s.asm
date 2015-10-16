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
extern vec_MinVal:label;

macro FAST_MIN(r0,r1,rMin)
	with r0=r0-r1;		
	with rMin=r0 A>>31;
	with r0=r0 and rMin;
	with rMin=r0+r1;
end FAST_MIN;



begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////


//! \fn void VEC_MinVal (nm32s *pSrcVec, int nSize, int &nMinValue) 
//!
//! \perfinclude _VEC_MinVal__FPiiRi.html

global _VEC_MinVal__FPiiRi :label;
global _void._.8.8VEC_MinVal.1int._.0.9._int.9._int._.6.2 :label;
<_VEC_MinVal__FPiiRi>
<_void._.8.8VEC_MinVal.1int._.0.9._int.9._int._.6.2>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec
	gr6 = [--ar5];									// Pointer to Minimum
	
	gr0 = 2;
	gr4 = 80000000h with gr5 >>=1;					// nSize in 64-bit longs
	nb1 = gr4;
	f1cr= gr4;
	wtw;
	
	ar4= _VEC_TmpBuffer64_G;
	delayed call vec_MinVal;
		ar6=_VEC_TmpBuffer16_G;								// 2xMinimum

	gr0=[ar6++];
	gr4=[ar6++];
	FAST_MIN(gr0,gr4,gr7);
	[gr6]=gr7;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar0,gr0;
	
return;
.wait;






	

end ".text_nmplv";
