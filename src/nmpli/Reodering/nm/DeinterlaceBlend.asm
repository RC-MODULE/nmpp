//==============================================================================
// 	
//	RC Module
// 	NeuroMatrix(r) Software
//    
//	File:               DeinterlaceMerge.asm
// 	Contents:           Merge two fields into interlaced frame
//						Version for width divisible by 8 on vector unit using
//																nmvcore lib
// 	Software design:    i.bezkorovainy
//
//==============================================================================
//
//	void IMG_DeinterlaceMerge (	nm8u* pSrcEven, 
//								nm8u* pSrcOdd, 
//								int nSrcWidth, 
//								int nSrcHeight, 
//								nm8u* pDst	);
//
//==============================================================================

global _void._.8.8IMG_DeinterlaceBlend.1unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.9._unsigned._char._.0.2: label;
extern vec_data: label;

begin ".textDeinterlacer"
.branch;

<_void._.8.8IMG_DeinterlaceBlend.1unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.9._unsigned._char._.0.2>
	
	ar5 = ar7 - 2	with gr7=false;	
	push ar0, gr0	with gr7++;
    push ar1, gr1	with gr7++;
    push ar2, gr2;
	push ar5, gr5	with gr0 = gr7;
	push ar6, gr6	with gr6 = gr7;
	
	ar1 = [--ar5];	// pSrcEven[0]
	ar2 = [--ar5];	// pSrcOdd[0]
	gr5 = [--ar5];	// nSrcWidth
	gr1 = [--ar5] with gr5 >>= 3; 	// gr1 = nSrcHeight and gr0 = nSrcWidth / 8
	ar6 = [--ar5]; 	// pDst[0] 
		
	ar0 = ar1;	
    <Loop>
	call vec_data; 		// copy from pSrcImg to pDstEven
	ar1 = ar0;
	ar0 = ar2;
    call vec_data; 		// copy from pSrcImg to pDstOdd
	ar2 = ar0 with gr1--;
	if <>0 delayed goto Loop;
		ar0 = ar1;
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