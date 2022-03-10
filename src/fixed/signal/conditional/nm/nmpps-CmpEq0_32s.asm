begin ".text_nmplv"

	//! \fn void nmppsCmpEq0_32s(nm32s* pSrcVec, nm32s* pDstVec, int nSize);
	//!
	//! \perfinclude _nmppsCmpEq0_32s.html
	// Author: Ivan Zhilenkov
extern vec_CmpEq0:label;
global _nmppsCmpEq0_32s:label;
<_nmppsCmpEq0_32s>
 
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.

	nb1  = 80000000h;wtw;
	f1cr = 80000000h;
	f2cr = 80000000h;  
    call vec_CmpEq0 with gr5>>=1;
		
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

end ".text_nmplv";