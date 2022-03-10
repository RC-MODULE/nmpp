//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   GetMax.asm
//! \author ������ �������
//! \brief  �������������� �������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vMinMax.h"
import from macros.mlb;
extern	_nmppsTmpBuffer64_G_: long;
extern	_nmppsTmpBuffer16_G_: long;
extern vec_MinVal_v4nm16s:label;
extern vec_MinVal:label;




begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMin_16s15b(nm16s *pSrcVec, int nSize, int16b &nMinValue) 
//!
//! \perfinclude _nmppsMin_16s15b.html

global _nmppsMin_16s15b:label;
<_nmppsMin_16s15b>
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
	ar4 = _nmppsTmpBuffer64_G_;
	delayed call vec_MinVal;
		ar6=_nmppsTmpBuffer16_G_;								// 4xMinimum

	delayed call vec_MinVal_v4nm16s;
		ar0=ar6;
		nul;

	[gr6]=gr7;
	POP_REGS();
return;
.wait;




	

end ".text_nmplv";
