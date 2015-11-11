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
extern	_nmppsTmpBuffer64_G_: long;
extern	_nmppsTmpBuffer16_G_: long;
extern vec_MaxVal:label;


begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////


//! \fn void nmppsMax_64s(nm64s63b *pSrcVec, int nSize, int64b &nMaxValue) 
//!
//! \perfinclude _nmppsMax_64s.html

global _nmppsMax__FPliRl_ :label;
global _nmppsMax_64s:label;
<_nmppsMax_64s>
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
		ar4= _nmppsTmpBuffer64_G_;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar0,gr0;
	
return;
.wait;






	

end ".text_nmplv";
