//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyDspCommon.a $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCopyDspCommon.asm
//! \author Павел Лукашевич
//! \brief  Функции инициализации и копирования для матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_Mul2D2W8_AddVr:label;

data ".data_nmplm_G"

	vec_Wt_Zero:long[8]=(

		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl
		);

	vec_Wt_Dsp08:long[16]=(

		00000000000000001hl,
		00000000000000100hl,
		00000000000010000hl,
		00000000001000000hl,
		00000000100000000hl,
		00000010000000000hl,
		00001000000000000hl,
		00100000000000000hl,

		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl,
		00000000000000000hl
		);


end ".data_nmplm_G";

begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////
//	mtr_CopyDspCore
/////////////////////////////////////////////////////////////////////////////////
//	ar0  	Pointer to Src matrix
//	gr0  	Src matrix Stride in 32bit words
//	ar4  	Pointer to Weight matrix
//	ar6  	Pointer to Dst matrix
//	gr6  	Dst matrix Stride in 32bit words
//	gr2  	Dst matrix height
//	gr3  	Dst matrix width in 64bit words
//	gr7  	nb1 reg
/////////////////////////////////////////////////////////////////////////////////
// Registers : |ar0|ar1|ar2|ar3|   |ar5|ar6|   |
//			   |   |gr1|gr2|gr3|gr4|gr5|   |gr7| will be changed after return !
/////////////////////////////////////////////////////////////////////////////////
global mtr_CopyDspCore:label;
<mtr_CopyDspCore>

	ar4 = vec_Wt_Dsp08 with gr4 = -gr4;
	ar4 +=gr4;

	gr4 = gr7;
	nb1 = gr4 with gr2 - gr3;

	if > delayed goto ColumnCopy;
		gr1 = 2;

//<RowCopy>//<RowCopy>//<RowCopy>//<RowCopy>//<RowCopy>

	push ar0,gr0 with gr0 = gr1;
	push ar6,gr6 with gr6 = gr1;
	
<RowCopyRep>
	
	delayed call vec_Mul2D2W8_AddVr with gr5 = gr3;
		with gr0 = gr1;
		ar1 = ar0 + gr0;
	
	pop ar6,gr6;
	pop ar0,gr0;

	nul;
	nul;

	ar0+=gr0;
	ar6+=gr6;

	push ar0,gr0;
	push ar6,gr6 with gr2--;

	if > delayed  goto RowCopyRep;
		with gr0 = gr1;
		with gr6 = gr1;

	pop ar6,gr6;
	pop ar0,gr0;

return;
//<ColumnCopy>//<ColumnCopy>//<ColumnCopy>//<ColumnCopy>
<ColumnCopy>

	ar3 = ar0;
	ar5 = ar6;
	
<ColumnCopyRep>

	delayed call vec_Mul2D2W8_AddVr with gr5 = gr2;
		ar1 = ar0 + 2 with gr1 = gr0;
	
	ar0 = ar3 + 2;
	ar6 = ar5 + 2 with gr3--;
	
	if > delayed  goto ColumnCopyRep;
		ar3 = ar0;
		ar5 = ar6;

return;
.wait;
end ".text_nmplm"; 