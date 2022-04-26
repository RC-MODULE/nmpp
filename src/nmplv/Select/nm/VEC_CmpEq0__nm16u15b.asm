//------------------------------------------------------------------------
//
//  $Workfile:: BoolConvert16to1.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   BoolConvert16to1.asm
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
//////////////////////////////////////////////////////////////////////
//import from macros.mlb;
//////////////////////////////////////////////////////////////////////
begin ".text_nmplv"

//! \fn void nmppsCmpEq0_16u15b(nm16u15b* pSrcVec, nm1* pDstVec, int nSize, int nTrueFlag);
//!
//! \perfinclude _nmppsCmpEq0_16u15b.html

global _nmppsCmpEq0_16u15b:label;
<_nmppsCmpEq0_16u15b>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0 with gr0 = false;
	push ar1, gr1 with gr0++;
	push ar2, gr2 with gr0 <<= 5;	//gr0 = 32.	
	push ar4, gr4;	
	push ar5,gr5;
	push ar6, gr6;
	ar0 = [--ar5];					//ar0 - source.
	ar6 = [--ar5];					//ar6 - dst.
	gr4 = [--ar5];					//gr4 - source size.
	gr2 = [--ar5];					//gr2 - invert flag.
	gr2--;
	ar2 = gr2;
	gr5 = ar6 with gr1 = gr4 << 21;		
	vr = ar2, gr2;
	sb = 00020002h with gr1 >>= 21;	//4 rows.
	if =0 delayed goto lab_BoolConvert16to1_0 with gr4 >>= 11;
		ar5 = _w_BoolConvert_L with gr5;
	gr4++ noflags;
<lab_BoolConvert16to1_0>
	if > delayed goto lab_BoolConvert16to1_1 with gr5 = true;
		ar1 = _buf_BoolConvert_L;
	ar5 = _w_BoolConvert_G;
	ar1 = _buf_BoolConvert_G;
<lab_BoolConvert16to1_1>
	nb1 = gr5;						//64 cols.
	ar4 = ar5;
	rep 32 wfifo = [ar4++], ftw,wtw;
	f1cr = 0fffefffeh;
	gr4--;
	if =0 goto lab_BoolConvert16to1_3 with gr4--;
		////WTW_REG_DEPRICATED(gr5);
<lab_BoolConvert16to1_2>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	//return to next vector.
.repeat 6;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	//return to next vector.
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	
.repeat 7;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	//return to next vector.
.endrepeat;
	ar4 = ar5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	ar0-=30;
	rep 32 wfifo = [ar4++], ftw,wtw;
	rep 32 [ar6++] = afifo;
	if > goto lab_BoolConvert16to1_2 with gr4--;
		////WTW_REG_DEPRICATED(gr5);
<lab_BoolConvert16to1_3>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;
.repeat 6;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	
.repeat 7;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	//WTW_REG_DEPRICATED(gr5);
	wtw;
	ar0-=1022;	//return to next vector.
.endrepeat;
	ar4 = ar1 with gr1;
	if =0 delayed goto lab_BoolConvert16to1_5 with gr5 = gr1 << 27;
		gr1 >>= 5;
		gr5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar4++] = afifo;
<lab_BoolConvert16to1_4>
	if <>0 delayed goto lab_BoolConvert16to1_41 with gr1--;
		ar5 = _mask_table;
	gr1--;
<lab_BoolConvert16to1_41>
	if < goto lab_BoolConvert16to1_42;
<lab_BoolConvert16to1_411>
	if > delayed goto lab_BoolConvert16to1_411 with gr1--;
		gr4 = [ar1++];
		[ar6++] = gr4;
<lab_BoolConvert16to1_42>
	gr4 = [ar1++] with gr5 >>= 27;
	gr5 = [ar5+=gr5];
	gr4 = gr4 and gr5;
	delayed goto lab_BoolConvert16to1_6 with gr4 and gr2;
		[ar6++] = gr4;
		nul;
<lab_BoolConvert16to1_5>
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar6++] = afifo;
<lab_BoolConvert16to1_6>
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
//		END OF FILE BoolConvert16to1.asm                                 */
//********************************************************************/
