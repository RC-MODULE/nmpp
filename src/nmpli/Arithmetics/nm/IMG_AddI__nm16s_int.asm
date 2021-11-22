//------------------------------------------------------------------------
//
//  $Workfile:: add16_16.asm $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   Add36_16.asm
//! \author Сергей Свечников
//! \brief  Преобразование со сложением и с форточкой.
//!
//! \endif
//!
//------------------------------------------------------------------------
global _nmppiAddI__FPSsiPSsiii: label;
global _void._.8.8nmppiAddI.1short._.0.9._int.9._short._.0.9._int.9._int.9._int.2 :label;
 import from macros.mlb;
fin_add: label;

begin ".text_nmpli"
AA: label;
BB: label;
CC: label;
no_remainder: label;


    //--------------------------------------------------------------------
    //! \fn void nmppiAddI(nm16s* pSrcDstImg, int nSrcDstStride, nm16s *pSrcImg,  int nSrcStride, int nWidth, int nHeight)
    //! 
//! \perfinclude _nmppiAddI__FPSsiPSsiii.html
    //--------------------------------------------------------------------

<_nmppiAddI__FPSsiPSsiii>
<_void._.8.8nmppiAddI.1short._.0.9._int.9._short._.0.9._int.9._int.9._int.2>
   ar5 = ar7 - 2;
   PUSH_REGS();
   ar4=[--ar5];	 // dst16
   gr4=[--ar5];	 // nDstStride word32   
   ar0=[--ar5];  // src16
   gr0=[--ar5];	 // nSrcStride word32
   gr5=[--ar5];  // W width	(pixels)
   gr6=[--ar5]with gr2=gr5>>7;    // gr6=H height, gr2=width/128
   sb=20002h;
   ar5=80008000h with gr1=gr2<<6; 
   nb1=ar5 with gr0-=gr1;
   wtw;
   ar1=ar4 with gr4-=gr1;
   gr3=31 with gr5=gr5>>2;  // W в четвёрках пикселей
   ar3=CC with gr3=gr5 and gr3;  // new rep count
   if <>0 delayed goto with_remainder with gr1=gr4;
   ar5=AA with gr3--; // for remainder handling 
.branch;
   ar6=gr2 with gr2--;
<AA>if > delayed goto ar5 with gr2--;
     rep 32 data=[ar0++] with data;
     rep 32 data=[ar1++] with data+afifo;
     rep 32 [ar4++]=afifo;
     gr2=ar6;
     ar0=ar0+gr0 with gr6--;
     if <>0 delayed goto ar5;
     ar1=ar1+gr1;
     ar4=ar4+gr4 with gr2--;
 <fin_add>
   POP_REGS();
   return;
<with_remainder>
    gr7=9c101518h with gr3<<=13; // rep 1 data=[ar0++] with data;
    gr5=9c501b16h with gr7=gr7 or gr3;//rep 1 data=[ar1++]with afifo+data
    [ar3++]=gr7 with gr5=gr5 or gr3;
    gr7=9f100000h;
    [ar3++]=gr5 with gr7=gr7 or gr3;
    [ar3++]=gr7 with gr3>>=12;
   gr3=gr3+1;
   gr3=gr3+1;
   ar5=BB with gr0-=gr3; 
   with gr2;
   if =0 delayed goto L1 with gr4-=gr3;  // remainder only
   ar6=gr2 with gr1-=gr3;
   with gr2--;
<BB>
     if > delayed goto ar5 with gr2--;
     rep 32 data=[ar0++] with data;
     rep 32 data=[ar1++] with data+afifo;
     rep 32 [ar4++]=afifo;
<CC> rep 1 data=[ar0++] with data;         // 9c101518
     rep 1 data=[ar1++] with afifo+data;   // 9c501b16
     rep 1 [ar4++]=afifo; 
     gr2=ar6;
     ar0=ar0+gr0 with gr6--;
     if <>0 delayed goto ar5;
     ar1=ar1+gr1;
     ar4=ar4+gr4 with gr2--;
     nul;
   POP_REGS();
   return;
<L1>
delayed goto CC;
   ar5=CC;
end ".text_nmpli";
