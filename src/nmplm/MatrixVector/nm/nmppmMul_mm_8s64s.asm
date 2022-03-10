//------------------------------------------------------------------------
//
//  $Workfile:: mtrMul_M08M64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMul_M08M64.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на матрицу.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void nmppmMul_mm_8s64s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
//!
//! \perfinclude nmppmMul_mm_8s64s.html
//--------------------------------------------------------------------

extern mtrMul_mm_8sXs:label;
extern _nmppsTmpBuffer64_G_: long[64];
const LongColumns=_nmppsTmpBuffer64_G_;


global _nmppmMul_mm_8s64s:label;
<_nmppmMul_mm_8s64s>
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
	ar2 = [--ar5];			// SrcMatrixB
	ar6 = [--ar5];			// DstMatrix
	gr4 = [--ar5];			// nWidth  B in 64-bit words
	[LongColumns] = gr4 with gr0>>=2;	// nWidth A in 32-bit words
	gr4 <<=1;
	gr6 = gr4 with gr3=false;			
	nb1 = gr3;
	<Next_MulMV>
		push ar0,gr0;
		push ar6,gr6;
		
		delayed call mtrMul_mm_8sXs;
			ar4 = ar2;
			nul;

		pop ar6,gr6;
		pop ar0,gr0;
		gr7 = [LongColumns];
		ar2+=2;
		ar6+=2	with gr7--;
	if <>0 delayed goto Next_MulMV;
		[LongColumns] = gr7;

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
