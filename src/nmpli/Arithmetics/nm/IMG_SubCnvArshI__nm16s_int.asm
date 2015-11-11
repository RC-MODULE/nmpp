//------------------------------------------------------------------------
//
//  $Workfile:: Sub32_16.ASM $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   Sub32_16.asm
//! \author Сергей Свечников
//! \brief  Преобразование с вычитанием и с форточкой.
//!
//! \endif
//!
//------------------------------------------------------------------------
global _IMG_SubConvertRShiftI__FPSsiPiiiii: label;
global _void._.8.8IMG_SubConvertRShiftI.1short._.0.9._int.9._int._.0.9._int.9._int.9._int.9._int.2 :label;
 import from macros.mlb;
fin_add: label;

begin ".text_nmpli"

AA: label;
BB: label;
CC: label;
DD: label;
SH_n: label;
no_remainder: label;
sh_all: label;
matrix4:word[18]=( 0,0,1,0,0,0,10000h,0,
                   0,0,0,1,0,0,0,10000h,  0,0);
matrptr:word[2];


    //--------------------------------------------------------------------
    //! \fn void IMG_SubConvertRShiftI(nm16s* pSrcDstImg,  int nSrcDstStride,  nm32s* pSrcImg, int nSrcStride, int nShift, int nWidth, int nHeight)
	//!
//! \perfinclude _IMG_SubConvertRShiftI__FPSsiPiiiii.html
    //--------------------------------------------------------------------

<_IMG_SubConvertRShiftI__FPSsiPiiiii>
<_void._.8.8IMG_SubConvertRShiftI.1short._.0.9._int.9._int._.0.9._int.9._int.9._int.9._int.2>
   ar5 = ar7 - 2;
   PUSH_REGS();
   ar4=[--ar5];	 // dst16
   gr4=[--ar5];  // stride16 (pixels)
   ar0=[--ar5];  // src32
   gr0=[--ar5];	 // stride32 (pixels)
   gr7=[--ar5]with gr3=false;	 // shifts32
   gr5=[--ar5]with gr3++;	     // W width	(pixels)
   gr6=[--ar5]with gr3++;	     // H height , gr3=2
  
  gr1=20002h with gr7<<=6;   // gr1=instruction gr3<<=0

  if =0 delayed goto sh_all;
  ar6=matrix4+2;  // берём младшие 16р. без сдвига,sb=20002
  ar6=matrix4;    // делаем регистр sb, настроенный на shift32
  gr1=5010101bh;  // instruction: nul with gr3<<=0
  gr2=gr3 with gr1=gr1 or gr7; // do instruction gr3<<=(shift32)
  [SH_n]=gr1;     // modify instruction to: gr3<<=shift32
  nul;nul;nul;nul;// don't remove this four nuls;
<SH_n> nul;       // исполнение инструукции gr3=2 << shift32
  gr1=gr3+gr2;    // gr3=2 + (2 << shift32)

<sh_all>
   [matrptr]=ar6;
   [AA+1]=gr1;    // modify instruction sb=0;
   [BB+1]=gr1;    // modify instruction sb=0;
   ar5=80008000h; // Y=4 by 16 bits in a word64
   nb1=ar5;
   wtw;
     
    gr2=31 with gr5=gr5>>2;  // W в четвёрках пикселей
    gr2=gr5 and gr2;  // new rep count
    if =0 delayed goto no_remainder with gr5<<=1;
    ar3=CC;  // remainder does not exists
    ar3=BB with gr2--;
    gr2<<=13;      // rep counter for additional vector command
    gr1=94140018h; //rep 1 data=[ar0++gr0],ftw with vsum ,data,0;
    gr3=9450001ch with gr1 = gr1 or gr2;//rep 1 data=[ar1++gr1] with vsum ,data,afifo;
    [DD-1]=gr1 with gr3 = gr3 or gr2;
    gr1=9c90181ch;//rep 1 data=[ar2++] with data-afifo;
    [DD+2]=gr3 ;
    gr3=9f100000h with gr1 = gr1 or gr2;//rep 1 [ar4++]=afifo;
    [DD+6]=gr1 with gr3 = gr3 or gr2;
    [DD+7]=gr3;
<no_remainder>
    gr1=4 with gr4-=gr5;   // (stride16 в словах)-(W в словах)
    gr5>>=6;     // W (count of rep 32 for result)
       
<LinesLoop>
     push ar0,gr0;
     ar1=ar0+2 with gr0=gr1;
     ar2=ar4 with gr7=gr5;
     if =0 goto ar3;

<AA> sb=0;// this instruction is modified; don't edit it!;
     ar6=[matrptr];
     rep 8 wfifo=[ar6++], ftw;
     WTW_REG( ar5);                                    //
     rep 32 data=[ar0++gr0],ftw with vsum ,data,0;
     WTW_REG( ar5);                                    //
     rep 32 data=[ar1++gr1] with vsum ,data,afifo;
     sb=30003h with gr7--;
     if <>0 delayed goto AA;                           //
     rep 32 data=[ar2++] with data-afifo;
     rep 32 [ar4++]=afifo;
// here  line finish
    goto ar3;  // to BB or to CC

<BB>sb=0;// this instruction is modified; don't edit it;
     ar6=[matrptr];
     rep 8 wfifo=[ar6++], ftw;
     WTW_REG( ar5);                                    //
     rep 1 data=[ar0++gr0],ftw with vsum ,data,0;
<DD> WTW_REG( ar5);                                    //
     rep 1 data=[ar1++gr1] with vsum ,data,afifo;
     sb=30003h;
     rep 1 data=[ar2++] with data-afifo;
     rep 1 [ar4++]=afifo; 
<CC> // next line computing
    pop ar0,gr0;
	nul;
    ar0=ar0+gr0;
    ar4=ar4+gr4 with gr6--;  // Height--;
    if <>0 delayed goto LinesLoop;
    nul;nul;
 <fin_add>

   POP_REGS();
   return;
end ".text_nmpli";
