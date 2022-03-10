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
//! \brief  ���������� ������� 3
//!
//! \endif
//!
//------------------------------------------------------------------------

extern 	tbl_LUT_Median3:word[8];



begin ".text_nmpls"

//! \fn uint32b SIG_Median3(uint32b a, uint32b b, uint32b c)
//! \perfinclude _SIG_Median3__FUiUiUi.html
global _SIG_Median3__FUiUiUi:label;
global _unsigned._int._.8.8SIG_Median3.1unsigned.9._unsigned.9._unsigned.2 :label;
<_SIG_Median3__FUiUiUi>
<_unsigned._int._.8.8SIG_Median3.1unsigned.9._unsigned.9._unsigned.2>
.branch;
    ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1 with gr7=false;

	gr0 = [--ar5]; // a
	gr1 = [--ar5]; // b
	push ar2,gr2			with gr0 - gr1;
	gr2 = [--ar5]			with gr7 C<<=1;
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

