//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   CharShortAccess.asm
//! \author ������ �������
//! \brief  ������� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

begin ".text_nmplv"

//! \fn uint8u nmppsGet_8u(nm8u *pVec, int nIndex) 
//!
//! \perfinclude _nmppsGet_8u.html

global _nmppsGet_8u:	label;
<_nmppsGet_8u>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	gr0 = gr7>>2;
	gr7 = [ar0+=gr0] with gr0=gr7<<30;
	with gr0>>=28;
	gr0++;
	gr0++;
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;

	delayed return with	gr7<<=24;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7<<=16;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7<<=8;
		gr7 >>=24;
		nul;
		nul;
	delayed return with	gr7 >>=24;
		nul;
		nul;
		nul;
.wait;




end ".text_nmplv";
