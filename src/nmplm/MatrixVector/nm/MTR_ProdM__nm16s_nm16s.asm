//------------------------------------------------------------------------
//
//  $Workfile:: mtrMul_M16M16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMul_M16M16.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на матрицу.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------	
//! \fn void MTR_ProdM( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
//!
//! \perfinclude _MTR_ProdM__FPSsiiPSsPSsi.html
//--------------------------------------------------------------------
	
extern rep_n_Mul_M16V64:label;
extern _nmppsTmpBuffer64_G_: long[64];
const LongColumns=_nmppsTmpBuffer64_G_;

global _MTR_ProdM__FPSsiiPSsPSsi:label;
global _void._.8.8MTR_ProdM.1short._.0.9._int.9._int.9._short._.0.9._short._.0.9._int.2 :label;
<_MTR_ProdM__FPSsiiPSsPSsi>
<_void._.8.8MTR_ProdM.1short._.0.9._int.9._int.9._short._.0.9._short._.0.9._int.2>
.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	//-----------------------------------------
	ar0 = [--ar5];			// SrcMatrixA
	gr5 = [--ar5];			// nHeight A
	gr0 = [--ar5];			// nWidth  A in 16-bit words
	ar4 = [--ar5];			// SrcMatrixB
	ar6 = [--ar5];			// DstMatrix
	gr4 = [--ar5];			// nWidth  B in 16-bit words
	gr4 >>=2;
	[LongColumns] = gr4 with gr0>>=1;
	gr4 <<=1;
	gr6 = gr4;
	gr3 = 80008000h;			// gr3(nb1)
	
	<Next_MulMV>
		push ar0,gr0;
		push ar4,gr4;
		push ar6,gr6;
		
		delayed call rep_n_Mul_M16V64;
			nul;
			nul;

		pop ar6,gr6;
		pop ar4,gr4;
		pop ar0,gr0;
		ar4+=2;
		ar6+=2;

		gr7 = [LongColumns];
		with gr7--;
		[LongColumns] = gr7;
	if <>0 delayed goto Next_MulMV;
		nul;
		nul;

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
