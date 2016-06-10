//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinV_8s.asm             $
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

extern vec_CmpLtV:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCmpLt_8s7b(nm8s*  pSrcVec1, nm8s* pSrcVec2,  nm8s*  pDstMin, int nSize);
//!
//! \perfinclude _nmppsCmpLt_8s7b.html

global _nmppsCmpLt_8s7b:label;
<_nmppsCmpLt_8s7b>
.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	push ar1,gr1	with gr0++;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr1=gr0;

	ar0 = [--ar5] with gr6=gr0;		    // pSrcVec1
	ar1 = [--ar5];						// pSrcVec2
	ar6 = [--ar5];						// pDstMin
	gr5 = [--ar5];						// nSize
	
	
	nb1  = 080808080h with gr5>>=3;
	f1cr = 0FEFEFEFEh;
    f2cr = 0FEFEFEFEh;  	
	delayed call vec_CmpLtV;
		wtw;
		nul;
		
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
