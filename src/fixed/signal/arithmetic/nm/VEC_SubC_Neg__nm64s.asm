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

begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSubCRev (nm64s *pSrcVec, int64b *pnVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsSubCRev_64s.html

global _nmppsSubCRev_64s:label;
<_nmppsSubCRev_64s>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	with gr6=gr7;
	ar0 = [--ar5];						// pSrcVec
	ar1 = ar5-3;
	ar5 = ar1;
	
	//ar1 = [--ar5];						// SrcN
	ar6 = [--ar5];						// pDstVec
	gr5 = [--ar5];						// nSize
	
	nb1 = 00000000h;
	wtw;
	delayed call vec_ram_sub_data 	with gr5;		// nSize in 64-bit longs
		nul;
		nul;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
