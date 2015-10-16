//==============================================================================
// 	
//	RC Module
// 	NeuroMatrix(r) Software
//    
//	File:               DeinterlaceSplit.asm
// 	Contents:           Splitting frame into even and odd fields
//						Version for width divisible by 8 on vector unit using
//																nmvcore lib
// 	Software design:    i.bezkorovainy
//
//==============================================================================
//
//	void IMG_DeinterlaceSplit (	nm8u* pSrcImg, 
//								int nSrcWidth, 
//								int nSrcHeight, 
//								nm8u* pDstEven, 
//								nm8u* pDstOdd 	)
//
//==============================================================================

global _void._.8.8IMG_DeinterlaceSplit.1unsigned._char._.0.9._int.9._int.9._unsigned._char._.0.9._unsigned._char._.0.2: label;
extern vec_data: label;

begin ".textDeinterlacer"
.branch;

<_void._.8.8IMG_DeinterlaceSplit.1unsigned._char._.0.9._int.9._int.9._unsigned._char._.0.9._unsigned._char._.0.2>
	
	ar5 = ar7 - 2	with gr7=false;	
	push ar0, gr0	with gr7++;
    push ar1, gr1	with gr7++;
    push ar2, gr2;
	push ar5, gr5	with gr0 = gr7;
	push ar6, gr6	with gr6 = gr7;
	
	ar0 = [--ar5];	// pSrcImg[0]
	gr5 = [--ar5];	// nSrcWidth
	gr1 = [--ar5]; 	// nSrcHeight  
	ar1 = [--ar5] with gr5 >>= 3; // ar1 points to *pDstEven[0] and gr5 = nSrcWidth / 8
	ar2 = [--ar5] with gr1 >>= 1; // pDstOdd[0]
	
	ar6 = ar1;
	<Loop>
	call vec_data; 		// copy from pSrcImg to pDstEven
	ar1 = ar6;
	ar6 = ar2;
    call vec_data ;		// copy from pSrcImg to pDstOdd
	ar2 = ar6 with gr1--;  	
	if <>0 delayed goto Loop;
		ar6 = ar1;
		nul;
		
	pop ar6, gr6;
	pop ar5, gr5;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
	
	return;
	
.wait;	
end ".textDeinterlacer";
///////////////////////////////////////////////////////////////////////////////
//	END OF FILE
///////////////////////////////////////////////////////////////////////////////