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
extern	_nmppsTmpBuffer64_G_: long;
extern	_nmppsTmpBuffer16_G_: long;
extern vec_MaxVal:label;

macro FAST_MAX(r0,r1,rMax)
	with r0=r0-r1;		
	with rMax=r0 A>>31;
	with r0=r0 and not rMax;
	with rMax=r0+r1;
end FAST_MAX;




begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////


//! \fn void nmppsMax_32s31b(nm32s *pSrcVec, int nSize, int &nMaxValue) 
//!
//! \perfinclude _nmppsMax_32s31b.html

global _nmppsMax_32s31b:label;
<_nmppsMax_32s31b>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec
	gr6 = [--ar5];									// Pointer to Maximum
	
	gr0 = 2;
	gr4 = 80000000h with gr5 >>=1;					// nSize in 64-bit longs
	nb1 = gr4;
	f1cr= gr4;
	wtw;
	
	ar4= _nmppsTmpBuffer64_G_;
	delayed call vec_MaxVal;
		ar6=_nmppsTmpBuffer16_G_;								// 2xMaximum

	gr0=[ar6++];
	gr4=[ar6++];
	FAST_MAX(gr0,gr4,gr7);
	[gr6]=gr7;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar0,gr0;
	
return;
.wait;






	

end ".text_nmplv";
