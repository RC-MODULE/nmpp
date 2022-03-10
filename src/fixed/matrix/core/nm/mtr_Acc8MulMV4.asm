//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulCore_Acc8MulMV4.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulCore_Acc8MulMV4.asm
//! \author Сергей Мушкаев
//! \brief  Функции ядра для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------

import from macros.mlb;
data ".data_nmplm_G"
global	vec_ar0gr0:long;
global	vec_ar1gr1:long;
global	vec_ar2gr2:long;
global	vec_ar3gr3:long;
global	vec_ar4gr4:long;
global	vec_ar5gr5:long;
global	vec_ar6gr6:long;
global	vec_ar7gr7:long;
end ".data_nmplm_G";

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
macro MTR_ACC8MUL_MV4_REP(nVal)
		ar0,gr0 = [vec_ar0gr0];
		ar1,gr1 = [vec_ar1gr1];
		ar2,gr2 = [vec_ar2gr2];
		ar3,gr3 = [vec_ar3gr3];

		rep nVal data =[ar0++gr0],ftw with vsum ,data,0;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar1++gr1],ftw with vsum ,data,afifo;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar2++gr2],ftw with vsum ,data,afifo;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar3++gr3],ftw	with vsum ,data,afifo;

		[vec_ar0gr0] = ar0,gr0;
		[vec_ar1gr1] = ar1,gr1;
		[vec_ar2gr2] = ar2,gr2;
		[vec_ar3gr3] = ar3,gr3;
		
		ar0,gr0 = [vec_ar4gr4];
		ar1,gr1 = [vec_ar5gr5];
		ar2,gr2 = [vec_ar6gr6];
		ar3,gr3 = [vec_ar7gr7];
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar0++gr0],ftw with vsum ,data,afifo;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar1++gr1],ftw with vsum ,data,afifo;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar2++gr2],ftw with vsum ,data,afifo;
		WTW_REG_DEPRICATED(gr4);
		rep nVal data =[ar3++gr3]		with vsum ,data,afifo;
		rep nVal [ar6++gr6]=afifo;	
		nul;
		[vec_ar4gr4] = ar0,gr0;
		[vec_ar5gr5] = ar1,gr1;
		[vec_ar6gr6] = ar2,gr2;
		delayed return; 
			nul;
			[vec_ar7gr7] = ar3,gr3;
		nul;nul;nul;nul;nul;nul;
		
end MTR_ACC8MUL_MV4_REP;


global mtr_Acc8MulMV4:label;
      <mtr_Acc8MulMV4>
.branch;
	Acc8MulMV4_rep0:label;
	nb1 = gr4	with gr7=gr5>>5;
	rep 32 wfifo=[ar4++],ftw;
	push ar5,gr5 with gr5<<=27;
	ar4-=64			with gr7;
	//WTW_REG_DEPRICATED(gr4);
	wtw;
	if =0 delayed goto Acc8MulMV4_repN with gr5>>=21;
		 ar5 = Acc8MulMV4_rep0 with gr7--;
	<Next_Acc8MulMV4_rep32>
		ar0,gr0 = [vec_ar0gr0];
		ar1,gr1 = [vec_ar1gr1];
		ar2,gr2 = [vec_ar2gr2];
		ar3,gr3 = [vec_ar3gr3];
		
		rep 32 data =[ar0++gr0],ftw with vsum ,data,0;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar1++gr1],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar2++gr2],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar3++gr3],ftw	with vsum ,data,afifo;

		[vec_ar0gr0] = ar0,gr0;
		[vec_ar1gr1] = ar1,gr1;
		[vec_ar2gr2] = ar2,gr2;
		[vec_ar3gr3] = ar3,gr3;
		
		ar0,gr0 = [vec_ar4gr4];
		ar1,gr1 = [vec_ar5gr5];
		ar2,gr2 = [vec_ar6gr6];
		ar3,gr3 = [vec_ar7gr7];
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar0++gr0],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar1++gr1],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar2++gr2],ftw with vsum ,data,afifo;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
		rep 32 data =[ar3++gr3]		with vsum ,data,afifo;
		rep 32 wfifo=[ar4++],ftw;
		[vec_ar4gr4] = ar0,gr0;
		[vec_ar5gr5] = ar1,gr1;
		[vec_ar6gr6] = ar2,gr2;
		[vec_ar7gr7] = ar3,gr3;
		ar4-=64;
		//WTW_REG_DEPRICATED(gr4);
		wtw;
	if <>0 delayed  goto Next_Acc8MulMV4_rep32 with gr7--; 
		nul;
		rep 32 [ar6++gr6]=afifo;

	<Acc8MulMV4_repN>
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Acc8MulMV4_rep0>
	ftw;
	nul;
	delayed return;
		nul;
		nul;
		nul;
	.repeat 56;
		nul;
	.endrepeat;
	MTR_ACC8MUL_MV4_REP(1);
	MTR_ACC8MUL_MV4_REP(2);
	MTR_ACC8MUL_MV4_REP(3);
	MTR_ACC8MUL_MV4_REP(4);
	MTR_ACC8MUL_MV4_REP(5);
	MTR_ACC8MUL_MV4_REP(6);
	MTR_ACC8MUL_MV4_REP(7);
	MTR_ACC8MUL_MV4_REP(8);
	MTR_ACC8MUL_MV4_REP(9);
	MTR_ACC8MUL_MV4_REP(10);
	MTR_ACC8MUL_MV4_REP(11);
	MTR_ACC8MUL_MV4_REP(12);
	MTR_ACC8MUL_MV4_REP(13);
	MTR_ACC8MUL_MV4_REP(14);
	MTR_ACC8MUL_MV4_REP(15);
	MTR_ACC8MUL_MV4_REP(16);
	MTR_ACC8MUL_MV4_REP(17);
	MTR_ACC8MUL_MV4_REP(18);
	MTR_ACC8MUL_MV4_REP(19);
	MTR_ACC8MUL_MV4_REP(20);
	MTR_ACC8MUL_MV4_REP(21);
	MTR_ACC8MUL_MV4_REP(22);
	MTR_ACC8MUL_MV4_REP(23);
	MTR_ACC8MUL_MV4_REP(24);
	MTR_ACC8MUL_MV4_REP(25);
	MTR_ACC8MUL_MV4_REP(26);
	MTR_ACC8MUL_MV4_REP(27);
	MTR_ACC8MUL_MV4_REP(28);
	MTR_ACC8MUL_MV4_REP(29);
	MTR_ACC8MUL_MV4_REP(30);
	MTR_ACC8MUL_MV4_REP(31);
.wait;


end ".text_nmplm"; 
