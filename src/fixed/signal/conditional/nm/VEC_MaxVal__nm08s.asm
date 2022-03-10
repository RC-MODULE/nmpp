//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
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
extern vec_MaxVal_v8nm8s:label;
extern vec_MaxVal:label;


begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsMax_8s7b(nm8s *pSrcVec, int nSize, int8b &nMaxValue) 
//!
//! \perfinclude _nmppsMax_8s7b.html


global _nmppsMax_8s7b:label;
<_nmppsMax_8s7b>

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
	
	ar4 = _nmppsTmpBuffer64_G_;
	delayed call vec_MaxVal;
		ar6=_nmppsTmpBuffer16_G_;
	
	delayed call vec_MaxVal_v8nm8s;
		ar0=ar6;
		nul;

	[gr6]=gr7;							
	POP_REGS();
return;
.wait;


	

end ".text_nmplv";
