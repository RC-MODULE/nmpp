//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulMV4.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulMV4.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"


data ".data_nmplm_G"
	WeightsAdd4to1:long[16]=(
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl
				
					  );

end ".data_nmplm_G";

//import from macros.mlb;

begin ".text_nmplm"


//--------------------------------------------------------------------
//! \fn void MTR_ProdUnitV( v4nm16s* pSrcMtr, nm16s* pDstVec, int nHeight)
//!
//! \perfinclude _MTR_ProdUnitV__F7v4nm16sPPSsi.html
//--------------------------------------------------------------------
       
global _MTR_ProdUnitV__F7v4nm16sPPSsi:label;
global _void._.8.8MTR_ProdUnitV.1class._v4nm16s._.0.9._short._.0.9._int.2 :label;
<_MTR_ProdUnitV__F7v4nm16sPPSsi>
<_void._.8.8MTR_ProdUnitV.1class._v4nm16s._.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	//		nm8s*		SrcMtr,			
	ar6 = [--ar5];	//			nm16s*		pDstVec,		
	gr6 = [--ar5];	//	int			nHeight			// Matrix height					:=[0,1,2,...]
	
	gr4 = 80008000h;	// nSize in 64-bit longs
	nb1 = gr4;
	sb  = 00020002h;
	ar4 = WeightsAdd4to1;
	ar5 = ar4;
	ar1 = ar0+2;
	ar2 = ar0+4;
	ar3 = ar0+6;
	gr0 = 8;
	gr1 = 8;
	gr2 = 8;
	gr3 = 8;
	with gr7 = gr6>>7;
	gr7--;
	<Next_Add4to1_rep32>
		rep 16 wfifo=[ar4++],ftw;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data=[ar0++gr0],ftw with vsum ,data,0;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
 		rep 32 data=[ar1++gr1],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data=[ar2++gr2],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data=[ar3++gr3] with vsum ,data,afifo;
	if <>0 delayed  goto Next_Add4to1_rep32 with gr7--; 
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
