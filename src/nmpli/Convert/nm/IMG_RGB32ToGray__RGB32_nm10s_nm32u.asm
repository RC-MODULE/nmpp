//------------------------------------------------------------------------
//
//  $Workfile:: ConvertRGB32_nm10u_Gray_nm32s.asm             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   ConvertRGB32_nm10u_Gray_nm32s.asm
//! \author S. Mushkaev
//! \brief  Преобразование из RGB в Gray
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmpli"

// Коэффициенты преобразования RGB-> Gray в форате fixedpoint .16
tbl_w_RGB2Gray: long[8]=(
     00000000_00001d2fhl,// 0.114=1d2f
	 00000000_00009646hl,// 0.587=9646
	 00000000_00004c8bhl,// 0.299=4c8b
	 00000000_00000000hl,

     00001d2f_00000000hl,
	 00009646_00000000hl,
	 00004c8b_00000000hl,
	 00000000_00000000hl);
// 
extern vec_vsum_data_vr:label;

 
//! \fn void nmppiRGB32ToGray(RGB32_nm10s* pRGB, nm32u* pDstGray, int nSize);
//!
//! \perfinclude _nmppiRGB32ToGray__F11RGB32_nm10sPPUii.html
 
global _nmppiRGB32ToGray__F13RGB32_nm10sPPUii:label;
global _void._.8.8nmppiRGB32ToGray.1class._RGB32_nm10s._.0.9._unsigned._int._.0.9._int.2 :label;
<_nmppiRGB32ToGray__F13RGB32_nm10sPPUii>
<_void._.8.8nmppiRGB32ToGray.1class._RGB32_nm10s._.0.9._unsigned._int._.0.9._int.2>
.branch;
	vr = 0; 
	goto  _nmppiRGB32ToGray__F13RGB32_nm10sPPii+2;
		

//! \fn void nmppiRGB32ToGray(RGB32_nm10s* pRGB, nm32s* pDstGray, int nSize);
//!
//! \perfinclude _nmppiRGB32ToGray__F11RGB32_nm10sPPii.html
global _nmppiRGB32ToGray__F13RGB32_nm10sPPii:label;
global _void._.8.8nmppiRGB32ToGray.1class._RGB32_nm10s._.0.9._int._.0.9._int.2 :label;
<_nmppiRGB32ToGray__F13RGB32_nm10sPPii>
<_void._.8.8nmppiRGB32ToGray.1class._RGB32_nm10s._.0.9._int._.0.9._int.2>
	vr  = 0FF800000h;
	ar5 = tbl_w_RGB2Gray	with gr7=true;
	sb  = 80200802h			with gr7<<=31;  // sb=(10+10+10+2)x2
	nb1 = gr7;								// nb=32x2
	rep 8 wfifo=[ar5++],ftw;
	ar5 = ar7-2;
	
	push ar0,gr0 with gr0=false;
	push ar6,gr6 with gr0++;	
	push ar5,gr5;
	
	ar0 = [--ar5] with gr0++;	//  pSrc: bytes b,g,r,0,...//gr0=2
	ar6 = [--ar5] with gr6=gr0;	//  pDst
	gr5 = [--ar5];				//  nSize
	
	
	//void vec_vsum_data_vr(nmreg nb1, nmreg sb, nmreg woper, nmreg vr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6);
	call vec_vsum_data_vr with gr5>>=1;
		
			
	pop ar5,gr5;
	pop ar6,gr6;
	pop ar0,gr0;
	return;
end ".text_nmpli";