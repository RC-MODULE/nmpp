//------------------------------------------------------------------------
//
//  $Workfile:: AddVN.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   AddVN.asm
//! \author Сергей Мушкаев
//! \brief  Функции суммирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_data_add_ram:label;
extern _VEC_TmpBuffer16_G:long;

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_AddC (nm32s *pSrcVec, int32b nVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_AddC__FPiiPii.html

global _void._.8.8VEC_AddC.1int._.0.9._int.9._int._.0.9._int.2 :label;
<_void._.8.8VEC_AddC.1int._.0.9._int.9._int._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// pSrcVec
	gr1 = [--ar5];	// nVal
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	ar5 = _VEC_TmpBuffer16_G set;
	nb1 = 80000000h with gr5>>=1;	// nSize in 64-bit longs
	wtw;
	ar1 = gr1;
	gr0 = 2;
	gr6 = 2;
	delayed call vec_data_add_ram;
		[ar5]=ar1,gr1;
		ar1 = ar5;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;





end ".text_nmplv";
