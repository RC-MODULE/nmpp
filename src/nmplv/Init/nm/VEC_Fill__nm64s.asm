//------------------------------------------------------------------------
//
//  $Workfile:: Init.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
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

extern vec_ram:label;


begin ".text_nmplv"

    //--------------------------------------------------------------------
    //! \fn void nmppsSet_64sp(nm64s *pVec, int64b *nVal, int nSize) 
	//!
	//! \perfinclude _nmppsSet_64s.html
    //--------------------------------------------------------------------

global _nmppsSet_64sp:label;
<_nmppsSet_64sp>
.branch;
    ar5 = sp - 2	with gr7=false;
    push ar0,gr0	with gr7++;
	push ar5,gr5	with gr7++;
	push ar6,gr6	with gr6=gr7;

    ar6 = [--ar5];			// Buffer
	delayed call vec_ram;
		ar0 = [--ar5];			// *Init value(Hi|Lo)
    gr5 = [--ar5];			// nSize

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";