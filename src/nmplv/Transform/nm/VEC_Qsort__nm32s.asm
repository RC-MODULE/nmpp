//------------------------------------------------------------------------
//
//  $Workfile:: QuickSort.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   QuickSort.asm
//! \author Павел Лукашевич
//! \brief  Функции сортировки.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmplv"
////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_QSort (nm32s *pSrcDstVec, int nSize) 
//!
//! \perfinclude _VEC_QSort__FPii.html

global _VEC_QSort__FPii : label;
global _void._.8.8VEC_QSort.1int._.0.9._int.2 :label;
<_VEC_QSort__FPii>
<_void._.8.8VEC_QSort.1int._.0.9._int.2>
.branch;  

	ar5 = sp - 2;
	
	push ar0, gr0;// Registers saving
	push ar1, gr1;// Registers saving
	push ar2, gr2;// Registers saving
	push ar3, gr3;// Registers saving
	push ar4, gr4;// Registers saving
	push ar5, gr5;// Registers saving
	push ar6, gr6;// Registers saving

		gr0 = [--ar5];		//	Source;
		ar0 = [--ar5];		//	Num;
	
		push	ar0,gr0;
	
	call NextSort;			//Start massive
		pop		ar0,gr0;

	pop ar6, gr6;// Registers saving
	pop ar5, gr5;// Registers saving
	pop ar4, gr4;// Registers saving
	pop ar3, gr3;// Registers saving
	pop ar2, gr2;// Registers saving
	pop ar1, gr1;// Registers saving
	pop ar0, gr0;// Registers saving

	return;

//////////////////////////////////////////////////////////////
<NextSort>

	ar5 = sp - 2;

	gr4 = [--ar5];					//Above address	
	gr0 = [--ar5] with gr5 = gr4;	//Count;

	gr0--;
	if <= delayed return;
		gr6 = gr5 + gr0;			//Below address	
	
	gr7 = [gr5];
<LowLoop>
	gr2 = [gr6];
	gr2 - gr7;
	if <= goto HighLoop;

	delayed goto LowLoop;
		gr6--;
		nul;
<HighLoop>
	gr5 - gr6;
	if =0 goto Middle;

	gr5++;
	gr1 = [gr5];
	gr1 - gr7;
	if < delayed goto HighLoop;
		gr1 = [gr5];
		gr2 = [gr6];

	delayed	goto LowLoop;
		[gr5] = gr2;
		[gr6] = gr1;
	
<Middle>
	gr1 = [gr5];
	[gr5] = gr7;
	[gr4] = gr1;

	gr7 = gr5 - gr4;			//high massive lenth
	gr0 -= gr7;					//low massive lenth

	push	gr0	with gr5++;		//low massive data
	push	gr5;				//low massive data

	push	gr7;				//high massive data
	push	gr4;				//high massive data


	call NextSort;				//high massive
		pop		ar0,gr0;
	
	call NextSort;				//low massive
		pop		ar0,gr0;

	return;

//////////////////////////////////////////////////////////////
end ".text_nmplv";
