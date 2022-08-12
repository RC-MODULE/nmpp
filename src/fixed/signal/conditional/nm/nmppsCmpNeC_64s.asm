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
extern _VEC_TBL_MinusOne_G:long;

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsCmpNeC_64s (nm64s *pSrcVec, int64b nVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude nmppsCmpNeC_64s.html

global _nmppsCmpNeC_64s:label;
<_nmppsCmpNeC_64s>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff
	gr7 = [--ar5];  //dummy allign
	vr  = [--ar5];	// nVal
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	ar5 = _VEC_TBL_MinusOne_G set ;
	
	nb1 = 00000000h;	// nSize in 64-bit longs
	sb  = 00000000h;
	rep 1 wfifo = [ar5++],ftw,wtw;
	
	gr0 = 2;
	f1crl = 0FFFFFFFEh;
    f2crl = 0FFFFFFFEh;  
	f1crh = 0FFFFFFFFh;
    f2crh = 0FFFFFFFFh;  
	delayed call vec_CmpNeC;
		gr6 = 2;
			
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;

return with gr7=false;
.wait;



end ".text_nmplv";
