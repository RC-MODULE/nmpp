//------------------------------------------------------------------------
//
//  $Workfile:: SubVN.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   SubVN.asm
//! \author Иван Жиленков
//! \brief  Функции вычитания для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_data_sub_ram:label;
extern _nmppsTmpBuffer16_G_:long;

begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSubC (nm4s *pSrcVec, int4b nVal, nm4s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsSubC_4s.html

global _nmppsSubC_4s:label;
<_nmppsSubC_4s>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	with gr6=gr7;

	ar0 = [--ar5];						// pSrcVec
	gr1 = [--ar5];						// SrcN
	ar6 = [--ar5]	with gr7 = gr1<<28;	// pDstVec
	gr5 = [--ar5]	with gr1 = gr7>>4;	// nSize
	
	ar1 = _nmppsTmpBuffer16_G_+2	with gr1 = gr1 or gr7;
	nb1 = 88888888h		with gr7 = gr1 >> 8;
	wtw;
	gr1 = gr1 or gr7;
	
	gr7 = gr1 >> 16;
	gr1 = gr1 or gr7;
	
	delayed call vec_data_sub_ram with gr5>>=4;		// nSize in 64-bit longs
		[--ar1]=gr1;	
		[--ar1]=gr1;
	

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
