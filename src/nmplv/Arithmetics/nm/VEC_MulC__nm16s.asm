//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V16N32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V16N32.asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
import from macros.mlb;

//********** Global ********************
data ".data_nmplv_G"
	GWScalar:long[4]=(0l,0l,0l,0l);
end ".data_nmplv_G";
//********** Text   ********************
extern vec_vsum_data_0:label;


begin ".text_nmplv"


//! \fn void VEC_MulC (nm16s *pSrcVec, int32b nVal, nm32s *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_MulC__FPSsiPii.html

global _VEC_MulC__FPSsiPii:label;
global _void._.8.8VEC_MulC.1short._.0.9._int.9._int._.0.9._int.2 :label;
<_VEC_MulC__FPSsiPii>
<_void._.8.8VEC_MulC.1short._.0.9._int.9._int._.0.9._int.2>
.branch;


	ar5 = sp-2;
	push ar0,gr0;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5]	with gr0=false; 	// pSrcVec
	gr5 = [--ar5];						// Scalar value - nVal
	
	//-- WFIFO init ---------------------------
	ar6 = GWScalar with gr7 = false;
	gr6 = ar6;
	[ar6++] = gr5;
	[ar6++] = gr7;
	[ar6++] = gr7;
	[ar6++] = gr5;

	nb1 = 80000000h;
	sb  = 00020002h;
	ar6 = gr6;
	rep 4 wfifo=[ar6++],ftw;
	rep 2 wfifo=[--ar6];
	ar6 = gr6;
	rep 2 wfifo=[ar6++];
	
	ar6 = [--ar5]	with gr0++;			// pDstVec
    gr5 = [--ar5]	with gr0++;			// nSize
	
	
				
	

	push ar0,gr0	with gr6=gr0<<1;	// gr6=4
	push ar6,gr6;
	delayed call vec_vsum_data_0 with gr5>>=2;
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
