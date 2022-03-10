//------------------------------------------------------------------------
//
//  $Workfile:: nmppiWAdd.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   nmppiWAdd.cpp
//! \author S. Mushkaev
//! \brief  Взвешенное суммирование двух кадров
//!
//! \endif
//!
//------------------------------------------------------------------------


import from macros.mlb;
extern vec_Mul2D2W8_AddVr:label;

data ".data_nmpli_L"
		w_Zero16_L:long[16]=(0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl);
end ".data_nmpli_L";

data ".data_nmpli_G"
		w_Zero16_G:long[16]=(0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl,0hl);
end  ".data_nmpli_G";

begin ".text_nmpli"

//! \fn void nmppiWAdd2I(RGB32_nm10s* pSrcImg1, int nMulVal1, RGB32_nm10s* pSrcImg2, int nMulVal2, int nAddVal, RGB32_nm10s* pDstImg, int nSize)
//!
//! \n
//! \perfinclude _nmppiWAdd2I__F11RGB32_nm10sPi11RGB32_nm10sPii11RGB32_nm10sPi.html
global _nmppiWAdd2I__F13RGB32_nm10sPi13RGB32_nm10sPii13RGB32_nm10sPi :label;
global _void._.8.8nmppiWAdd2I.1class._RGB32_nm10s._.0.9._int.9._class._RGB32_nm10s._.0.9._int.9._int.9._class._RGB32_nm10s._.0.9._int.2 :label;
<_nmppiWAdd2I__F13RGB32_nm10sPi13RGB32_nm10sPii13RGB32_nm10sPi>
<_void._.8.8nmppiWAdd2I.1class._RGB32_nm10s._.0.9._int.9._class._RGB32_nm10s._.0.9._int.9._int.9._class._RGB32_nm10s._.0.9._int.2>
.branch;

	ar5 = ar7-2		with gr7 = true;
	push ar0,gr0	with gr7<<=31;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0 = [--ar5];	// pSrcImg1
	gr0 = [--ar5];	// nMulVal1
	ar1 = [--ar5];	// pSrcImg2
	gr1 = [--ar5];	// nMulVal2
	gr2 = [--ar5];	// nAddVal
	ar6 = [--ar5];	// pDstImg
	gr5 = [--ar5];	// nSize

	gr7 = 3Fh;
	gr0 = gr0 and gr7;
	gr1 = gr1 and gr7;
	gr2 = gr2 and gr7;
	//preparing of vr
	gr7 = gr2 << 10;
	gr7 = gr7 or gr2;
	gr7 <<=10;
	gr7 = gr7 or gr2;
	vr  = gr7;

	// Preparing of matrix of weighted coefficients
	ar4 = w_Zero16_G;
	gr4 = 2;
	[ar4++gr4]= gr0 with gr7 = gr0<<10;
	[ar4++gr4]= gr7 with gr7<<=10;
	[ar4++gr4]= gr7 ;
	ar4+=gr4;
	ar4++;
	[ar4++gr4]= gr0 with gr7 = gr0<<10;
	[ar4++gr4]= gr7 with gr7<<=10;
	[ar4++gr4]= gr7 ;
	ar4++;
	[ar4++gr4]= gr1 with gr7 = gr1<<10;
	[ar4++gr4]= gr7 with gr7<<=10;
	[ar4++gr4]= gr7 ;
	ar4+=gr4;
	ar4++;
	[ar4++gr4]= gr1 with gr7 = gr1<<10;
	[ar4++gr4]= gr7 with gr7<<=10;
	[ar4++gr4]= gr7 ;
	

	ar4 = w_Zero16_G;
	gr4 = 0a0080200h;
	sb  = 080200802h;
	nb1 = gr4;

	gr0 = 2;
	gr1 = 2;
	gr6 = 2;
	// void vec_Mul2D2W8_AddVr (nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6)
	delayed call vec_Mul2D2W8_AddVr with gr5>>=1;
		nul;
		nul;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return;
.wait;


end ".text_nmpli";