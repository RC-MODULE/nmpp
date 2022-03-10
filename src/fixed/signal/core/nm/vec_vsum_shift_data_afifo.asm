//------------------------------------------------------------------------
//
//  $Workfile:: vsum_shift_data_afifo.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   vsum_shift_data_afifo.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern	_nmppsTmpBuffer64_G_:long;
extern vec_data_add_afifo:label;

begin ".text_nmvcore"




macro VEC_ACCMUL_REP(N)
	delayed goto end_AccMul_repN;
		rep N data = [ar0++gr0] with vsum ,shift data,0;
		rep N [ar5++] = afifo;
end   VEC_ACCMUL_REP;


    //------------------------------------------------------------------------
    //! \fn void vec_vsum_shift_data_afifo(nmreg nb1, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6)
    //!
    //------------------------------------------------------------------------

global vec_vsum_shift_data_afifo:label;
<vec_vsum_shift_data_afifo>
.branch;
	AccMul_rep0:label;
	push ar2,gr2 with gr2=gr5<<27;
	push ar5,gr5 with gr5>>=5;	
	push ar4,gr4 with gr4=false noflags;
	
	ar5 = _nmppsTmpBuffer64_G_;
	if =0 delayed goto AccMul_repN with gr2>>=25;
		ar2 = AccMul_rep0  with gr5--;
	
	if =0 delayed goto end_AccMul_rep32 with gr5--;
		rep 32 data = [ar0++gr0] with vsum ,shift data,0;
		gr4++ noflags;

	<next_AccMul_rep32>
	if <>0 delayed goto next_AccMul_rep32 with gr5--;
		nul;
		rep 32 data = [ar0++gr0] with vsum ,shift data,afifo;
		
	<end_AccMul_rep32>
	rep 32 [ar5++]=afifo;
	gr4<<=5;			//gr4=32

	<AccMul_repN>
	ar2+=gr2			with gr2>>=2;
	delayed goto ar2	with gr5=gr4+gr2; 
						with gr2=false;
						with gr2++;
	<AccMul_rep0>
	delayed goto end_AccMul_repN;
		nul;
		nul;
	VEC_ACCMUL_REP(1);
	VEC_ACCMUL_REP(2);
	VEC_ACCMUL_REP(3);
	VEC_ACCMUL_REP(4);
	VEC_ACCMUL_REP(5);
	VEC_ACCMUL_REP(6);
	VEC_ACCMUL_REP(7);
	VEC_ACCMUL_REP(8);
	VEC_ACCMUL_REP(9);
	VEC_ACCMUL_REP(10);
	VEC_ACCMUL_REP(11);
	VEC_ACCMUL_REP(12);
	VEC_ACCMUL_REP(13);
	VEC_ACCMUL_REP(14);
	VEC_ACCMUL_REP(15);
	VEC_ACCMUL_REP(16);
	VEC_ACCMUL_REP(17);
	VEC_ACCMUL_REP(18);
	VEC_ACCMUL_REP(19);
	VEC_ACCMUL_REP(20);
	VEC_ACCMUL_REP(21);
	VEC_ACCMUL_REP(22);
	VEC_ACCMUL_REP(23);
	VEC_ACCMUL_REP(24);
	VEC_ACCMUL_REP(25);
	VEC_ACCMUL_REP(26);
	VEC_ACCMUL_REP(27);
	VEC_ACCMUL_REP(28);
	VEC_ACCMUL_REP(29);
	VEC_ACCMUL_REP(30);
	VEC_ACCMUL_REP(31);	
	<end_AccMul_repN>
	pop  ar4,gr4;
	push ar0,gr0;
	delayed call vec_data_add_afifo with gr0=gr2+1;
		ar0=_nmppsTmpBuffer64_G_;
	pop ar0,gr0;
	pop ar5,gr5;
	pop ar2,gr2;
	delayed return;
		nul;
		nul;
		nul;

return;
.wait;




end ".text_nmvcore";
