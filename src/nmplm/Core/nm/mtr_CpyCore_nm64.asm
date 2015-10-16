//------------------------------------------------------------------------
//
//  $Workfile:: mtrCpyCore_nm64u.asm $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrCpyCore_nm64u.asm
//! \author Павел Лукашевич
//! \brief  Функции ядра для копирования матриц.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern vec_data:label;
begin ".text_nmplm"
/////////////////////////////////////////////////////////////////////////////////
//mtr_CpyCore_nm64
/////////////////////////////////////////////////////////////////////////////////
//	ar0  	Pointer to Src matrix
//	gr1  	Src matrix Stride in 32bit words
//	ar6  	Pointer to Dst matrix
//	gr4  	Dst matrix Stride in 32bit words
//	gr2  	Dst matrix height
//	gr3  	Dst matrix width in 64bit words
/////////////////////////////////////////////////////////////////////////////////
// Registers : |ar0|ar1|   |   |ar4|   |ar6|   |
//			   |gr0|gr1|gr2|gr3|gr4|gr5|gr6|gr7|   will be changed after return !
/////////////////////////////////////////////////////////////////////////////////

global mtr_CpyCore_nm64:label;
<mtr_CpyCore_nm64>

	with gr2 - gr3;
	if > delayed goto ColumnCopy with gr7 = false;
		gr7++;
		gr7++;

//<RowCopy>

	ar4 = ar6 with gr6 = gr7;
	ar1 = ar0 with gr0 = gr7;

<RowCopyRep>

	delayed call vec_data with gr5 = gr3;
		ar1 += gr1;
		ar4 += gr4;
	
	with gr2--;
	if > delayed  goto RowCopyRep;
		ar0 = ar1;
		ar6 = ar4;

return;

<ColumnCopy>//<ColumnCopy>

	ar1 = ar0 with gr0 = gr1;
	ar4 = ar6 with gr6 = gr4; 
	gr1 = gr7 with gr4 = gr7;
	
	
<ColumnCopyRep>

	delayed call vec_data with gr5 = gr2;
		ar1 += gr1;
		ar4 += gr4;
	
	with gr3--;
	if > delayed  goto ColumnCopyRep;
		ar0 = ar1;
		ar6 = ar4;

return;
/////////////////////////////////////////////////////////////////////////////////
.wait;
end ".text_nmplm"; 