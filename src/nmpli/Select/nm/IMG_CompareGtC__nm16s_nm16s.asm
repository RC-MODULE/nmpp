//------------------------------------------------------------------------
//
//  $Workfile:: compare_gtc16. $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   Add36_16.asm
//! \author Сергей Свечников
//! \brief  Сравнение с порогом 16-разрядных пикселей. С ROI.
//!
//! \endif
//!
//------------------------------------------------------------------------
global _nmppiCompareGtC__FPSsiPSsiPSsii: label;
global _void._.8.8nmppiCompareGtC.1short._.0.9._int.9._short._.0.9._int.9._short._.0.9._int.9._int.2 :label;
import from macros.mlb;

begin ".text_nmpli"
     
    //--------------------------------------------------------------------
    //! \fn int nmppiCompareGtC(nm16s *pSrcImg, int nSrcStride, nm16s *pDstImg, int nDstStride, nm16s *pThreshold, int nWidth, int nHeight)
	//!
//! \perfinclude _nmppiCompareGtC__FPSsiPSsiPSsii.html
    //--------------------------------------------------------------------

<_nmppiCompareGtC__FPSsiPSsiPSsii>
<_void._.8.8nmppiCompareGtC.1short._.0.9._int.9._short._.0.9._int.9._short._.0.9._int.9._int.2>
   ar5 = ar7 - 2;
   PUSH_REGS();

AA: label;
BB: label;
CC: label;
no_remainder: label;

   ar0=[--ar5];  // src16
   gr0=[--ar5];	 // nSrcStride in word32
   ar4=[--ar5];	 // dst16
   gr4=[--ar5];	 // nDstStride word32   
   ar1=[--ar5];  // plThreshold
   gr5=[--ar5];  // W width	(pixels)
   gr6=[--ar5]with gr2=gr5>>7;    // gr6=H height, gr2=width/128

ar2=80000c00h;//!!  для отладки
   sb=20002h;
   ar5=80008000h with gr1=gr2<<6; 
   nb1=ar5 with gr0-=gr1;
   wtw;
   gr3=31 with gr5=gr5>>2;  // W в четвёрках пикселей
   ar3=CC with gr3=gr5 and gr3;  // new rep count
   f1cr=80008000h with gr4-=gr1;
   if <>0 goto with_remainder with gr3--;
   
.branch;
   ar6=gr2 with gr2--;
<AA> rep 32 ram=[ar0++];
     rep 32 data=[ar1] with ram-data;
     if > delayed goto AA with gr2--;
     rep 32 with not activate afifo;
     rep 32 [ar4++]=afifo;
     gr2=ar6;
     ar0=ar0+gr0 with gr6--;
     if <>0 delayed goto AA;
     ar4=ar4+gr4 with gr2--;
 <go_home>
   POP_REGS();
   return;
<with_remainder>
    gr7=9c180000h with gr3<<=13; // rep 1 ram=[ar0++];
    gr5=9050180eh with gr7=gr7 or gr3;//rep 1 data=[ar1]with ram-data
    [ar3++]=gr7 with gr5=gr5 or gr3;
    gr7=800012d0h; 
    [ar3++]=gr5 with gr7=gr7 or gr3;
    gr5=9f100000h;
    [ar3++]=gr7 with gr5=gr5 or gr3;
    [ar3++]=gr5 with gr3>>=12;
   gr3=gr3+1;
   gr3=gr3+1;
   ar5=BB with gr0-=gr3; 
   with gr2;
   if =0 delayed goto L1 with gr4-=gr3;  // remainder only
   ar6=gr2;
   with gr2--;
<BB> rep 32 ram=[ar0++];
     rep 32 data=[ar1] with ram-data;
     if > delayed goto ar5 with gr2--;
     rep 32 with not activate afifo;
     rep 32 [ar4++]=afifo;            
<CC> rep 1 ram=[ar0++];               //9c180000
     rep 1 data=[ar1] with ram-data;  //9050180e
     rep 1 with not activate afifo;   //800012d0
     rep 1 [ar4++]=afifo;             //9f100000
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
