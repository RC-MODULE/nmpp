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

extern vec_CmpNeC:label;
extern _VEC_TBL_Diagonal_FFh_G:long;

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsCmpNeC_8s (nm8s *pSrcVec, int8b nVal, nm8s *pDstVec, int nSize) 
//!
//! \perfinclude nmppsCmpNeC_8s.html

global _nmppsCmpNeC_8s:label;
<_nmppsCmpNeC_8s>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff
	gr0 = [--ar5];	// nVal
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	ar5 = _VEC_TBL_Diagonal_FFh_G set ;
	
	nb1 = 80808080h with gr5>>=3;	// nSize in 64-bit longs
	sb  = 02020202h;
	rep 8 wfifo = [ar5++],ftw,wtw;
	
	gr0 <<=24;
	gr0 >>=24;
	gr7 = gr0 << 8;
	gr7 = gr7 or gr0;
	gr0 = gr7 << 16;
	gr1 = gr7 or gr0;
	vr  = gr1;
	gr0 = 2;
	f1cr = 0FEFEFEFEh;
    f2cr = 0FEFEFEFEh;  
	delayed call vec_CmpNeC;
		gr6 = 2;
	
		
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;

return with gr7=false;
.wait;



end ".text_nmplv";
