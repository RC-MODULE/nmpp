//------------------------------------------------------------------------
//
//  $Workfile:: Cnv16to08.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   Cnv16to08.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif 
//!
//------------------------------------------------------------------------
//#include "vConvert.h"


extern vec_Mul2D2W4_AddVr:label;
extern tbl_f1cr_nm16:long[8];

//data ".data_nmplv_L"
//	LWConvert16to8:  long[8] = ( 
//						0000000000000001hl, 
//						0000000000000100hl,
//						0000000000010000hl, 
//						0000000001000000hl,
//						0000000100000000hl, 
//						0000010000000000hl,
//						0001000000000000hl, 
//						0100000000000000hl);
//
//
//end ".data_nmplv_L";
//
//
//data ".data_nmplv_G"
//	GWConvert16to8:  long[8] = ( 
//						0000000000000001hl, 
//						0000000000000100hl,
//						0000000000010000hl, 
//						0000000001000000hl,
//						0000000100000000hl, 
//						0000010000000000hl,
//						0001000000000000hl, 
//						0100000000000000hl);
//
//end ".data_nmplv_G";
begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCnv_16s(nm16s* pSrcVec, nm8s* pDstVec, int nSize)
//!
//! \perfinclude _nmppsCnv_16s.html


global _nmppsClipCnv_AddC_16s:label;
<      _nmppsClipCnv_AddC_16s>
.branch;
	ar5 = sp - 2	with gr7=false;
	f1cr = gr7;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6;
	
	ar0 = [--ar5];					// [pSrcVec]
	gr6 = [--ar5];					// [ClipIndex]
	ar6 = tbl_f1cr_nm16	with gr6<<=1;		
	f1cr= [ar6+=gr6] 	with gr6=gr7;// gr6=2;

	gr4 = [--ar5];					// [AddValue]
	gr4<<=24;
	gr7 = gr4>>8;
	gr7 = gr7 or gr4;
	gr4 = gr7 >> 16;
	gr7 = gr4 or gr7;
	vr  = gr7;
	
	nb1 = 80808080h;
	sb  = 00020002h;
	
	ar6 = [--ar5];					// [pDstVec]
	gr5 = [--ar5]	with gr6 = gr0;	// [nSize] gr6 = 2
	delayed call vec_Mul2D2W4_AddVr	with gr5>>=3;
		ar1 = ar0+gr0 	with gr0 = gr1;	// gr0=4	
		ar4 = [--ar5] ;				// [weights] (LWConvert16to8)
		
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";
