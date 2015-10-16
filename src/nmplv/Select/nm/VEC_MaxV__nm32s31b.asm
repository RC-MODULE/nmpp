//------------------------------------------------------------------------
//
//  $Workfile:: CompareMaxV_32s.asm            $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   CompareMaxV_8s.asm
//! \author S. Mushkaev
//! \brief  Elementwise Max comparision
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_CompareMax:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void VEC_MaxV(nm32s31b*  pSrcVec1, nm32s31b* pSrcVec2,  nm32s31b*  pDstMax, int nSize);
//!
//! \perfinclude _VEC_MaxV__FPiPiPii.html

global _VEC_MaxV__FPiPiPii :label;
global _void._.8.8VEC_MaxV.1int._.0.9._int._.0.9._int._.0.9._int.2 :label;
<_VEC_MaxV__FPiPiPii>
<_void._.8.8VEC_MaxV.1int._.0.9._int._.0.9._int._.0.9._int.2>
.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	push ar1,gr1	with gr0++;
	push ar3,gr3;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr1=gr0;

	ar0 = [--ar5] with gr6=gr0;		    // pSrcVec1
	ar1 = [--ar5];						// pSrcVec2
	ar6 = [--ar5];						// pDstMax
	gr5 = [--ar5];						// nSize
	
	
	nb1 =80000000h with gr5>>=1;
	ar3 = ar1 with gr3 = gr1;
	wtw;
	delayed call vec_CompareMax;
		f1cr=80000000h;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar3,gr3;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
