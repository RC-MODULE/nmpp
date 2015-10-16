//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulMV16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulMV16.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"


data ".data_nmplm_G"
	WeightsAdd16to1:long[32]=(
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl
				
					  );

end ".data_nmplm_G";

import from macros.mlb;

begin ".text_nmplm"



/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void MTR_ProdUnitV( v16nm8s* pSrcMtr, nm16s* pDstVec, int nHeight)
//!
//! \perfinclude _MTR_ProdUnitV__F7v16nm8sPPSsi.html
//--------------------------------------------------------------------

       
global _MTR_ProdUnitV__F7v16nm8sPPSsi:label;
global _void._.8.8MTR_ProdUnitV.1class._v16nm8s._.0.9._short._.0.9._int.2 :label;
<_MTR_ProdUnitV__F7v16nm8sPPSsi>
<_void._.8.8MTR_ProdUnitV.1class._v16nm8s._.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	
	ar1 = [--ar5];	// SrcBuff
	ar6 = [--ar5];	// pDstVec
	gr6 = [--ar5];	// nSize in 8 bit elements
	
	gr4 = 80008000h;
	nb1 = gr4;
	sb  = 02020202h;
	ar4 = WeightsAdd16to1;
	ar5 = ar4;
	gr0 = 16 with gr1=false;
	gr2=2;
	with gr7 = gr6>>7;
	
	<Next_Add16to1_rep32>
		rep 32 wfifo=[ar4++],ftw;
		WTW_REG(gr4);
		ar0=ar1     with gr1+=gr2;
		rep 32 data=[ar0++gr0],ftw with vsum ,data,0;
		ar0=ar1+gr1 with gr1+=gr2;
		rep 32 data=[ar0++gr0] with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		WTW_REG(gr4);
 		rep 32 data=[ar0++gr0],ftw with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		rep 32 data=[ar0++gr0] with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		WTW_REG(gr4);
		rep 32 data=[ar0++gr0],ftw with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		rep 32 data=[ar0++gr0] with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		WTW_REG(gr4);
		rep 32 data=[ar0++gr0]  with vsum ,data,afifo;
		ar0=ar1+gr1 with gr1+=gr2;
		rep 32 data=[ar0++gr0] with vsum ,data,afifo;
		ar0+=-16+2 with gr1=false;
		ar1=ar0 with gr7--;
	if <>0 delayed  goto Next_Add16to1_rep32; 
		rep 32 [ar6++]=afifo;	
		ar4=ar5;


	<Finish>
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return with gr7=false;
.wait;
end ".text_nmplm"; 
