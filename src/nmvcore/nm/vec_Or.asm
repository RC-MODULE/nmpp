//------------------------------------------------------------------------
//
//  $Workfile:: Log_Or.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Log_Or.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


macro VEC_OR_REP(N)
	delayed return;
		rep N data = [ar0++gr0] with data;
		rep N data = [ar1++gr1] with data or afifo;
		rep N [ar6++gr6] = afifo;
end   VEC_OR_REP;

Or_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Or(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Or :label;
<vec_Or>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Or_repN with gr2>>=25;
		ar2 = Or_rep0 with gr5--;
	<next_Or_rep32>
		rep 32 data = [ar0++gr0] with data;
		rep 32 data = [ar1++gr1] with data or afifo;
	if <>0 delayed goto next_Or_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6] = afifo;
	<Or_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Or_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_OR_REP(1);
	VEC_OR_REP(2);
	VEC_OR_REP(3);
	VEC_OR_REP(4);
	VEC_OR_REP(5);
	VEC_OR_REP(6);
	VEC_OR_REP(7);
	VEC_OR_REP(8);
	VEC_OR_REP(9);
	VEC_OR_REP(10);
	VEC_OR_REP(11);
	VEC_OR_REP(12);
	VEC_OR_REP(13);
	VEC_OR_REP(14);
	VEC_OR_REP(15);
	VEC_OR_REP(16);
	VEC_OR_REP(17);
	VEC_OR_REP(18);
	VEC_OR_REP(19);
	VEC_OR_REP(20);
	VEC_OR_REP(21);
	VEC_OR_REP(22);
	VEC_OR_REP(23);
	VEC_OR_REP(24);
	VEC_OR_REP(25);
	VEC_OR_REP(26);
	VEC_OR_REP(27);
	VEC_OR_REP(28);
	VEC_OR_REP(29);
	VEC_OR_REP(30);
	VEC_OR_REP(31);
return;
.wait;




end ".text_nmvcore";
