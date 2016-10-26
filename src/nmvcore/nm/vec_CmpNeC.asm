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


macro VEC_CMP_NE_C(N)
	rep N data= [ar0++gr0] with vsum ,data,vr;
	rep N [ar7],ram = afifo with 0-afifo ;
	delayed return;
		rep N  with activate afifo or activate ram;
		rep N [ar6++gr6] = afifo;
		nul;
	nul;
	nul;
end   VEC_CMP_NE_C;

Cmp_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_CmpNeC(nmreg nb1,nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6 )
    //!
    //------------------------------------------------------------------------

global vec_CmpNeC :label;
<vec_CmpNeC>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Cmp_repN with gr2>>=24;
		ar2 = Cmp_rep0 with gr5--;
	<next_Cmp_rep32>
		rep 32 data= [ar0++gr0] with vsum ,data,vr;
		rep 32 [ar7],ram = afifo with 0-afifo;
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
	nul;
	nul;
	nul;
	nul;
	VEC_CMP_NE_C(1);
	VEC_CMP_NE_C(2);
	VEC_CMP_NE_C(3);
	VEC_CMP_NE_C(4);
	VEC_CMP_NE_C(5);
	VEC_CMP_NE_C(6);
	VEC_CMP_NE_C(7);
	VEC_CMP_NE_C(8);
	VEC_CMP_NE_C(9);
	VEC_CMP_NE_C(10);
	VEC_CMP_NE_C(11);
	VEC_CMP_NE_C(12);
	VEC_CMP_NE_C(13);
	VEC_CMP_NE_C(14);
	VEC_CMP_NE_C(15);
	VEC_CMP_NE_C(16);
	VEC_CMP_NE_C(17);
	VEC_CMP_NE_C(18);
	VEC_CMP_NE_C(19);
	VEC_CMP_NE_C(20);
	VEC_CMP_NE_C(21);
	VEC_CMP_NE_C(22);
	VEC_CMP_NE_C(23);
	VEC_CMP_NE_C(24);
	VEC_CMP_NE_C(25);
	VEC_CMP_NE_C(26);
	VEC_CMP_NE_C(27);
	VEC_CMP_NE_C(28);
	VEC_CMP_NE_C(29);
	VEC_CMP_NE_C(30);
	VEC_CMP_NE_C(31);
return;
.wait;




end ".text_nmvcore";
