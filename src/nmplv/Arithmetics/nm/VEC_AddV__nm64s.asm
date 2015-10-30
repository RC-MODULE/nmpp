//------------------------------------------------------------------------
//
//  $Workfile:: Add.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Add.Asm
//! \author Сергей Мушкаев
//! \brief  Функции суммирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"



extern vec_Add:label;
begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsAdd (nm64s *pSrcVec1, nm64s *pSrcVec2, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsAdd_64s.html


global _void._.8.8nmppsAdd.1long._.0.9._long._.0.9._long._.0.9._int.2 :label;

<_void._.8.8nmppsAdd.1long._.0.9._long._.0.9._long._.0.9._int.2>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++;
	push ar5,gr5 with gr0++;		// gr0=2 
	push ar6,gr6 with gr1=gr0;
	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 64-bit elements
	
	nb1 = 0;		
	delayed call vec_Add with gr1=gr0;
		wtw;						
		gr6=gr0;					// gr6=2
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;






end ".text_nmplv";
