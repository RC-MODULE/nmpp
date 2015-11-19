//------------------------------------------------------------------------
//
//  $Workfile:: Convert1to2s.a $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   Convert1to2.asm
//! \author ������ ������� 
//! \brief  ������� �������������� ��������� �������.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vConvert.h"
//-----------------------------------------------------------------------------
data ".data_nmplv_L"
	w_nmppsConvert_L_: long[128] = (
		3hl, 30hl, 300hl, 3000hl, 30000hl, 300000hl, 3000000hl, 30000000hl,
		300000000hl, 3000000000hl, 30000000000hl, 300000000000hl,
		3000000000000hl, 30000000000000hl, 300000000000000hl, 3000000000000000hl,
		0hl dup 16,
		0Chl, 0C0hl, 0C00hl, 0C000hl, 0C0000hl, 0C00000hl, 0C000000hl, 0C0000000hl,
		0C00000000hl, 0C000000000hl, 0C0000000000hl, 0C00000000000hl,
		0C000000000000hl, 0C0000000000000hl, 0C00000000000000hl, 0C000000000000000hl,
		0hl dup 32,
		3hl, 30hl, 300hl, 3000hl, 30000hl, 300000hl, 3000000hl, 30000000hl,
		300000000hl, 3000000000hl, 30000000000hl, 300000000000hl,
		3000000000000hl, 30000000000000hl, 300000000000000hl, 3000000000000000hl,
		0hl dup 16,
		0Chl, 0C0hl, 0C00hl, 0C000hl, 0C0000hl, 0C00000hl, 0C000000hl, 0C0000000hl,
		0C00000000hl, 0C000000000hl, 0C0000000000hl, 0C00000000000hl,
		0C000000000000hl, 0C0000000000000hl, 0C00000000000000hl, 0C000000000000000hl);
end ".data_nmplv_L";
data ".data_nmplv_G"
	w_nmppsConvert_G_: long[32];
end ".data_nmplv_G";
//-----------------------------------------------------------------------------
import from macros.mlb;
//-----------------------------------------------------------------------------
begin ".text_nmplv"

//! \fn void nmppsConvert_1s2s*(nm1* pSrcVec, nm2s* pDstVec, int nSize)
//!
//! \perfinclude nmppsConvert_1s2s.html


global _nmppsConvert_1s2s:label;
<_nmppsConvert_1s2s>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar4, gr4;
	push ar5, gr5  with gr4 = true;

	ar0 = [--ar5];		//Source buffer.
	ar1 = [--ar5];		//Result buffer.
	gr7 = [--ar5];		//Size of input buffer in bits.
	
	ar2 = ar1+2;
	gr1 = 4;
	gr2 = 4;


	nb1 = gr4 with gr7 >>= 11;
	sb  = 0aaaaaaaahl;
	ar5 = w_nmppsConvert_L_ ;
	gr5 = ar5 with gr7--;
	rep 32 wfifo = [ar5++], ftw;
	WTW_REG(gr4);
	if =0 delayed goto lab_nmppsConvert_2_ with gr7--;
		rep 32 wfifo = [ar5++], ftw;
		nul;

<lab_nmppsConvert_1_>
	rep 32 data,ram = [ar0++] with vsum, data, 0;
	WTW_REG(gr4);
	rep 32 wfifo = [ar5++], ftw with vsum, shift ram, afifo;
	WTW_REG(gr4);
	rep 32 [ar1++gr1] = afifo;
	rep 32 wfifo = [ar5++], ftw with vsum, ram, 0;
	WTW_REG(gr4);
	ar5 = gr5;
	rep 32 wfifo = [ar5++], ftw with vsum, shift ram, afifo;
	WTW_REG(gr4);
	if > delayed goto lab_nmppsConvert_1_ with gr7--;	
		rep 32 [ar2++gr2] = afifo;
		rep 32 wfifo = [ar5++], ftw;

<lab_nmppsConvert_2_>
	rep 32 ram = [ar0++] with vsum, data, 0;
	WTW_REG(gr4);
	rep 32 wfifo = [ar5++], ftw with vsum, shift ram, afifo;
	WTW_REG(gr4);
	rep 32 [ar1++gr1] = afifo;
	rep 32 wfifo = [ar5++], ftw with vsum, ram, 0;
	WTW_REG(gr4);
	rep 32 with vsum, shift ram, afifo;
	rep 32 [ar2++gr2] = afifo;

	pop ar5, gr5;
	pop ar4, gr4;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
.wait;
//////////////////////////////////////////////////////////////////////
end ".text_nmplv";
//********************************************************************/
//		END OF FILE vConvert1to2.asm                                     */
//********************************************************************/