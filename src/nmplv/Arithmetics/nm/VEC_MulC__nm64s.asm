//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V64N64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V64N64.asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
data ".data_nmplv_G"
	GTmpLong1:long[1];
end ".data_nmplv_G";


begin ".text_nmplv"
extern vec_vsum_data_0:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMulC (nm64s *pSrcVec, int64b nVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC_64s.html

global _nmppsMulC_64s:label;
global _void._.8.8nmppsMulC.1long._.0.9._long.9._long._.0.9._int.2 :label;
<_nmppsMulC_64s>
<_void._.8.8nmppsMulC.1long._.0.9._long.9._long._.0.9._int.2>
.branch;


	ar5 = sp-2		with gr7 = false;
	push ar0,gr0;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5] with gr0=gr7+1;			// pSrcVec
	push ar0,gr0;
	gr6 = [--ar5];
	gr6 = [--ar5];			// Scalar value(Hi)
	ar6 = [--ar5];			// Scalar value(Lo)
	//-- WFIFO init ---------------------------
	nb1 = gr7;
	ar0 = GTmpLong1;
	[ar0] = ar6,gr6 ;
	sb  = gr7;
	rep 1 wfifo=[ar0++],ftw;
	//-----------------------------------------
	pop ar0,gr0;
	ar6 = [--ar5] with gr0++;				// pDstVec
    gr5 = [--ar5] with gr6=gr0;				// nSize

	delayed call vec_vsum_data_0;
		nul;
		wtw;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv"; 
