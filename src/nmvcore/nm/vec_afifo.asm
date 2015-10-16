//------------------------------------------------------------------------
//
//  $Workfile:: afifo.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   afifo.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


        

macro VEC_INIT_REP(N)
	delayed return;
		rep N data = [ar0] with data;
		rep N [ar6++gr6] = afifo;
		nul;
end VEC_INIT_REP;

Init_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_afifo(nmreg ar0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_afifo :label;
<vec_afifo>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Init_repN with gr2>>=25;
		ar2 = Init_rep0 with gr5--;

	if =0 delayed goto last_Init_rep32 with gr5--;
		rep 32 data=[ar0] with data;
	<next_Init_rep32>
	if <>0 delayed goto next_Init_rep32 with gr5--;
		rep 32 [ar6++gr6] = afifo with afifo;
		nul;
	<last_Init_rep32>
		rep 32 [ar6++gr6] = afifo;
	<Init_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Init_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_INIT_REP(1);
	VEC_INIT_REP(2);
	VEC_INIT_REP(3);
	VEC_INIT_REP(4);
	VEC_INIT_REP(5);
	VEC_INIT_REP(6);
	VEC_INIT_REP(7);
	VEC_INIT_REP(8);
	VEC_INIT_REP(9);
	VEC_INIT_REP(10);
	VEC_INIT_REP(11);
	VEC_INIT_REP(12);
	VEC_INIT_REP(13);
	VEC_INIT_REP(14);
	VEC_INIT_REP(15);
	VEC_INIT_REP(16);
	VEC_INIT_REP(17);
	VEC_INIT_REP(18);
	VEC_INIT_REP(19);
	VEC_INIT_REP(20);
	VEC_INIT_REP(21);
	VEC_INIT_REP(22);
	VEC_INIT_REP(23);
	VEC_INIT_REP(24);
	VEC_INIT_REP(25);
	VEC_INIT_REP(26);
	VEC_INIT_REP(27);
	VEC_INIT_REP(28);
	VEC_INIT_REP(29);
	VEC_INIT_REP(30);
	VEC_INIT_REP(31);
return;
.wait;



end ".text_nmvcore";
