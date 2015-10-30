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
extern vec_MaxVal_v4nm16s:label;
extern vec_MaxVal:label;

begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMaxVal_16s(nm16s *pSrcVec, int nSize, int16b &nMaxValue) 
//!
//! \perfinclude _nmppsMaxVal_16s.html

global _nmppsMaxVal__FPSsiRi_ :label;
global _void._.8.8nmppsMaxVal_.1short._.0.9._int.9._int._.6.2 :label;
<_nmppsMaxVal_16s>
<_void._.8.8nmppsMaxVal_.1short._.0.9._int.9._int._.6.2>
.branch;
	ar5=sp-2;
	PUSH_REGS();
	ar0 = [--ar5];									// pSrcVec
	gr5 = [--ar5];									// nSize of pSrcVec
	gr6 = [--ar5];									// Pointer to Maximum
	
	gr0=2 with gr5 >>=2;							// nSize in 64-bit longs
	gr4 =80008000h;
	nb1 =gr4;
	f1cr=gr4;
	wtw;
	ar4 = _nmppsTmpBuffer64_G_;
	delayed call vec_MaxVal;
		ar6=_nmppsTmpBuffer16_G_;								// 4xMaximum

	delayed call vec_MaxVal_v4nm16s;
		ar0=ar6;
		nul;

	[gr6]=gr7;
	POP_REGS();
return;
.wait;






	

end ".text_nmplv";
