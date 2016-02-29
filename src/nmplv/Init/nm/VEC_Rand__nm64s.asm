//------------------------------------------------------------------------
//
//  $Workfile:: InitRandom.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file   InitRandom.asm
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vMinMax.h"

extern vec_ram:label;
import from macros.mlb;
data ".data_nmplv_L"
end ".data_nmplv_L";

data ".data_nmplv_G"
	//nRandomize:long=0FFFFFFFFhl;
	nRandomize:long=0;//0100000001hl;
	RandMul:long=1664525L;
	RandAdd:long=1013904223L;
end ".data_nmplv_G";


begin ".text_nmplv"



////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void nmppsRandUniform_64s(nm64s *pDstVec, int nSize); //, int nRandomize=1) 
//!
//! \perfinclude _nmppsRandUniform_64s.html
//--------------------------------------------------------------------
    
global _nmppsRandUniform_64s:label;
<_nmppsRandUniform_64s>
.branch;
    
	gr7 = false;
	nb1 = gr7;
	sb  = gr7;
	ar5 = RandMul;
	rep 1 wfifo=[ar5],ftw;

	ar5 = sp - 2;
    push ar6,gr6;

    ar6 = [--ar5];			// Buffer
    gr7 = [--ar5];			// nSize
	//gr6 = [--ar5];			// Random
	ar5 = nRandomize with gr6=false;
	vr  = [RandAdd]  with gr7--;
	//[ar5] = gr6	
	if < delayed goto end_Random;
		//WTW_REG(gr6);
		wtw;
		nul;
		
	if =0 delayed goto last_Random_rep1 with gr7--;
		rep 1 data=[ar5] with vsum ,shift data,vr;
		nul;
	<next_Random_rep1>
	if <>0 delayed goto next_Random_rep1 with gr7--;
		rep 1 [ar6++]=afifo with vsum ,shift afifo,vr;
		nul;
	
	<last_Random_rep1>
	rep 1 [ar6++]	=afifo with afifo;
	rep 1 [ar5] = afifo;
	<end_Random>
	pop ar6,gr6;
	return;
.wait;




end ".text_nmplv";