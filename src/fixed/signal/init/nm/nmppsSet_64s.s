//------------------------------------------------------------------------
//
//  $Workfile:: Init.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2022
//
//! \if file_doc
//!
//! \file   Init.asm
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vMinMax.h"

.extern vec_ram;


//begin ".text_nmplv"
.text

//--------------------------------------------------------------------
//! \fn void nmppsSet_64s(int64b val, nm64s *pDst, int len) 
//--------------------------------------------------------------------

.global _nmppsSet_64s
_nmppsSet_64s:
//.branch;
    ar5 = ar7 - 4	with gr7=false;
	
	// sp 		top stack 
	// -------------------
	// 	        pswr
	//	        ret addr
	// 			val hi
	// sp-4  	val lo
	// 			pDst
	// 			len
	
    push ar0,gr0	with gr7++;
	push ar5,gr5	with gr7++;
	push ar6,gr6;
	ar0 = ar5;						// pointer to 64-bit val in stack
	delayed call vec_ram;
		ar6 = [--ar5];				// pDst
		gr5 = [--ar5] with gr6=gr7;	// len & step 2;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;
//.wait;



//end ".text_nmplv";