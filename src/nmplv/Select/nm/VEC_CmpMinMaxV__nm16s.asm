//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinMaxV_16s.asm            $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   CompareMinMaxV_16s.asm
//! \author Сергей Свечников
//! \brief  Elementwise min/max comparision
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_CompareMinMax:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void  nmppsCmpMinMaxV_16s(nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstMin, nm16s *pDstMax, int nSize)
//!
//! \perfinclude _nmppsCmpMinMaxV_16s.html

global _nmppsCmpMinMaxV__FPSsPSsPSsPSsi_ :label;
global _nmppsCmpMinMaxV_16s:label;
<_nmppsCmpMinMaxV_16s>
.branch;
	ar5=sp-2;
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++;
    push ar2,gr2 with gr0++;
	push ar3,gr3 with gr1=gr0;
	push ar4,gr4 with gr3=gr0;
	push ar5,gr5 with gr4=gr0;
	push ar6,gr6;

	ar0 = [--ar5];		        // pSrcVec1
	ar1 = [--ar5];			    // pSrcVec2
	gr6 = [--ar5];			    // pDstMin
    ar6 = [--ar5];              // pDstMax
	gr7 = [--ar5]with gr5=gr0;  // nSize
	ar5=gr6 with gr6=gr0;
	
	nb1 =80008000h with gr7>>=2;
	wtw;
	delayed call vec_CompareMinMax;
		f1cr=80008000h;
		
	pop ar6,gr6;
	pop ar5,gr5;
    pop ar4,gr4;
	pop ar3,gr3;
	pop ar1,gr1;
    pop ar2,gr2;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
