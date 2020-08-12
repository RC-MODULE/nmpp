//------------------------------------------------------------------------
//
//  $Workfile:: Swap.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Split.asm
//! \author Сергей Свечников
//! \brief  Функции инициализации и копирования.
//!
//! \endif
//!
//------------------------------------------------------------------------
data ".data_nmplv_L"

matr1: word [10]=(0,0,
 00001h,0000h,    // 0
 0000h,0000h,     // 1
 0000h,00001h,    // 2
 0000h,0000h             // 3
 );
end ".data_nmplv_L";
begin ".text_nmplv"
extern vec_Mul2D2W2_AddVr: label;

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSplit_32s(const nm32s* src, nm32s* dst1, nm32s* dst2, int size);
//!
//! \perfinclude nmppsSplit_32s.html

global _nmppsSplit_32s: label;
<_nmppsSplit_32s>
.branch;
	nb1=80000000h;  // 4 по 16 на afifo
	sb=0002h;     // 4 по 16 на входе X
	vr=0;
	f1cr=0;
	ar5 = ar7-2;
	push ar6,gr6;
	push ar5,gr5;
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++; // gr0=1
	push ar2,gr2 with gr0<<=2; // gr0=4
	push ar3,gr3 with gr1=gr0; // gr1=4
	push ar4,gr4 with gr6=gr0>>1; // gr6=2
	ar0 = [--ar5]; // psrc
	gr3=ar0;
	ar6 = [--ar5]with gr4=gr3+1; // pdst0 ( чётные )
	ar3 = [--ar5]with gr4++; // pdst1 ( нечётные )
	gr5 = [--ar5]; // src size (bytes)
	ar1=gr4 with gr5>>=2;

	delayed call vec_Mul2D2W2_AddVr;
		ar4=matr1+2;

	//========================================= odd
	ar6=ar3; ar0=gr3; ar1=gr4;

	delayed call vec_Mul2D2W2_AddVr;
		ar4=matr1;
	//=========================================
	<fin>
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	pop ar5,gr5;
	pop ar6,gr6;
	return;
.wait;   
end ".text_nmplv";
/*
size     ticks   for 1 dbl
400      559     2.184
800      847     1.654
1000     1422    1.389
2000     2578    1.259
4000     4879    1.191
8000     9485    1.158
10000    18705   1.142
*/
