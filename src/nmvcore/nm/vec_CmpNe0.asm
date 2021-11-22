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

import from minrep.mlb;
DEF_MIN_REP();

macro VEC_CMP_NE_0(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data,ram = [ar0++gr0] with 0-data ;
		rep N  with activate afifo or activate ram;
		rep N [ar6++gr6] = afifo;
.endif;
end   VEC_CMP_NE_0;

Cmp_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_CmpNe0(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_CmpNe0 :label;
<vec_CmpNe0>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Cmp_repN with gr2>>=25;
		ar2 = Cmp_rep0 with gr5--;
	<next_Cmp_rep32>
		nul;
		rep 32 data,ram = [ar0++gr0] with 0-data;
	if <>0 delayed goto next_Cmp_rep32 with gr5--;
		rep 32 with  activate afifo or activate ram;
		rep 32 [ar6++gr6] = afifo;
	<Cmp_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Cmp_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_CMP_NE_0(1);
	VEC_CMP_NE_0(2);
	VEC_CMP_NE_0(3);
	VEC_CMP_NE_0(4);
	VEC_CMP_NE_0(5);
	VEC_CMP_NE_0(6);
	VEC_CMP_NE_0(7);
	VEC_CMP_NE_0(8);
	VEC_CMP_NE_0(9);
	VEC_CMP_NE_0(10);
	VEC_CMP_NE_0(11);
	VEC_CMP_NE_0(12);
	VEC_CMP_NE_0(13);
	VEC_CMP_NE_0(14);
	VEC_CMP_NE_0(15);
	VEC_CMP_NE_0(16);
	VEC_CMP_NE_0(17);
	VEC_CMP_NE_0(18);
	VEC_CMP_NE_0(19);
	VEC_CMP_NE_0(20);
	VEC_CMP_NE_0(21);
	VEC_CMP_NE_0(22);
	VEC_CMP_NE_0(23);
	VEC_CMP_NE_0(24);
	VEC_CMP_NE_0(25);
	VEC_CMP_NE_0(26);
	VEC_CMP_NE_0(27);
	VEC_CMP_NE_0(28);
	VEC_CMP_NE_0(29);
	VEC_CMP_NE_0(30);
	VEC_CMP_NE_0(31);
return;
.wait;




end ".text_nmvcore";
