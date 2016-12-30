//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinMaxV_8s.asm             $
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
//! \author Сергей Свечников
//! \brief  Elementwise min/max comparision
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_CompareMinMax:label;


begin ".text_nmplv"

//! \fn void  nmppsCmpMinMaxV_8s(nm8s *pSrcVec1, nm8s *pSrcVec2, nm8s *pDstMin, nm8s *pDstMax, int nSize)
//!
//! \perfinclude _nmppsCmpMinMaxV_8s.html

global _nmppsCmpMinMaxV_8s:label;
<_nmppsCmpMinMaxV_8s>
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
	
	
	nb1 =80808080h with gr7>>=3;
	f1cr=80808080h;
	delayed call vec_CompareMinMax;
		wtw;		
		ar5=gr6 with gr6=gr0;	
		
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
