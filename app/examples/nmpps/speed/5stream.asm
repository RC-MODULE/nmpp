//------------------------------------------------------------------------
//
//  $Workfile:: MultipleAdd16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   MultipleAdd16.Asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения с накоплением для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"
global _run5streams:label;
<_run5streams>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	
	ar0 = [--ar5];	// ram
	ar1 = [--ar5];	// wfifo
	ar2 = [--ar5];	// data
	ar3 = [--ar5];	// afifo
	ar4 = [--ar5];	// scalar
	gr7 = [--ar5];	// size
	.wait;
	nb1 = 80008000h with gr7>>=6;
	sb = 0aaaaaaaah with gr7--;
	.branch;
	//.wait;
	//gr5 = pcr;
	//gr1 = 080h;
	//gr5 = gr5 or gr1;
	//pcr = gr5;
	<Next>
		
		rep 32 ram  =[ar0];	
		
		rep 32 wfifo=[ar1],ftw;
		
	if <>0 delayed goto Next with gr7--;
		
		rep 32 data =[ar2] with data+ram;
		rep 32 [ar3]=afifo;

	
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
	return ;
.wait;
end ".text_nmplv";
 


