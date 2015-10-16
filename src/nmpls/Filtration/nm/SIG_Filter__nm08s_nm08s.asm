//------------------------------------------------------------------------
//
//  $Workfile:: Filter32to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/01/21 19:22:37 $
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
    //! \fn void SIG_Filter(nm8s* pSrcVec, nm8s* pDstVec, int nSize, nm64s* pKernel)
	//!
	// \perfinclude _SIG_Filter__FPcPciPl.html
    //--------------------------------------------------------------------
extern vec_ClipMulNDNW8_AddVr:label;
global _SIG_Filter__FPcPciPl:label;
global _void._.8.8SIG_Filter.1char._.0.9._char._.0.9._int.9._long._.0.2 :label;
<_SIG_Filter__FPcPciPl>
<_void._.8.8SIG_Filter.1char._.0.9._char._.0.9._int.9._long._.0.2>
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
	ar4 = ar1;		// pKernel
	gr1 = [ar1++];				// Number of arrays
	//gr0 = gr1>>1;
	//gr0 = gr0<<1;
	//gr0 = -gr0;
	//ar0 = ar0+gr0;
	gr4 = [ar1++];				// Here ar1 = Pointer to array of dispacements
								// gr4 - displacement to weights from pKernel
	ar4+=gr4;					// ar4   = Pointer to weights
	gr0 = 2;
	gr6 = 2;

	sb	= 02020202h;
	gr4 = 80808080h;
	nb1 = gr4;
	f1cr= 0;
	vr  = 0;
	call vec_ClipMulNDNW8_AddVr with gr5>>=3;

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
