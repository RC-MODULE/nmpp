//------------------------------------------------------------------------
//
//  $Workfile:: vsum_activate_data_0.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   vsum_activate_data_0.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"




macro VEC_MUL_ACTIVATE_DATA_0_REP(N)
	delayed return;
		rep N data=[ar0++gr0]	with vsum , activate data,0;
		rep N [ar6++gr6]=afifo;
		nul;
end VEC_MUL_ACTIVATE_DATA_0_REP;


    //------------------------------------------------------------------------
    //! \fn void vec_vsum_activate_data_0(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

<vec_vsum_activate_data_0>
global vec_vsum_activate_data_0:label;
.branch;
	MulActivateData_rep0:label;
	push ar2,gr2 with gr2=gr5<<27;
	push ar5,gr5 with gr5>>=5;
	if =0 delayed goto MulActivateData_repN with gr2>>=25;
		ar2 = MulActivateData_rep0 with gr5--;
	
	<NextMulActivateData_rep32>
	if <>0 delayed goto NextMulActivateData_rep32 with gr5--;
		rep 32 data =[ar0++gr0]	with vsum , activate data, 0;
		rep 32 [ar6++gr6]=afifo;
	<MulActivateData_repN>
	ar2+=gr2;
	delayed goto ar2 ; 
		pop ar5,gr5;
		pop ar2,gr2;
	<MulActivateData_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_MUL_ACTIVATE_DATA_0_REP(1);
	VEC_MUL_ACTIVATE_DATA_0_REP(2);
	VEC_MUL_ACTIVATE_DATA_0_REP(3);
	VEC_MUL_ACTIVATE_DATA_0_REP(4);
	VEC_MUL_ACTIVATE_DATA_0_REP(5);
	VEC_MUL_ACTIVATE_DATA_0_REP(6);
	VEC_MUL_ACTIVATE_DATA_0_REP(7);
	VEC_MUL_ACTIVATE_DATA_0_REP(8);
	VEC_MUL_ACTIVATE_DATA_0_REP(9);
	VEC_MUL_ACTIVATE_DATA_0_REP(10);
	VEC_MUL_ACTIVATE_DATA_0_REP(11);
	VEC_MUL_ACTIVATE_DATA_0_REP(12);
	VEC_MUL_ACTIVATE_DATA_0_REP(13);
	VEC_MUL_ACTIVATE_DATA_0_REP(14);
	VEC_MUL_ACTIVATE_DATA_0_REP(15);
	VEC_MUL_ACTIVATE_DATA_0_REP(16);
	VEC_MUL_ACTIVATE_DATA_0_REP(17);
	VEC_MUL_ACTIVATE_DATA_0_REP(18);
	VEC_MUL_ACTIVATE_DATA_0_REP(19);
	VEC_MUL_ACTIVATE_DATA_0_REP(20);
	VEC_MUL_ACTIVATE_DATA_0_REP(21);
	VEC_MUL_ACTIVATE_DATA_0_REP(22);
	VEC_MUL_ACTIVATE_DATA_0_REP(23);
	VEC_MUL_ACTIVATE_DATA_0_REP(24);
	VEC_MUL_ACTIVATE_DATA_0_REP(25);
	VEC_MUL_ACTIVATE_DATA_0_REP(26);
	VEC_MUL_ACTIVATE_DATA_0_REP(27);
	VEC_MUL_ACTIVATE_DATA_0_REP(28);
	VEC_MUL_ACTIVATE_DATA_0_REP(29);
	VEC_MUL_ACTIVATE_DATA_0_REP(30);
	VEC_MUL_ACTIVATE_DATA_0_REP(31);


return;
.wait;

end ".text_nmvcore";
