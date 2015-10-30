//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V32N64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V32N64.asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_vsum_data_0:label;

data ".data_nmplv_G"
	GWScalar:long[2]=(0l,0l);
end ".data_nmplv_G";


begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMulC (nm32s *pSrcVec, int64b nVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsMulC__FPilPli.html

global _nmppsMulC__FPilPli:label;
global _void._.8.8nmppsMulC.1int._.0.9._long.9._long._.0.9._int.2 :label;
<_nmppsMulC__FPilPli>
<_void._.8.8nmppsMulC.1int._.0.9._long.9._long._.0.9._int.2>
.branch;


	ar5 = sp-2;
	push ar0,gr0	with gr0=false;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr0++;			// gr0=2

	ar0 = [--ar5];			// pSrcVec
	push ar0,gr0;
	gr6 = [--ar5];
	gr6 = [--ar5];			// Scalar value(Hi)
	ar6 = [--ar5];			// Scalar value(Lo)
	//-- WFIFO init ---------------------------
	ar0 = GWScalar;
	[ar0] = ar6,gr6 with gr7 = false;
	nb1 = gr7;
	sb  = gr0;
	rep 2 wfifo=[ar0++],ftw;
	rep 2 wfifo=[--ar0];
	//-----------------------------------------
	pop ar0,gr0;
	ar6 = [--ar5];			// pDstVec
    gr5 = [--ar5];			// nSize
	
	push ar0,gr0	with gr6=gr0<<1;	// gr6=4
	push ar6,gr6;
	delayed call vec_vsum_data_0 with gr5 >>= 1;
		wtw;
		ftw;
	pop ar6,gr6;
	pop ar0,gr0;

	wtw;
	delayed call vec_vsum_data_0;
		ar6+=2;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv"; 
