//------------------------------------------------------------------------
//
//  $Workfile:: activate_data.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   activate_data.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"
    

    //------------------------------------------------------------------------
    //! \fn void vec_MaxVal_v4nm16s(nmreg ar0, nmreg gr0, nmreg gr5, nmreg gr7)
    //!
    //------------------------------------------------------------------------

.branch;
global vec_MaxVal_v4nm16s:label;
<vec_MaxVal_v4nm16s>
//	// ------------------ Поиск максимума среди 4-х 16р. элементов пузырька ----------------------------

	// ------------------ Поиск максимума среди 4-х 16р. элементов пузырька ----------------------------
	//	ar5,gr5 =[ar0];
	//	gr7 = 0FFFF0000h;							//  маска для выделения старшего элемента
	//	gr0 = gr5 and gr7;			// gr0 =[0]
	//	gr1 = gr5 <<16;				// gr1 =[1]
	//	gr5 = ar5;
	//	gr2 = gr5 and gr7;			// gr2 =[2]
	//	gr7 = gr5 <<16; 			// gr7 =[3] let it be max
	//	gr7 - gr0;
	//	if carry delayed skip 4; 	// skip if gr3<gr0
	//		nul;
	//		gr7 - gr1;
	//	gr7 = gr0;
	//	gr7 - gr1;
	//	if carry delayed skip 4; //skip if gr0<gr1
	//		nul;
	//		gr7 - gr2;
	//	gr7 = gr1;
	//	gr7 - gr2;
	//	if not carry delayed return ; 	//skip if gr0<gr1
	//		nul;
	//		nul;
	//		nul;
	//	delayed return;
	//		gr7 = gr2 A>>16;
	//		nul;
	//		nul;
	//		
	//.wait;

	
	ar5, gr5 = [ar0];
	gr0 = gr5<<16;
	gr1 = gr5>>16;
	gr1 = gr1<<16;
	gr5 = gr0-gr1;
	gr5 = gr5 A>>31;
	gr0 = gr0 and not gr5;
	gr7 = gr1 and gr5;
	gr5 = ar5 with	gr7 = gr7 or gr0;


	gr0 = gr5<<16;
	gr1 = gr5>>16;
	gr1 = gr1<<16;
	gr5 = gr0-gr7;
	gr5 = gr5 A>>31;
	gr0 = gr0 and not gr5;
	gr7 = gr7 and gr5;
	gr7 = gr7 or  gr0;


	gr5 = gr1-gr7;
	gr5 = gr5 A>>31;
	.align;
	gr1 = gr1 and not gr5;
	delayed return with	
		gr7 = gr7 and gr5;
		gr7 = gr7 or  gr1;
		gr7 = gr7 A>>16;
end ".text_nmvcore";		
	