//------------------------------------------------------------------------
//
//  $Workfile:: Log_Xor.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   Log_Xor.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


macro VEC_XOR_REP(N)
	delayed return;
		rep N data = [ar0++gr0] with data;
		rep N data = [ar1++gr1] with data xor afifo;
		rep N [ar6++gr6] = afifo;
end   VEC_XOR_REP;

Xor_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Xor(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_Xor :label;
<vec_Xor>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Xor_repN with gr2>>=25;
		ar2 = Xor_rep0 with gr5--;
	<next_Xor_rep32>
		rep 32 data = [ar0++gr0] with data;
		rep 32 data = [ar1++gr1] with data xor afifo;
	if <>0 delayed goto next_Xor_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6] = afifo;
	<Xor_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Xor_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_XOR_REP(1);
	VEC_XOR_REP(2);
	VEC_XOR_REP(3);
	VEC_XOR_REP(4);
	VEC_XOR_REP(5);
	VEC_XOR_REP(6);
	VEC_XOR_REP(7);
	VEC_XOR_REP(8);
	VEC_XOR_REP(9);
	VEC_XOR_REP(10);
	VEC_XOR_REP(11);
	VEC_XOR_REP(12);
	VEC_XOR_REP(13);
	VEC_XOR_REP(14);
	VEC_XOR_REP(15);
	VEC_XOR_REP(16);
	VEC_XOR_REP(17);
	VEC_XOR_REP(18);
	VEC_XOR_REP(19);
	VEC_XOR_REP(20);
	VEC_XOR_REP(21);
	VEC_XOR_REP(22);
	VEC_XOR_REP(23);
	VEC_XOR_REP(24);
	VEC_XOR_REP(25);
	VEC_XOR_REP(26);
	VEC_XOR_REP(27);
	VEC_XOR_REP(28);
	VEC_XOR_REP(29);
	VEC_XOR_REP(30);
	VEC_XOR_REP(31);
return;
.wait;



end ".text_nmvcore";
