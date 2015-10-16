//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulCore_MulMV4.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulCore_MulMV4.asm
//! \author Сергей Мушкаев
//! \brief  Функции ядра для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------


import from macros.mlb;

begin ".text_nmplm"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Register interface function of weighted multiplication with activation
//
// It is equavalent notice of next pseudo-instuctions:
//		rep 32 wfifo=[ar4++],ftw,wtw;
//		rep nVal data=[ar0++gr0],ftw,wtw with vsum ,activate,0;
//		rep nVal data=[ar1++gr1],ftw,wtw with vsum ,activate,0;
//		rep nVal data=[ar2++gr2],ftw,wtw with vsum ,activate,0;
//		rep nVal data=[ar3++gr3] with vsum ,activate,0;
//		rep nVal [ar6++gr6]=afifo;
// where nVal=[0,1,2,3....31,32,33....]
//
//
// INPUT REGISTERS:
// ar0->SrcMtr1												:long Global[gr5*gr0/2]
// gr0= SrcMtr1 row to row   reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar1->SrcMtr2												:long Global[gr5*gr1/2]
// gr1= SrcMtr2 row to row   reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar2->SrcMtr3												:long Global[gr5*gr2/2]
// gr2= SrcMtr3 row to row   reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar3->SrcMtr4												:long Global[gr5*gr3/2]
// gr3= SrcMtr4 row to row   reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar4= 4x8 Vector Coefficients								:long Local [32] 
// gr4= nb1 (set column configuration)
//
// ar6->pDstVec												:long Local [gr5*gr6/2]
// gr6= pDstVec  long to long writing step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// gr5= nVal - vector's size in 64-bit words(longs)			:=[0,1,2,3..]
//
// sb = 8 string configration value ( divides weights matrix on 8 rows )
//
// NOTE:  There are no stack operations for some input registers,
// Registers : |ar0|ar1|ar2|ar3|ar4|   |ar6|   |
//			   |   |   |   |   |   |   |   |gr7|      will be changed after return !
//
// STATUS: Tested, optimized
//
macro MTR_ACC4MUL_MV8_REP(nVal)
		rep nVal data=[ar0++gr0],ftw with vsum ,data,0;
		WTW_REG(gr4);
 		rep nVal data=[ar1++gr1],ftw with vsum ,data,afifo;
		WTW_REG(gr4);
		rep nVal data=[ar2++gr2],ftw with vsum ,data,afifo;
		WTW_REG(gr4);
		delayed return; 
			rep nVal data=[ar3++gr3] with vsum ,data,afifo;
			rep nVal [ar6++gr6]=afifo;	
		nul;
		nul;
		nul;
		nul;
end MTR_ACC4MUL_MV8_REP;


global mtr_Acc4MulMV8:label;
      <mtr_Acc4MulMV8>
.branch;
	Acc4MulMV8_rep0:label;
	nb1 = gr4	with gr7=gr5>>5;
	rep 32 wfifo=[ar4++],ftw;
	push ar5,gr5 with gr5<<=27;	
	ar4-=64			with gr7;

	WTW_REG(gr4);
	if =0 delayed goto Acc4MulMV8_repN with gr5>>=23;
		 ar5 = Acc4MulMV8_rep0 with gr7--;
	<Next_Acc4MulMV8_rep32>
		rep 32 data =[ar0++gr0],ftw with vsum ,data,0;
		WTW_REG(gr4);
 		rep 32 data =[ar1++gr1],ftw with vsum ,data,afifo;
		WTW_REG(gr4);
		rep 32 data =[ar2++gr2],ftw with vsum ,data,afifo;
		WTW_REG(gr4);
		rep 32 data =[ar3++gr3]		with vsum ,data,afifo;
		rep 32 wfifo=[ar4++],ftw;
		ar4-=64;
		WTW_REG(gr4);
	if <>0 delayed  goto Next_Acc4MulMV8_rep32 with gr7--; 
		nul;
		rep 32 [ar6++gr6]=afifo;

	<Acc4MulMV8_repN>
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Acc4MulMV8_rep0>
	ftw;
	nul;
	delayed return;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	nul;nul;nul;nul;
	MTR_ACC4MUL_MV8_REP(1);
	MTR_ACC4MUL_MV8_REP(2);
	MTR_ACC4MUL_MV8_REP(3);
	MTR_ACC4MUL_MV8_REP(4);
	MTR_ACC4MUL_MV8_REP(5);
	MTR_ACC4MUL_MV8_REP(6);
	MTR_ACC4MUL_MV8_REP(7);
	MTR_ACC4MUL_MV8_REP(8);
	MTR_ACC4MUL_MV8_REP(9);
	MTR_ACC4MUL_MV8_REP(10);
	MTR_ACC4MUL_MV8_REP(11);
	MTR_ACC4MUL_MV8_REP(12);
	MTR_ACC4MUL_MV8_REP(13);
	MTR_ACC4MUL_MV8_REP(14);
	MTR_ACC4MUL_MV8_REP(15);
	MTR_ACC4MUL_MV8_REP(16);
	MTR_ACC4MUL_MV8_REP(17);
	MTR_ACC4MUL_MV8_REP(18);
	MTR_ACC4MUL_MV8_REP(19);
	MTR_ACC4MUL_MV8_REP(20);
	MTR_ACC4MUL_MV8_REP(21);
	MTR_ACC4MUL_MV8_REP(22);
	MTR_ACC4MUL_MV8_REP(23);
	MTR_ACC4MUL_MV8_REP(24);
	MTR_ACC4MUL_MV8_REP(25);
	MTR_ACC4MUL_MV8_REP(26);
	MTR_ACC4MUL_MV8_REP(27);
	MTR_ACC4MUL_MV8_REP(28);
	MTR_ACC4MUL_MV8_REP(29);
	MTR_ACC4MUL_MV8_REP(30);
	MTR_ACC4MUL_MV8_REP(31);
.wait;


end ".text_nmplm"; 
