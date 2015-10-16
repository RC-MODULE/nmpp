//------------------------------------------------------------------------
//
//  $Workfile:: Math_Add.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Add.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"


macro VEC_ADD_REP(N)
	rep N data = [ar0++gr0] with data;
	rep N data = [ar1++gr1] with data + afifo;
	delayed return;
		rep N data = [ar2++gr2] with data + afifo;
		rep N data = [ar3++gr3] with data + afifo;
		rep N [ar6++gr6] = afifo;
	nul;
	nul;
end   VEC_ADD_REP;

Add_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Add4V(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg ar3, nmreg gr3, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Add4V :label;
<vec_Add4V>
.branch;
	push ar4,gr4 with gr4=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Add_repN with gr4>>=24;
		ar4 = Add_rep0 with gr5--;
	next_Add_rep32:label;
	ar5 = next_Add_rep32;
	<next_Add_rep32>
		rep 32 data = [ar0++gr0] with data;
		rep 32 data = [ar1++gr1] with data + afifo;
		rep 32 data = [ar2++gr2] with data + afifo;
	if <>0 delayed goto ar5 with gr5--;	
		rep 32 data = [ar3++gr3] with data + afifo;
		rep 32 [ar6++gr6] = afifo;
		
	<Add_repN>
	ar4+=gr4;
	delayed goto ar4; 
		pop ar5,gr5;
		pop ar4,gr4;
	<Add_rep0>
	nul; nul; nul; nul;
	delayed return;
		nul;
		nul;
		nul;
	VEC_ADD_REP(1);
	VEC_ADD_REP(2);
	VEC_ADD_REP(3);
	VEC_ADD_REP(4);
	VEC_ADD_REP(5);
	VEC_ADD_REP(6);
	VEC_ADD_REP(7);
	VEC_ADD_REP(8);
	VEC_ADD_REP(9);
	VEC_ADD_REP(10);
	VEC_ADD_REP(11);
	VEC_ADD_REP(12);
	VEC_ADD_REP(13);
	VEC_ADD_REP(14);
	VEC_ADD_REP(15);
	VEC_ADD_REP(16);
	VEC_ADD_REP(17);
	VEC_ADD_REP(18);
	VEC_ADD_REP(19);
	VEC_ADD_REP(20);
	VEC_ADD_REP(21);
	VEC_ADD_REP(22);
	VEC_ADD_REP(23);
	VEC_ADD_REP(24);
	VEC_ADD_REP(25);
	VEC_ADD_REP(26);
	VEC_ADD_REP(27);
	VEC_ADD_REP(28);
	VEC_ADD_REP(29);
	VEC_ADD_REP(30);
	VEC_ADD_REP(31);
return;
.wait;




end ".text_nmvcore";
