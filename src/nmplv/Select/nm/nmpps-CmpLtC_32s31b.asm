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

extern vec_CmpLtC:label;


begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsCmpLtC_32s31b (nm32s *pSrcVec, int32b nVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude nmppsCmpLtC_32s31b.html

global _nmppsCmpLtC_32s31b:label;
<_nmppsCmpLtC_32s31b>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff
	gr1 = [--ar5];	// nVal
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	
	nb1 = 80000000h with gr5>>=1;	// nSize in 64-bit longs
	wtw;
	ar1 = gr1 ;
	ar5 = ar7;
	push ar1,gr1;
	ar1 = ar5;
	gr0 = 2;
	f1cr = 0FFFFFFFEh;
    	delayed call vec_CmpLtC;
		gr6 = 2;
			
	pop ar1,gr1; 
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;

return with gr7=false;
.wait;



end ".text_nmplv";
