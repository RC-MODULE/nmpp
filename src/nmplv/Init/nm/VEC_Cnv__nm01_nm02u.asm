//------------------------------------------------------------------------
//
//  $Workfile:: Convert1to2.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   Convert1to2.asm
//! \author Сергей Мушкаев 
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vConvert.h"
//-----------------------------------------------------------------------------
data ".data_nmplv_L"
	w_nmppsConvert_L_: long[128] = (
		1hl, 10hl, 100hl, 1000hl, 10000hl, 100000hl, 1000000hl, 10000000hl,
		100000000hl, 1000000000hl, 10000000000hl, 100000000000hl,
		1000000000000hl, 10000000000000hl, 100000000000000hl, 1000000000000000hl,
		0hl dup 16,
		4hl, 40hl, 400hl, 4000hl, 40000hl, 400000hl, 4000000hl, 40000000hl,
		400000000hl, 4000000000hl, 40000000000hl, 400000000000hl,
		4000000000000hl, 40000000000000hl, 400000000000000hl, 4000000000000000hl,
		0hl dup 32,
		1hl, 10hl, 100hl, 1000hl, 10000hl, 100000hl, 1000000hl, 10000000hl,
		100000000hl, 1000000000hl, 10000000000hl, 100000000000hl,
		1000000000000hl, 10000000000000hl, 100000000000000hl, 1000000000000000hl,
		0hl dup 16,
		4hl, 40hl, 400hl, 4000hl, 40000hl, 400000hl, 4000000hl, 40000000hl,
		400000000hl, 4000000000hl, 40000000000hl, 400000000000hl,
		4000000000000hl, 40000000000000hl, 400000000000000hl, 4000000000000000hl);
end ".data_nmplv_L";
data ".data_nmplv_G"
	w_nmppsConvert_G_: long[32];
end ".data_nmplv_G";
//-----------------------------------------------------------------------------
import from macros.mlb;
//-----------------------------------------------------------------------------
macro tail(N)
 	rep N data,ram = [ar0++],wtw with vsum, data, 0;
	rep N with vsum, shift ram, afifo;
	rep 32 wfifo = [ar5++], ftw,wtw;
	rep N [ar1++gr1] = afifo	with vsum, ram, 0;
	delayed goto ar4;	
		rep 32 wfifo = [ar5++], ftw,wtw ;
		rep N with vsum, shift ram, afifo;
		rep N [ar2++gr2] = afifo; 
end tail;
begin ".text_nmplv"

//! \fn void nmppsConvert_1u2u*(nm1* pSrcVec, nm2u* pDstVec, int nSize)
//!
//! \perfinclude nmppsConvert_1u2u.html


global _nmppsConvert_1u2u:label;
<_nmppsConvert_1u2u>
.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar4, gr4;
	push ar5, gr5 with gr4 = true;

	ar0 = [--ar5];		//Source buffer.
	ar1 = [--ar5];		//Result buffer.
	gr7 = [--ar5];		//Size of input buffer in bits.
	
	ar2 = ar1+2;
	gr1 = 4;
	gr2 = 4;

	
	nb1 = gr4;
	gr4 = gr7>>6;
	gr4<<=27;
	gr4>>=27;
	with gr7 >>= 11;
	sb = 0aaaaaaaahl;
	ar5 = w_nmppsConvert_L_ ;
	gr5 = ar5 with gr7;
	rep 32 wfifo = [ar5++], ftw, wtw;
	if =0 delayed goto lab_nmppsConvert_2_;
		rep 32 wfifo = [ar5++], ftw;
		gr7--;

<lab_nmppsConvert_1_>
	rep 32 data,ram = [ar0++],wtw with vsum, data, 0;
	rep 32 wfifo = [ar5++], ftw,wtw with vsum, shift ram, afifo;
	rep 32 [ar1++gr1] = afifo;
	rep 32 wfifo = [ar5++], ftw,wtw with vsum, ram, 0;
	ar5 = gr5;
	rep 32 wfifo = [ar5++], ftw,wtw with vsum, shift ram, afifo;
	if > delayed goto lab_nmppsConvert_1_ with gr7--;	
		rep 32 [ar2++gr2] = afifo;
		rep 32 wfifo = [ar5++], ftw;

<lab_nmppsConvert_2_>
	start_tail: label;
	end_tail: label;
	ar4 = start_tail	with gr4 <<=3;
	delayed goto ar4+gr4;
		nul;
		ar4 = end_tail;
<start_tail>
	delayed goto end_tail;
		wtw;nul;
	nul;nul;nul;nul;
	tail(1 );
	tail(2 );
	tail(3 );
	tail(4 );
	tail(5 );
	tail(6 );
	tail(7 );
	tail(8 );
	tail(9 );
	tail(10);
	tail(11);
	tail(12);
	tail(13);
	tail(14);
	tail(15);
	tail(16);
	tail(17);
	tail(18);
	tail(19);
	tail(20);
	tail(21);
	tail(22);
	tail(23);
	tail(24);
	tail(25);
	tail(26);
	tail(27);
	tail(28);
	tail(29);
	tail(30);
	tail(31);
<end_tail>
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