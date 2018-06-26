//------------------------------------------------------------------------
//
//  $Workfile:: Swap.as $
//
//  чЕЛФПТОП-НБФТЙЮОБС ВЙВМЙПФЕЛБ
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Split.asm
//! \author уЕТЗЕК уЧЕЮОЙЛПЧ
//! \brief  жХОЛГЙЙ ЙОЙГЙБМЙЪБГЙЙ Й ЛПРЙТПЧБОЙС.
//!
//! \endif
//!
//------------------------------------------------------------------------

data ".data_nmplv_L"

matr1: word [18]=(0,0,
 00001h,0000h,    // 0
 0000h,0000h,     // 1
 10000h,0000h,    // 2
 0,0,             // 3
 //---------------
 0000h,00001h,    // 4
 0000h,0000h,     // 5
 0000h,10000h,    // 6
 0000h,0000h      // 7
 );
end ".data_nmplv_L";
begin ".text_nmplv"

extern vec_Mul2D2W4_AddVr: label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSplit_16s(nm16s* src, nm16s* dst1, nm16s* dst2, int size);
//!
//! \perfinclude nmppsSplit_16s.html

global _nmppsSplit_16s: label;
<_nmppsSplit_16s>
.branch;
   nb1=80008000h;  // 4 РП 16 ОБ afifo
   sb=20002h;     // 4 РП 16 ОБ ЧИПДЕ X
   vr=0;
   f1cr=0;
   ar5 = ar7-2;
   push ar6,gr6;
   push ar0,gr0 with gr0=false;
   push ar1,gr1 with gr0++; // gr0=1
   push ar2,gr2 with gr0<<=2; // gr0=4
   push ar3,gr3 with gr1=gr0; // gr1=4
   push ar4,gr4 with gr6=gr0>>1; // gr6=2
   ar0 = [--ar5]; // psrc
   gr3=ar0;
   ar6 = [--ar5]with gr4=gr3+1; // pdst0 ( ЮЈФОЩЕ )
   ar3 = [--ar5]with gr4++; // pdst1 ( ОЕЮЈФОЩЕ )
   gr5 = [--ar5]; // src size (bytes)
   ar1=gr4 with gr5>>=4;
   delayed call vec_Mul2D2W4_AddVr;
   ar4=matr1+2;
//========================================= odd
   ar6=ar3; ar0=gr3; ar1=gr4;
   delayed call vec_Mul2D2W4_AddVr;
   ar4=matr1;
//=========================================
<fin>
   pop ar4,gr4;
   pop ar3,gr3;
   pop ar2,gr2;
   pop ar1,gr1;
   pop ar0,gr0;
   pop ar6,gr6;
   return;
.wait;   
end ".text_nmplv";
/*
size     ticks   for 1 dbl
400      502     1.961
800      807     1.576
1000     1414    1.381
2000     2632    1.285
4000     5065    1.237
8000     9927    1.212
10000    19656   1.200
ticks=198+1.188*N ЗДЕ N ЮЙУМП dbl ОБ ЧИПДЕ
*/
