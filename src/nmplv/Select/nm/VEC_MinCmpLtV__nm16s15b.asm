//------------------------------------------------------------------------
//
//  $Workfile:: Min.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   Min.asm
//! \author Сергей Мушкаев
//! \brief  Статистические функции.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern	_nmppsTmpBuffer64_G_: long;
//********** Global ********************
data ".data_nmplv_G"
	GTmpLong1:  long;
end ".data_nmplv_G";
//********** Text   ********************


begin ".text_nmplv"

/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMinCmpLtV_16s(nm16s15b *pSrcVec1, nm16s15b *pSrcVec2, nm16s15b *pDstMin, nm16s15b *pDstSignMask, int nSize) 
//!		
//! \perfinclude _nmppsMinCmpLtV__FPSsPSsPSsPSsi_.html

global _nmppsMinCmpLtV__FPSsPSsPSsPSsi_ :label; 
global _void._.8.8nmppsMinCmpLtV_.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2:label;
 <_nmppsMinCmpLtV__FPSsPSsPSsPSsi_> 
 <_void._.8.8nmppsMinCmpLtV_.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2> 
 .branch; ar5=sp-2; push ar0,gr0	with gr0=false; push ar1,gr1	with 
 gr0++; push ar4,gr4	with gr0++; push ar5,gr5	with gr1=gr0; push ar6,gr6	
 with gr4=gr0;

	ar0 = [--ar5]	with gr6=gr0;		// A Buffer
	ar1 = [--ar5];						// B Buffer
	ar6 = [--ar5];						// Min Buffer
	ar4 = [--ar5];						// Mask Buffer
	gr5 = [--ar5];						// nSize in 16-bit elements
	
	nb1 =80008000h with gr5>>=2;
	wtw;
	delayed call vec_reg_MinMask;
		f1cr=80008000h;
		
		
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;

return;
.wait;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Register interface MinMask function 
// Bit capacity of vector and activate parameters
// are determined by current states of nb1 and f1cr registers before the function call.
//
// INPUT REGISTERS:
// ar0->pSrcVec1												:long Global[size/2]
// gr0= pSrcVec1 long to long reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar1->pSrcVec2												:long Global[size/2]
// gr1= pSrcVec2 long to long reading step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar4->MaskVector												:long Local [size/2]
// gr4= MaskVector  long to long writing step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// ar6->pDstVec												:long Local [size/2]
// gr6= pDstVec  long to long writing step  in 32-bit words	:=[....-4,-2,0,2,4,...]
//
// gr5= nVal - vector's size in 64-bit words(longs)				:=[0,1,2,3..]
//
// nb1 (Bit partition)		must be previously set
// f1cr(Activate register)	must be previously set
//
// NOTE:  There are no stack operations for some input registers,
// Registers : ar0|ar1|   |   |ar4|   |ar6|   |  will be changed after return !
//			      |   |   |   |   |   |   |   |    
global vec_reg_MinMask:label;
<vec_reg_MinMask>
	push ar3,gr3	with gr3=gr5;	
	push ar5,gr5	with gr5>>=5;

	if =0 delayed goto MinMask_rep1;
		push ar2,gr2 with gr2=gr1;
		ar2=ar1		 with gr5--;
		
	<Next_MinMask_rep32>
		rep 32 ram=[ar0++gr0];							// Read pSrcVec1
		rep 32 data=[ar1++gr1]	with ram-data;			// Read pSrcVec2
		rep 32					with activate afifo;	//
		rep 32 [ar4++gr4]=afifo with afifo;				// Write MaskVector
	if <>0 delayed goto Next_MinMask_rep32 with gr5--; 
		rep 32 data=[ar2++gr2]  with mask afifo,ram,data;
		rep 32 [ar6++gr6]=afifo;						// Write pDstVec

	<MinMask_rep1>
	with gr5=gr3<<27;
	with gr5>>=27;
	if =0 delayed goto End_MinMask with gr5--;
		nul;
		nul;
	
	<Next_MinMask_rep1>
		rep 1 ram=[ar0++gr0];
		rep 1 data=[ar1++gr1]	with ram-data;
		rep 1					with activate afifo;
		rep 1 [ar4++gr4]=afifo with afifo;
	if <>0 delayed goto Next_MinMask_rep1 with gr5--; 
		rep 1 data=[ar2++gr2]  with mask afifo,ram,data;
		rep 1 [ar6++gr6]=afifo;

	<End_MinMask>
	pop ar2,gr2;
	pop ar5,gr5;
	pop ar3,gr3;
return;

end ".text_nmplv";
