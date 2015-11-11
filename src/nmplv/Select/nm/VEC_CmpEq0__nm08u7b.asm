//------------------------------------------------------------------------
//
//  $Workfile:: BoolConvert8to1.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   BoolConvert8to1.asm
//! \author Сергей Ландышев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

    // \addtogroup nmppsCmpZero_
    // \brief Сравнивает элементы массива с нулевым значением. 
	//
	//\f[
	//pDstVec[i] = \left\{ {\begin{array}{*{20}c}
	//   1 & if & pSrcVec[i] > 0 \or pSrcVec[i] = -1  \\
	//   0 & if & pSrcVec[i] < -1 \or pSrcVec[i] = 0  \\
	//\end{array}} \right.,\,\,\,\,if\,\,invFlag = 0
	//\f]
	//
	//\f[
	//pDstVec[i] = \left\{ {\begin{array}{*{20}c}
	//    0 & if & pSrcVec[i] > 0 \or pSrcVec[i] =  -1  \\
	//    1 & if & pSrcVec[i] < -1 \or pSrcVec[i] = 0  \\
	//\end{array}} \right.,\,\,\,\,if\,\,invFlag =  - 1
	//\f]
    //
	// \param pSrcVec  Входной вектор.
    // \param nSize    Размер векторов в элементах.
	// \param nInvFlag Флаг инверсии результирующего бита.\n
    // \retval pDstVec Результирующий бинарный вектор.
	// \return \e void 
    //
    //  

data ".data_nmplv_L"
global	_w_BoolConvert_L:	long[64] = (
		0000000000000001hl, 0000000000000002hl,
		0000000000000004hl, 0000000000000008hl,
		0000000000000010hl, 0000000000000020hl,
		0000000000000040hl, 0000000000000080hl,
		0000000000000100hl, 0000000000000200hl,
		0000000000000400hl, 0000000000000800hl,
		0000000000001000hl, 0000000000002000hl,
		0000000000004000hl, 0000000000008000hl,
		0000000000010000hl, 0000000000020000hl,
		0000000000040000hl, 0000000000080000hl,
		0000000000100000hl, 0000000000200000hl,
		0000000000400000hl, 0000000000800000hl,
		0000000001000000hl, 0000000002000000hl,
		0000000004000000hl, 0000000008000000hl,
		0000000010000000hl, 0000000020000000hl,
		0000000040000000hl, 0000000080000000hl,
		0000000100000000hl, 0000000200000000hl,
		0000000400000000hl, 0000000800000000hl,
		0000001000000000hl, 0000002000000000hl,
		0000004000000000hl, 0000008000000000hl,
		0000010000000000hl, 0000020000000000hl,
		0000040000000000hl, 0000080000000000hl,
		0000100000000000hl, 0000200000000000hl,
		0000400000000000hl, 0000800000000000hl,
		0001000000000000hl, 0002000000000000hl,
		0004000000000000hl, 0008000000000000hl,
		0010000000000000hl, 0020000000000000hl,
		0040000000000000hl, 0080000000000000hl,
		0100000000000000hl, 0200000000000000hl,
		0400000000000000hl, 0800000000000000hl,
		1000000000000000hl, 2000000000000000hl,
		4000000000000000hl, 8000000000000000hl);
global	_buf_BoolConvert_L:	long[64];
global	_mask_table: word[32] = (
		0ffffffffh, 000000001h, 000000003h, 000000007h,
		00000000fh, 00000001fh, 00000003fh, 00000007fh,
		0000000ffh, 0000001ffh, 0000003ffh, 0000007ffh,
		000000fffh, 000001fffh, 000003fffh, 000007fffh,
		00000ffffh, 00001ffffh, 00003ffffh, 00007ffffh,
		0000fffffh, 0001fffffh, 0003fffffh, 0007fffffh,
		000ffffffh, 001ffffffh, 003ffffffh, 007ffffffh, 
		00fffffffh, 01fffffffh, 03fffffffh, 07fffffffh);
end ".data_nmplv_L";
data ".data_nmplv_G"
global	_w_BoolConvert_G:	long[64] = (
		0000000000000001hl, 0000000000000002hl,
		0000000000000004hl, 0000000000000008hl,
		0000000000000010hl, 0000000000000020hl,
		0000000000000040hl, 0000000000000080hl,
		0000000000000100hl, 0000000000000200hl,
		0000000000000400hl, 0000000000000800hl,
		0000000000001000hl, 0000000000002000hl,
		0000000000004000hl, 0000000000008000hl,
		0000000000010000hl, 0000000000020000hl,
		0000000000040000hl, 0000000000080000hl,
		0000000000100000hl, 0000000000200000hl,
		0000000000400000hl, 0000000000800000hl,
		0000000001000000hl, 0000000002000000hl,
		0000000004000000hl, 0000000008000000hl,
		0000000010000000hl, 0000000020000000hl,
		0000000040000000hl, 0000000080000000hl,
		0000000100000000hl, 0000000200000000hl,
		0000000400000000hl, 0000000800000000hl,
		0000001000000000hl, 0000002000000000hl,
		0000004000000000hl, 0000008000000000hl,
		0000010000000000hl, 0000020000000000hl,
		0000040000000000hl, 0000080000000000hl,
		0000100000000000hl, 0000200000000000hl,
		0000400000000000hl, 0000800000000000hl,
		0001000000000000hl, 0002000000000000hl,
		0004000000000000hl, 0008000000000000hl,
		0010000000000000hl, 0020000000000000hl,
		0040000000000000hl, 0080000000000000hl,
		0100000000000000hl, 0200000000000000hl,
		0400000000000000hl, 0800000000000000hl,
		1000000000000000hl, 2000000000000000hl,
		4000000000000000hl, 8000000000000000hl);
global	_buf_BoolConvert_G:	long[64];
end ".data_nmplv_G";
//////////////////////////////////////////////////////////////////////
import from macros.mlb;
//////////////////////////////////////////////////////////////////////

begin ".text_nmplv"




//--------------------------------------------------------------------
//! \fn void nmppsCmpEq0_8u(nm8u7b* pSrcVec, nm1* pDstVec, int nSize, int nTrueFlag);
//!
//! \perfinclude _nmppsCmpEq0__FUcP3nm1Pii_.html
//--------------------------------------------------------------------

    global _nmppsCmpEq0_8u:	label;
global _nmppsCmpEq0_8u:label;
<_nmppsCmpEq0_8u>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0 with gr0 = false;
	push ar1, gr1 with gr0++;
	push ar2, gr2 with gr0 <<= 4;	//gr0 = 16.
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
	sb = 02020202h with gr1 >>= 21;	//8 rows.
	if =0 delayed goto lab_BoolConvert8to1_0 with gr4 >>= 11;
		ar5 = _w_BoolConvert_L with gr5;
	gr4++ noflags;
<lab_BoolConvert8to1_0>
	if > delayed goto lab_BoolConvert8to1_1 with gr5 = true;
		ar1 = _buf_BoolConvert_L;
	ar5 = _w_BoolConvert_G;
	ar1 = _buf_BoolConvert_G;
<lab_BoolConvert8to1_1>
	nb1 = gr5;						//64 cols.
	ar4 = ar5;
	rep 32 wfifo = [ar4++], ftw;
	f1cr = 0fefefefeh;
	gr4--;
	if =0 delayed goto lab_BoolConvert8to1_3 with gr4--;
		WTW_REG(gr5);
<lab_BoolConvert8to1_2>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	WTW_REG(gr5);
	ar0-=510;	//return to next vector.
.repeat 2;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;	//return to next vector.
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;	
.repeat 3;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;	//return to next vector.
.endrepeat;
	ar4 = ar5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	ar0-=14;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 [ar6++] = afifo;
	if > delayed goto lab_BoolConvert8to1_2 with gr4--;
		WTW_REG(gr5);
<lab_BoolConvert8to1_3>
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, vr;
	WTW_REG(gr5);
	ar0-=510;
.repeat 2;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;
.endrepeat;
	rep 32 wfifo = [ar4++], ftw;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;	
.repeat 3;
	rep 32 data = [ar0++gr0], ftw with vsum, activate data, afifo;
	WTW_REG(gr5);
	ar0-=510;	//return to next vector.
.endrepeat;
	ar4 = ar1 with gr1;
	if =0 delayed goto lab_BoolConvert8to1_5 with gr5 = gr1 << 27;
		gr1 >>= 5;
		gr5;
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar4++] = afifo;
<lab_BoolConvert8to1_4>
	if <>0 delayed goto lab_BoolConvert8to1_41 with gr1--;
		ar5 = _mask_table;
	gr1--;
<lab_BoolConvert8to1_41>
	if < goto lab_BoolConvert8to1_42;
<lab_BoolConvert8to1_411>
	if > delayed goto lab_BoolConvert8to1_411 with gr1--;
		gr4 = [ar1++];
		[ar6++] = gr4;
<lab_BoolConvert8to1_42>
	gr4 = [ar1++] with gr5 >>= 27;
	gr5 = [ar5+=gr5];
	gr4 = gr4 and gr5;
	delayed goto lab_BoolConvert8to1_6 with gr4 and gr2;
		[ar6++] = gr4;
		nul;
<lab_BoolConvert8to1_5>
	rep 32 data = [ar0++gr0] with vsum, activate data, afifo;
	rep 32 [ar6++] = afifo;
<lab_BoolConvert8to1_6>
	pop ar6, gr6;
	pop ar5,gr5;
	pop ar4, gr4;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
.wait;
end ".text_nmplv";
