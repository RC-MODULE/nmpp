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
	nRandomize:long=0l;
	RandMul:long=1664525L;
	RandAdd:long=1013904223L;
end ".data_nmplv_G";


begin ".text_nmplv"



////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void VEC_Rand (nm64s *pDstVec, int nSize, int nRandomize=1) 
//!
//! \perfinclude _VEC_Rand__FPlii.html
//--------------------------------------------------------------------
    
global _VEC_Rand__FPlii:label;
global _void._.8.8VEC_Rand.1long._.0.9._int.9._int.2 :label;
<_VEC_Rand__FPlii>
<_void._.8.8VEC_Rand.1long._.0.9._int.9._int.2>
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
	gr6 = [--ar5];			// Random
	ar5 = nRandomize;
	vr  = [RandAdd];
	[ar5] = gr6	with gr6=false;
	with gr7--;
	if < delayed goto end_Random;
		//WTW_REG(gr6);
		wtw;
		nul;
		
	if =0 delayed goto last_Random_rep1 with gr7--;
		rep 1 data=[ar5] with vsum ,data,vr;
		nul;
	<next_Random_rep1>
	if <>0 delayed goto next_Random_rep1 with gr7--;
		rep 1 [ar6++]=afifo with vsum ,afifo,vr;
		nul;
	
	<last_Random_rep1>
	rep 1 [ar6++]	=afifo;
	<end_Random>
	pop ar6,gr6;
	return;
.wait;




end ".text_nmplv";