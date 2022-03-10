//------------------------------------------------------------------------
//
//  $Workfile:: Log_And.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Log_And.asm
//! \author ������ �������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


import from minrep.mlb;
DEF_MIN_REP();

macro VEC_AND_NOT_REP(N)
.if (NMPP_MIN_REP <= N);
	delayed return;
		rep N data = [ar0++gr0] with data;
		rep N data = [ar1++gr1] with not data and afifo;
		rep N [ar6++gr6] = afifo;
.endif;
end   VEC_AND_NOT_REP;

And_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_AndNot(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6);
    //!
    //------------------------------------------------------------------------

global vec_AndNot :label;
<vec_AndNot>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto And_repN with gr2>>=25;
		ar2 = And_rep0 with gr5--;
	<next_And_rep32>
		rep 32 data = [ar0++gr0] with data;
		rep 32 data = [ar1++gr1] with not data and afifo;
	if <>0 delayed goto next_And_rep32 with gr5--;
		nul;
		rep 32 [ar6++gr6] = afifo;
	<And_repN>
	ar2+=gr2;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<And_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_AND_NOT_REP(1);
	VEC_AND_NOT_REP(2);
	VEC_AND_NOT_REP(3);
	VEC_AND_NOT_REP(4);
	VEC_AND_NOT_REP(5);
	VEC_AND_NOT_REP(6);
	VEC_AND_NOT_REP(7);
	VEC_AND_NOT_REP(8);
	VEC_AND_NOT_REP(9);
	VEC_AND_NOT_REP(10);
	VEC_AND_NOT_REP(11);
	VEC_AND_NOT_REP(12);
	VEC_AND_NOT_REP(13);
	VEC_AND_NOT_REP(14);
	VEC_AND_NOT_REP(15);
	VEC_AND_NOT_REP(16);
	VEC_AND_NOT_REP(17);
	VEC_AND_NOT_REP(18);
	VEC_AND_NOT_REP(19);
	VEC_AND_NOT_REP(20);
	VEC_AND_NOT_REP(21);
	VEC_AND_NOT_REP(22);
	VEC_AND_NOT_REP(23);
	VEC_AND_NOT_REP(24);
	VEC_AND_NOT_REP(25);
	VEC_AND_NOT_REP(26);
	VEC_AND_NOT_REP(27);
	VEC_AND_NOT_REP(28);
	VEC_AND_NOT_REP(29);
	VEC_AND_NOT_REP(30);
	VEC_AND_NOT_REP(31);
return;
.wait;


end ".text_nmvcore";
