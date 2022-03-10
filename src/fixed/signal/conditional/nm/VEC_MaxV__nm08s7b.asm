//------------------------------------------------------------------------
//
//  $Workfile:: CompareMaxV_8s.asm             $
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

extern vec_CompareMax:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMaxEvery_8s(nm8s7b*  pSrcVec1, nm8s7b* pSrcVec2,  nm8s7b*  pDstMax, int nSize);
//!
//! \perfinclude _nmppsMaxEvery_8s.html

global _nmppsMaxEvery__FPcPcPci_ :label;
global _nmppsMaxEvery_8s:label;
<_nmppsMaxEvery_8s>

.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	push ar1,gr1	with gr0++;
	push ar3,gr3;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr1=gr0;

	ar0 = [--ar5] with gr6=gr0;		    // pSrcVec1
	ar1 = [--ar5];						// pSrcVec2
	ar6 = [--ar5];						// pDstMin
	gr5 = [--ar5];						// nSize
	
	
	nb1 =80808080h with gr5>>=3;
	f1cr=80808080h;
	delayed call vec_CompareMax;
		wtw;
		ar3 = ar1 with gr3 = gr1;
		
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar3,gr3;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
