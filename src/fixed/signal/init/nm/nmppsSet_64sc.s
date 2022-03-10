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

.extern vec_ram


//.section .text_nmplv,"ax",@probits
.text

//--------------------------------------------------------------------
//! \fn void nmppsSet_64sc(int64sc val, nm64sc *pDst, int len) 
//--------------------------------------------------------------------

.global _nmppsSet_64sc
_nmppsSet_64sc:

    ar5 = ar7 - 2	with gr7=false;
	
	// sp 		top stack 
	// -------------------
	// 	        pswr
	//	        ret addr
	// 			& val 
	// 			pDst
	// 			len
	
	
	
    push ar0,gr0	with gr7++;
	push ar5,gr5	with gr7=gr7<<2;
	push ar6,gr6;
	
	ar0 = [--ar5];					// addr val
	ar6 = [--ar5]  with gr6=gr7;	// pDst & step 4;		
	
	delayed call vec_ram;
		gr5 = [--ar5];				// len
		ar5 = ar6 with gr0 = gr5;
	
	ar0+= 2;						
	ar6 = ar5 with gr5=gr0;
	delayed call vec_ram;
		ar6+=2;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;




