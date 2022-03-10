//------------------------------------------------------------------------
//
//  $Workfile:: nmppirgb_y.asm             $
//
//  <nmpli>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   nmppirgb_y.asm
//! \author S. Svechnikov
//! \brief  Преобразование из RGB в Gray
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmpli"

rgbMatr: long[8]=(// 0.299=4c8b,   0.587=9646,   0.114=1d2f 
     1d2fhl,9646hl,4c8bhl,0l,
     1d2f00000000hl,964600000000hl,4c8b00000000hl,0l);
RamL: long=(8080808080808080hl);


    //--------------------------------------------------------------------
    //! \fn void nmppiRGB32ToGray(RGB32_nm8u * pRGB, nm32s* pDstGray, int nSize);
	//!
	//! \perfinclude _nmppiRGB32ToGray__F10RGB32_nm8uPPii.html
    //--------------------------------------------------------------------

global _nmppiRGB32ToGray_8u32s:label;
<_nmppiRGB32ToGray_8u32s>
vr=0l; skip job;



    //--------------------------------------------------------------------
    //! \fn void nmppiRGB32ToGray(RGB32_nm8u * pRGB, nm32u* pDstGray, int nSize);
	//!
	//! \perfinclude _nmppiRGB32ToGray__F10RGB32_nm8uPPUii.html
    //--------------------------------------------------------------------


global _nmppiRGB32ToGray_8u32u:label;
<_nmppiRGB32ToGray_8u32u>
vr=80000000800000hl;
<job>  ar5=ar7-2;
  push ar0,gr0 with gr7=true;push ar1,gr1 with gr7<<=31;

  sb=2020202h;  // 8x8  on X port
  nb1=gr7;      // 2x32 on Y port
  ar0=rgbMatr;
//  vrl=800000h;  // rgbMatr (0+1+2)*!28
//  vrh=800000h;  // rgbMatr (4+5+6)*128
.branch;
  rep 8 wfifo=[ar0++],ftw;
  push ar2,gr2;  push ar6,gr6;
  ar1=[--ar5];  //  SRC: bytes b,g,r,0,...
  ar6=[--ar5];  //  Dst
  gr5=[--ar5];  //  nSize
.wait; nb1=gr7; wtw; .branch;
   ar2=RamL with gr5>>=6;  // rep 32 counter
   if =0 skip fin;
   rep 32 ram=[ar2];  

L0: label;
   gr2=L0 with gr5--;
//------------------ here 132 ticks ----------------
<L0> if > delayed goto gr2 with gr5--;
   rep 32 data=[ar1++] with data xor ram;
   rep 32 with vsum,afifo,vr;
   rep 32 [ar6++]=afifo;
// ---------------- 1 tick for 1 pixel -------------
<fin>
  pop ar6,gr6;pop ar2,gr2; pop ar1,gr1; pop ar0,gr0;
  return;
end ".text_nmpli";