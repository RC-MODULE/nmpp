//------------------------------------------------------------------------
//
//  $Workfile:: Math_IncNeg.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   Math_IncNeg.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


macro VEC_INC_NEG_REP(N)
	delayed return;
		rep N data,ram = [ar0++gr0]	with activate data;				
		rep N						with ram - afifo;				
		rep N [ar6++gr6] = afifo;		
end VEC_INC_NEG_REP;

    //------------------------------------------------------------------------
    //! \fn void vec_IncNeg(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_IncNeg :label;
<vec_IncNeg>
.branch;
	IncNeg_rep0: label;
	push ar2,gr2 with gr2=gr5<<27;
	push ar5,gr5 with gr5>>=5;
	if =0 delayed goto IncNeg_repN with gr2>>=25;
		ar2 = IncNeg_rep0 with gr5--;
	<next_IncNeg_rep32>
		rep 32 data,ram = [ar0++gr0]	with activate data;				
		rep 32							with ram - afifo;				
	if <>0 delayed goto next_IncNeg_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6] = afifo;		
	<IncNeg_repN>
	ar2+= gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<IncNeg_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_INC_NEG_REP(1);
	VEC_INC_NEG_REP(2);
	VEC_INC_NEG_REP(3);
	VEC_INC_NEG_REP(4);
	VEC_INC_NEG_REP(5);
	VEC_INC_NEG_REP(6);
	VEC_INC_NEG_REP(7);
	VEC_INC_NEG_REP(8);
	VEC_INC_NEG_REP(9);
	VEC_INC_NEG_REP(10);
	VEC_INC_NEG_REP(11);
	VEC_INC_NEG_REP(12);
	VEC_INC_NEG_REP(13);
	VEC_INC_NEG_REP(14);
	VEC_INC_NEG_REP(15);
	VEC_INC_NEG_REP(16);
	VEC_INC_NEG_REP(17);
	VEC_INC_NEG_REP(18);
	VEC_INC_NEG_REP(19);
	VEC_INC_NEG_REP(20);
	VEC_INC_NEG_REP(21);
	VEC_INC_NEG_REP(22);
	VEC_INC_NEG_REP(23);
	VEC_INC_NEG_REP(24);
	VEC_INC_NEG_REP(25);
	VEC_INC_NEG_REP(26);
	VEC_INC_NEG_REP(27);
	VEC_INC_NEG_REP(28);
	VEC_INC_NEG_REP(29);
	VEC_INC_NEG_REP(30);
	VEC_INC_NEG_REP(31);
return;
.wait;






end ".text_nmvcore";
