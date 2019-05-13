//------------------------------------------------------------------------
//
//  $Workfile:: mtrMul_M32V64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMul_M32V64.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppmMul_mv_32s64s( nm32s* pSrcMtr,  nm64s* pSrcVec, nm64s* pDstVec, int nHeight, int nWidth);
//!
//! \perfinclude nmppmMul_mv_32s64s.html

extern mtrMul_mm_32sXs:label;
extern _nmppsTmpBuffer64_G_: long;
extern _nmppsTmpBuffer64_L_: long;

global _nmppmMul_mv_32s64s:label;
<_nmppmMul_mv_32s64s>
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
	ar0 = [--ar5]			// SrcMatrix
		with gr3=false;			// gr3(nb1)
	nb1 = gr3;
	ar4 = [--ar5]			// pSrcVec
		with gr4=gr3+1;				
	ar6 = [--ar5]			// pDstVec
		with gr4++;				// gr4 = 2 (Reading step)	

	delayed call mtrMul_mm_32sXs	with gr6=gr4;			// gr6 = 2 (Writing step)	
		gr5 = [--ar5];		// nHeight
		gr0 = [--ar5];		// nWidth in 32-bit words

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
