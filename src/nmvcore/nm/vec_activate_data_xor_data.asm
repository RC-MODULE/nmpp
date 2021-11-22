//------------------------------------------------------------------------
//
//  $Workfile:: activate_data.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   activate_data.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"
    
import from minrep.mlb;
DEF_MIN_REP();

macro VEC_ACTIVATE_DATA_XOR_DATA_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data = [ar0++gr0] with activate data xor data;
		rep N [ar6++gr6] = afifo;
		nul;
.endif;
end   VEC_ACTIVATE_DATA_XOR_DATA_REP;


    //------------------------------------------------------------------------
    //! \fn void vec_activate_data_xor_data(nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_activate_data_xor_data :label;
<vec_activate_data_xor_data>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	Activate_rep0 :label;
	if =0 delayed goto Activate_repN with gr2>>=25;
		ar2 = Activate_rep0 with gr5--;
	<next_Activate_rep32>
	if <>0 delayed goto next_Activate_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with activate data xor data;
		rep 32 [ar6++gr6] = afifo;
	<Activate_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Activate_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_ACTIVATE_DATA_XOR_DATA_REP(1);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(2);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(3);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(4);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(5);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(6);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(7);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(8);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(9);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(10);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(11);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(12);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(13);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(14);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(15);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(16);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(17);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(18);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(19);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(20);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(21);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(22);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(23);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(24);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(25);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(26);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(27);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(28);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(29);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(30);
	VEC_ACTIVATE_DATA_XOR_DATA_REP(31);
return;
.wait;





end ".text_nmvcore";
