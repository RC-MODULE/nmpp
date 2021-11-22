//------------------------------------------------------------------------
//
//  $Workfile:: data_add_afifo.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data_add_afifo.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern _nmppsTmpBuffer64_G_:long;

begin ".text_nmvcore"

    //------------------------------------------------------------------------
    //! \fn void vec_data_add_afifo(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6)
    //!
    //------------------------------------------------------------------------

global vec_data_add_afifo:label;
<vec_data_add_afifo>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	
	if =0 delayed goto Sum_rep1 with gr2>>=27;
		rep 1 with vfalse;
		rep 1 [ar6]=afifo;
			
	with gr5--;
	rep 32 data=[ar0++gr0] with data;
	if =0 delayed goto end_Sum_rep32 with gr5--;
		ar2 = _nmppsTmpBuffer64_G_;
	
	<next_Sum_rep32>
	if <>0 delayed goto next_Sum_rep32 with gr5--;
		nul;
		rep 32 data = [ar0++gr0] with data + afifo;
		
	<end_Sum_rep32>
	rep 32 [ar2++]=afifo;

	rep 16 data=[--ar2] with data;
	rep 16 data=[--ar2] with data+afifo;
	rep 16 [ar2++]=afifo;
	
	rep 8 data=[--ar2] with data;
	rep 8 data=[--ar2] with data+afifo;
	rep 8 [ar2++]=afifo;
	
	rep 4 data=[--ar2] with data;
	rep 4 data=[--ar2] with data+afifo;
	rep 4 [ar2++]=afifo;
	
	rep 2 data=[--ar2] with data;
	rep 2 data=[--ar2] with data+afifo;
	rep 2 [ar2++]=afifo;
	
	rep 1 data=[--ar2] with data;
	rep 1 data=[--ar2] with data+afifo;
	rep 1 [ar6]=afifo;
	

	<Sum_rep1>
	with gr5=gr2;
	if =0 delayed goto end_Sum_rep1;
		nul;
		nul;

	rep 1 data=[ar6] with data;
	with gr5--;
	<next_Sum_rep1>
	if <>0 delayed goto next_Sum_rep1 with gr5--;
		nul;
		rep 1 data=[ar0++gr0] with data+afifo;

	rep 1 [ar6]=afifo;
	<end_Sum_rep1>

	pop ar5,gr5;
	pop ar2,gr2;
	delayed return;
		nul;
		nul;
		nul;

return;
.wait;




end ".text_nmvcore";
