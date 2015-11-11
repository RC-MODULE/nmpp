//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinV_64s.asm            $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   CompareMinV_8s.asm
//! \author S. Mushkaev
//! \brief  Elementwise min comparision
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_CompareMin:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMinEvery_64s(nm64s63b* pSrcVec1, nm64s63b* pSrcVec2, nm64s63b* pDstMax, int nSize);
//!
//! \perfinclude _nmppsMinEvery_64s.html

global _nmppsMinEvery__FPlPlPli_ :label;
global _nmppsMinEvery_64s:label;
<_nmppsMinEvery_64s>
.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	nb1 = gr0;
	f1crl=gr0;
	wtw;

	push ar1,gr1	with gr0++;
	push ar3,gr3;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr1=gr0;

	ar0 = [--ar5] with gr6=gr0;		    // pSrcVec1
	ar1 = [--ar5];						// pSrcVec2
	ar6 = [--ar5];						// pDstMin
	gr5 = [--ar5];						// nSize
	
	
	ar3 = ar1 with gr3 = gr1;
	delayed call vec_CompareMin;
		f1crh=80000000h;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar3,gr3;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
