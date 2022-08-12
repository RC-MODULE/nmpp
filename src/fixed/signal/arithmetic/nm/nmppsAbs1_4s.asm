//------------------------------------------------------------------------
//
//  $Workfile:: Abs.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Abs.Asm
//! \author Сергей Мушкаев
//! \brief  Абсолютное значение элементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"

extern vec_activate_data_xor_data:label;

begin ".text_nmplv"


//! \fn void nmppsAbs1 (nm4s *pSrcVec, nm4s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAbs1__F4nm4sP4nm4sPi.html

global _nmppsAbs1_4s:label;
<_nmppsAbs1_4s>
.branch;
	ar5 = sp - 2	with gr7=gr5;
	push ar0,gr0	with gr0=false;
	push ar6,gr6	with gr0++;
	ar0 = [--ar5]	with gr0++;		// pSrcVec
	ar6 = [--ar5]	with gr6=gr0;	// pDstVec
	gr5 = [--ar5];	// nSize
	f1cr= 88888888h;   						
	call  vec_activate_data_xor_data with gr5>>=4;	// nSize in 64-bit longs


	pop ar6,gr6;
	pop ar0,gr0		with gr5=gr7;
	return;
.wait;


end ".text_nmplv";
