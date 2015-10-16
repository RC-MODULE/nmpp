//------------------------------------------------------------------------
//
//  $Workfile:: SubNV.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   SubNV.asm
//! \author Сергей Мушкаев
//! \brief  Функции вычитания для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_ram_sub_data:label;
extern  _VEC_TmpBuffer16_G:long;

begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_SubC_Neg (nm8s *pSrcVec, int8b nVal, nm8s *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_SubC_Neg__FPciPci.html

global _VEC_SubC_Neg__FPciPci:label;
global _void._.8.8VEC_SubC_Neg.1char._.0.9._int.9._char._.0.9._int.2 :label;
<_VEC_SubC_Neg__FPciPci>
<_void._.8.8VEC_SubC_Neg.1char._.0.9._int.9._char._.0.9._int.2>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	with gr6=gr7;

	ar0 = [--ar5];						// pSrcVec
	gr1 = [--ar5];						// SrcN
	ar6 = [--ar5]	with gr7 = gr1<<24;	// pDstVec
	gr5 = [--ar5]	with gr1 = gr7>>8;	// nSize
	
	ar1 = _VEC_TmpBuffer16_G+2	with gr1 = gr1 or gr7;
	nb1 = 80808080h		with gr7 = gr1 >> 16;
	wtw;
	gr1 = gr1 or gr7;
	
	delayed call vec_ram_sub_data with gr5>>=3;		// nSize in 64-bit longs
		[--ar1]=gr1;	
		[--ar1]=gr1;
	

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv";
