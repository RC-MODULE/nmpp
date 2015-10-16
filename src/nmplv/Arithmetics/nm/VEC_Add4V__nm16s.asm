//------------------------------------------------------------------------
//
//  $Workfile:: MultipleAdd16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   MultipleAdd16.Asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения с накоплением для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"


data ".data_nmplv_G"

end ".data_nmplv_G";

import from macros.mlb;

extern vec_Add4V:label;
begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_AddNV (nm16s **ppSrcVec, nm16s *pDstVec, int nSize, int nNumberOfVectors) 
//!
//! \perfinclude _VEC_AddNV__FPPSsPSsii.html

global _void._.8.8VEC_Add4V.1short._.0.0.9._short._.0.9._int.2 :label;
<_void._.8.8VEC_Add4V.1short._.0.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;
	
	PUSH_REGS();
	ar4 = [--ar5];	// Buffers
	ar6 = [--ar5];	// DstBuffer
	gr5 = [--ar5];	// SizeOfBuffers
	
	gr0 = 2;
	ar0 = [ar4++] with gr1=gr0;
	ar1 = [ar4++] with gr2=gr0;
	ar2 = [ar4++] with gr3=gr0;
	ar3 = [ar4++] with gr6=gr0;
	
	nb1 = 80008000h with gr5>>=2;	// nSize in 64-bit longs
	call vec_Add4V;
	
	POP_REGS();
	return ;
.wait;
end ".text_nmplv";
 


