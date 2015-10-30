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
extern _nmppsTmpBuffer16_G_:long;

begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsAddC (nm64s *pSrcVec, int64b *pnVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAddC__FPlPlPli.html

global _void._.8.8nmppsAddC.1long._.0.9._long._.0.9._long._.0.9._int.2 :label;

<_void._.8.8nmppsAddC.1long._.0.9._long._.0.9._long._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// SrcBuff
	ar1 = [--ar5];	// Increment*
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize

	nb1 = 00000000h;	// nSize in 64-bit longs
	wtw;

	gr0 = 2;
	delayed call vec_data_add_ram;
	gr6 = 2;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;



end ".text_nmplv";
