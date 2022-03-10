//------------------------------------------------------------------------
//
//  $Workfile:: Mem_Swap.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   Mem_Swap.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"

 

macro VEC_SWAP_REP(N)
		rep N ram =[ar0++gr0];
		rep N data=[ar1++gr1]	with data;
	delayed return;
		rep N [ar6++gr6]=afifo	with ram;
		rep N [ar4++gr4]=afifo;
		nul;
	nul;
	nul;
end VEC_SWAP_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_Swap(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

<vec_Swap>
global vec_Swap:label;
.branch;
	Swap_rep0:label;
	push ar2,gr2 with gr2=gr5<<27;
	push ar5,gr5 with gr5>>=5;
	if =0 delayed goto Swap_repN with gr2>>=24;
		ar2 = Swap_rep0 with gr5--;
	
	<Next_Swap_rep32>
		rep 32 ram =[ar0++gr0];
		rep 32 data=[ar1++gr1]	with data;
	if <>0 delayed goto Next_Swap_rep32 with gr5--;
		rep 32 [ar6++gr6]=afifo	with ram;
		rep 32 [ar4++gr4]=afifo;
	<Swap_repN>
	ar2+=gr2;
	delayed goto ar2 ; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Swap_rep0>
	delayed return;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	VEC_SWAP_REP(1);
	VEC_SWAP_REP(2);
	VEC_SWAP_REP(3);
	VEC_SWAP_REP(4);
	VEC_SWAP_REP(5);
	VEC_SWAP_REP(6);
	VEC_SWAP_REP(7);
	VEC_SWAP_REP(8);
	VEC_SWAP_REP(9);
	VEC_SWAP_REP(10);
	VEC_SWAP_REP(11);
	VEC_SWAP_REP(12);
	VEC_SWAP_REP(13);
	VEC_SWAP_REP(14);
	VEC_SWAP_REP(15);
	VEC_SWAP_REP(16);
	VEC_SWAP_REP(17);
	VEC_SWAP_REP(18);
	VEC_SWAP_REP(19);
	VEC_SWAP_REP(20);
	VEC_SWAP_REP(21);
	VEC_SWAP_REP(22);
	VEC_SWAP_REP(23);
	VEC_SWAP_REP(24);
	VEC_SWAP_REP(25);
	VEC_SWAP_REP(26);
	VEC_SWAP_REP(27);
	VEC_SWAP_REP(28);
	VEC_SWAP_REP(29);
	VEC_SWAP_REP(30);
	VEC_SWAP_REP(31);
return;
.wait;


end ".text_nmvcore";
