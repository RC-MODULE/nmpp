//------------------------------------------------------------------------
//
//  $Workfile:: Filter32to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/01/22 13:50:27 $
//
//! \if file_doc
//!
//! \file   Filter32to32.asm
//! \author S. Mushkaev
//! \brief  Функии фильтрации для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmpls"

    //--------------------------------------------------------------------
    //! \fn void SIG_Filter(nm16s* pSrcVec, nm16s* pDstVec, int nSize, nm64s* pKernel)
	//!
	// \perfinclude _SIG_Filter__FPSsPSsiPl.html
    //--------------------------------------------------------------------
extern vec_ClipMulNDNW4_AddVr:label;
global _SIG_Filter__FPSsPSsiPl:label;
global _void._.8.8SIG_Filter.1short._.0.9._short._.0.9._int.9._long._.0.2 :label;
<_SIG_Filter__FPSsPSsiPl>
<_void._.8.8SIG_Filter.1short._.0.9._short._.0.9._int.9._long._.0.2>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	
    
	ar0 = [--ar5];	// pSrcVec
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize
	ar1 = [--ar5];	// pKernel
	
	gr1 = [ar1++];				// Number of arrays
//	gr0 = gr1>>1;
//	gr0 = gr0<<1;
//	gr0 = -gr0;
//	ar0 = ar0+gr0;
	ar4 = [ar1++];				// Here ar1 = Pointer to array of dispacements
								// ar4      = Pointer to weights
	gr0 = 2;
	gr6 = 2;

	sb	= 00020002h;
	gr4 = 80008000h;
	nb1 = gr4;
	f1cr= 0;
	vr  = 0;
	call vec_ClipMulNDNW4_AddVr with gr5>>=2;

    pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
 
	return;

.wait;
end ".text_nmpls";
