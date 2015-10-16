//------------------------------------------------------------------------
//
//  $Workfile:: vec_ClipMul2D2W8_AddVr_Ext.asm   $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   vec_ClipMul2D2W8_AddVr_Ext.asm
//! \author Sergey Landyshev
//! \brief  \ru ‘ункции векторного €дра.
//!			\en Vector core function
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmvcore"
//------------------------------------------------------------------------
//! \fn vec_ClipMul2D2W8_AddVr_Ext
//! \ingroup vCore
//! \brief 
//! 
//! ¬звешенное умножение двух массивов с накоплением и активацей
//! ядро функции VEC_ClipPowC_Arsh_Cnv_Add—_Ext().
//! ƒействие функции эквивалентно следующим псевдоинструкци€м:
//! \code
//!		rep 8 wfifo=[ar4++],ftw,wtw;
//!		rep N data =[ar0++gr0] with vsum ,activate data,vr;
//!		rep 8 wfifo=[ar4++],ftw,wtw;	
//!		rep N data =[ar1++gr1] with vsum ,activate data,afifo;
//!		rep N [ar6++gr6]=afifo;
//! \endcode
//!
//! \param nb1  задает разбиение на колонки
//! \param  vr	константа дл€ суммировани€ 
//!
//! \param ar0	SrcMtr1		
//! \param gr0  SrcMtr1 stride 
//!
//! \param ar1  SrcMtr2		
//! \param gr1  SrcMtr2 stride 
//!
//! \param ar2  f1cr дл€ первой группы (адрес €чейки long).
//! \param gr2  f1cr дл€ второй группы (адрес €чейки long).
//!
//! \param ar3  sb дл€ первой группы (адрес €чейки long).
//! \param gr3  sb дл€ второй группы (адрес €чейки long).
//!
//! \param ar4  2 матрицы весовых коэффициентов по 8 64р. слов
//! \param gr4  дублирует nb1 
//!
//! \param gr5  ¬ысота матриц N = [0,1,2...31,32,33,...]
//!
//! \param ar6  DstVec							
//! \param gr6  DstVec  stride 
//!
//!
//! \restr ѕри выходе из функции измен€етс€ содержимое регистров:
//! ar0,ar1,ar6,gr7
//------------------------------------------------------------------------


macro MTR_MUL2D2W8_REP(N)
        sb = [gr3];
		rep N data=[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
 		delayed return; 
            f1cr = [gr2];
    		rep N data=[ar1++gr1]	  with vsum ,activate data,afifo;
			rep N [ar6++gr6]=afifo;	
		nul;
		nul;
end MTR_MUL2D2W8_REP;


global vec_ClipMul2D2W8_AddVr_Ext:label;
      <vec_ClipMul2D2W8_AddVr_Ext>
.branch;
	Mul2D2W8_AddVr_rep0:label;
	Next_Mul2D2W8_AddVr_rep32:label;
	push ar5,gr5	with gr7=gr5>>5;
	ar5 = ar4		with gr5<<=27;
    sb = [ar3];
	rep 16 wfifo=[ar4++],ftw,wtw;
	ar4 = ar5		with gr5>>=24;
	ar5 = Mul2D2W8_AddVr_rep0;
	push ar5,gr5;
	ar5 = ar4		with gr7;
	
	if  =0 delayed goto Mul2D2W8_AddVr_repN with gr7--;
		gr5 = Next_Mul2D2W8_AddVr_rep32;
		
	<Next_Mul2D2W8_AddVr_rep32>
        sb = [gr3];
        f1cr = [ar2];
		rep 32 data =[ar0++gr0],ftw,wtw with vsum ,activate data,vr;
        sb = [ar3];
        f1cr = [gr2];
        rep 16 wfifo=[ar4++],ftw;
	if  <>0 delayed  goto gr5 with gr7--; 
		rep 32 data =[ar1++gr1],wtw		with vsum ,activate data,afifo;
		ar4 = ar5;
		rep 32 [ar6++gr6]=afifo;

	<Mul2D2W8_AddVr_repN>
	pop ar5,gr5;
	f1cr = [ar2];
	ar5+=gr5;
	delayed goto ar5; 
		pop ar5,gr5;
		nul;
	<Mul2D2W8_AddVr_rep0>
	delayed return;
		ftw;
		wtw;
		nul;
	nul;
	nul;
	nul;
	nul;
	MTR_MUL2D2W8_REP(1);
	MTR_MUL2D2W8_REP(2);
	MTR_MUL2D2W8_REP(3);
	MTR_MUL2D2W8_REP(4);
	MTR_MUL2D2W8_REP(5);
	MTR_MUL2D2W8_REP(6);
	MTR_MUL2D2W8_REP(7);
	MTR_MUL2D2W8_REP(8);
	MTR_MUL2D2W8_REP(9);
	MTR_MUL2D2W8_REP(10);
	MTR_MUL2D2W8_REP(11);
	MTR_MUL2D2W8_REP(12);
	MTR_MUL2D2W8_REP(13);
	MTR_MUL2D2W8_REP(14);
	MTR_MUL2D2W8_REP(15);
	MTR_MUL2D2W8_REP(16);
	MTR_MUL2D2W8_REP(17);
	MTR_MUL2D2W8_REP(18);
	MTR_MUL2D2W8_REP(19);
	MTR_MUL2D2W8_REP(20);
	MTR_MUL2D2W8_REP(21);
	MTR_MUL2D2W8_REP(22);
	MTR_MUL2D2W8_REP(23);
	MTR_MUL2D2W8_REP(24);
	MTR_MUL2D2W8_REP(25);
	MTR_MUL2D2W8_REP(26);
	MTR_MUL2D2W8_REP(27);
	MTR_MUL2D2W8_REP(28);
	MTR_MUL2D2W8_REP(29);
	MTR_MUL2D2W8_REP(30);
	MTR_MUL2D2W8_REP(31);
.wait;
//------------------------------------------------------------------------
end ".text_nmvcore";
//------------------------------------------------------------------------