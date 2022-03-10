//------------------------------------------------------------------------
//
//  $Workfile:: Filter5exe.asm  $
//
//  
//  
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $       $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file    sig003.asm
//! \author S.Muskaev
//! \brief  Вычисление Медиана 3
//!
//! \endif
//!
//------------------------------------------------------------------------

 import from macros.mlb;


data ".data_nmpls_G"
global	tbl_LUT_Median3:word[8] =(
					1,	// 000 a<b  a<c  b<c	med=b
					0,	// 001 a<b  a<c  b>=c	med=c
					-1,	// 010 a<b  a>=c b<c	impossible
					2,	// 011 a<b  a>=c b>=c	med=a
					2,	// 100 a>=b a<c  b<c	med=a
					-1,	// 101 a>=b a<c  b>=c	impossible
					0,	// 110 a>=b a>=c b<c	med=c
					1	// 111 a>=b a>=c b>=c	med=b
					);
end ".data_nmpls_G";



begin ".text_nmpls"
//! \fn int SIG_Median3(int a, int b, int c);
//! \perfinclude _SIG_Median3__Fiii.html
global _SIG_Median3__Fiii:label;
global _int._.8.8SIG_Median3.1int.9._int.9._int.2 :label;
<_SIG_Median3__Fiii>
<_int._.8.8SIG_Median3.1int.9._int.9._int.2>
.branch;
    ar5 = ar7 - 2			with gr7=true;
	push ar0,gr0			with gr7<<=31;
	push ar1,gr1;			
	gr0 = [--ar5];									 // a
	gr1 = [--ar5]			with gr0 = gr0 xor gr7;  // b
	push ar2,gr2			with gr1 = gr1 xor gr7;
	gr2 = [--ar5]			with gr0 - gr1;
							with gr2 = gr2 xor gr7 noflags;							
							with gr7 = gr7 C<<1;
	ar1 = ar5				with gr0 - gr2; // c
							with gr7 C<<=1;
	ar0 = tbl_LUT_Median3	with gr1 - gr2;
	pop ar2,gr2				with gr0 = gr7 C<<1;
	gr1 = [ar0+=gr0];
	gr7 = [ar1+=gr1];

	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;

end ".text_nmpls";

