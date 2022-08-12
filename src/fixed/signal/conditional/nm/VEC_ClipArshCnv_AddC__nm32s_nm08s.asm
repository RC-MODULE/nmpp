//------------------------------------------------------------------------
//
//  $Workfile:: ClipPowCRShiftConvertAddC.asm    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file  ClipPowCRShiftConvertAddC.asm
//! \author Сергей Свечников
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------

data ".data_nmplv_L"
  LWRShiftConvert32to8: long[16]=( 
     0l, 1l,             0l,            100hl,
     0l, 10000hl,        0l,        1000000hl,
     0l, 100000000hl,    0l,    10000000000hl,
     0l, 1000000000000hl,0l,100000000000000hl );
end ".data_nmplv_L";

data ".data_nmplv_G"
  GWRShiftConvert32to8: long[16]=( 
     0l, 1l,             0l,            100hl,
     0l, 10000hl,        0l,        1000000hl,
     0l, 100000000hl,    0l,    10000000000hl,
    0l, 1000000000000hl, 0l,100000000000000hl );
end ".data_nmplv_G";
begin ".text_nmplv"
//extern F1CR_Tbl_32bit: long;	//Modified by S.Mushkaev	
extern  tbl_f1cr_nm32 : long;

extern tbl_sb_nm32_EvenARSH: long;
extern vec_ClipMul4D4W4_AddVr:label;     // core:from file Math_Mul4D4W4.asm 

//! \fn void nmppsClipRShiftConvert_AddC_32s(nm32s* pSrcVec, int nClipFactor,int nShift, int8b nAddValue,nm8s* pDstVec, int nSize);
//! 
//! \perfinclude _nmppsClipRShiftConvert_AddC_32s.html

global _nmppsClipRShiftConvertAddC_32s8s:label;
<_nmppsClipRShiftConvertAddC_32s8s>
	ar5=ar7-2 with gr7=false;
	push ar6,gr6 with gr7++;      //   gr7=1
	push ar0,gr0 with gr6=gr7<<1; //   gr6=2
	push ar1,gr1; 				  //   
	push ar2,gr2 with gr1=gr7<<3; //   gr1=8   
	push ar3,gr3 with gr2=gr1;    //   gr2=8
	push ar4,gr4 with gr3=gr1;    //   gr3=8
	push ar5,gr5;

	gr5=[--ar5];     //  SrcVec
	gr0=[--ar5];     //  ClipFactor
	ar0 = tbl_f1cr_nm32 with gr0<<=1;
	f1cr= [ar0+=gr0];
	gr0=[--ar5];     //  Shift
	ar0 = tbl_sb_nm32_EvenARSH;
	sb  = [ar0+=gr0];      
	gr4 = 80808080h;
	nb1 = gr4;
	gr0=[--ar5];     //  AddValue
	gr0<<=24;
	gr7 = gr0>>8;
	gr7 = gr7 or gr0;
	gr0 = gr7 >> 16;
	gr7 = gr0 or gr7;
	vr  = gr7 with gr0=gr1;  //   gr0=8;
	
	
	ar0=gr5 with gr7=gr5; // Где банка из
	if < delayed skip L0 with gr7+=gr6;  // gr7=src+2
		ar4 = LWRShiftConvert32to8; ar4 = GWRShiftConvert32to8;
	<L0>
	ar1=gr7 with gr7+=gr6; // ar1=src+2
	ar6=[--ar5];     //  DstVec
	gr5=[--ar5];     //  Size
	delayed call vec_ClipMul4D4W4_AddVr with gr5>>=3;
		ar2=gr7 with gr7+=gr6; // ar2=src+2
		ar3=gr7 with gr7+=gr6; // ar3=src+2
	//===================================
	pop ar5,gr5; 
	pop ar4,gr4;
	pop ar3,gr3; 
	pop ar2,gr2;
	pop ar1,gr1; 
	pop ar0,gr0;
	pop ar6,gr6;
	return;
end ".text_nmplv";
