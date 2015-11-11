//------------------------------------------------------------------------
//
//  $Workfile:: BoolConvert32to1.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   BoolConvert32to1.asm
//! \author Сергей Ландышев
//! \brief  Функции преобразования елементов вектора. 
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"
//////////////////////////////////////////////////////////////////////
extern _w_BoolConvert_L:		long;
extern _w_BoolConvert_G:		long;
extern _buf_BoolConvert_L:		long;
extern _buf_BoolConvert_G:		long;
extern _mask_table:			word;

import from macros.mlb;
begin ".text_nmplv"

//! \fn void  nmppsCmpEq0_32u(nm32u31b *pSrcVec, nm1 *pDstVec, int nSize, int nTrueFlag);
//!
//! \perfinclude _nmppsCmpEq0_32u.html

global _nmppsCmpEq0_32u:	label;
global _nmppsCmpEq0_32u:label;
<_nmppsCmpEq0_32u>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0 with gr0 = false;
	push ar1, gr1 with gr0++;
	push ar2, gr2 with gr0 <<= 6;	//gr0 = 64.
	push ar4, gr4;	
	push ar5,gr5;
	push ar6, gr6;
	ar0 = [--ar5];					//ar0 - source, gr7 = 7ffh.
	ar6 = [--ar5];					//ar6 - dst.
	gr4 = [--ar5];					//gr4 - source size.
	gr2 = [--ar5];
	gr2--;
	ar2 = gr2;
	vr = ar2, gr2;
	gr5 = ar6 with gr1 = gr4 << 21;
	sb = 2 with gr1 >>= 21;			//2 rows.
	if =0 delayed goto lab_BoolConvert32to1_0 with gr4 >>= 11;	//gr4 - counter.
		ar5 = _w_BoolConvert_L with gr5;
	gr4++ noflags;
<lab_BoolConvert32to1_0>
	if > delayed goto lab_BoolConvert32to1_1 with gr5 = true;
		ar1 = _buf_BoolConvert_L;	
	ar5 = _w_BoolConvert_G;
	ar1 = _buf_BoolConvert_G;
<lab_BoolConvert32to1_1>
	nb1 = gr5;						//64 cols.
	ar4 = ar5;
	rep 32 wfifo = [ar4++], ftw;
	f1cr = 0fffffffeh;
	gr4--;
	if =0 delayed goto lab_BoolConvert32to1_3 with gr4--;
		WTW_REG(gr5);
<lab_BoolConvert32to1_2>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	WTW_REG(gr5);
	ar0-=2046;	//return to next vector.
.repeat 14;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;	//return to next vector.
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;	
.repeat 15;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;	//return to next vector.
.endrepeat;
	ar4 = ar5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	ar0-=62;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 [ar6++] = afifo;
	if > delayed goto lab_BoolConvert32to1_2 with gr4--;
		WTW_REG(gr5);
<lab_BoolConvert32to1_3>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	WTW_REG(gr5);
	ar0-=2046;
.repeat 14;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0 ] with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;
.repeat 15;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=2046;	//return to next vector.
.endrepeat;
	ar4 = ar1 with gr1;
	if =0 delayed goto lab_BoolConvert32to1_5 with gr5 = gr1 << 27;
		gr1 >>= 5;
		gr5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar4++] = afifo; //Save afifo in temporary buffer.
<lab_BoolConvert32to1_4>
	if <>0 delayed goto lab_BoolConvert32to1_41 with gr1--;
		ar5 = _mask_table;
	gr1--;
<lab_BoolConvert32to1_41>
	if < goto lab_BoolConvert32to1_42;
<lab_BoolConvert32to1_411>
	if > delayed goto lab_BoolConvert32to1_411 with gr1--;
		gr4 = [ar1++];
		[ar6++] = gr4;
<lab_BoolConvert32to1_42>
	gr4 = [ar1++] with gr5 >>= 27;
	gr5 = [ar5+=gr5];
	gr4 = gr4 and gr5;
	delayed goto lab_BoolConvert32to1_6 with gr4 and gr2;
		[ar6++] = gr4;
		nul;
<lab_BoolConvert32to1_5>
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar6++] = afifo;
<lab_BoolConvert32to1_6>
	pop ar6, gr6;
	pop ar5,gr5;
	pop ar4, gr4;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
.wait;
//////////////////////////////////////////////////////////////////////
end ".text_nmplv";
//********************************************************************/
//		END OF FILE BoolConvert32to1.asm                                 */
//********************************************************************/