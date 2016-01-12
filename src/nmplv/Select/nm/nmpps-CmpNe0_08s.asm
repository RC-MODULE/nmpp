begin ".text_nmplv"

	//! \fn void nmppsCmpNe0_8s(nm8s* pSrcVec, nm8s* pDstVec, int nSize);
	//!
	//! \perfinclude _nmppsCmpNe0_8s.html

extern vec_CmpNe0:label;
global _nmppsCmpNe0_8s:label;
<_nmppsCmpNe0_8s>
 
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.

	nb1  = 80808080h;wtw;
	f1cr = 0FEFEFEFEh;
    delayed call vec_CmpNe0 with gr5>>=3;
		f2cr = 0FEFEFEFEh;  
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

end ".text_nmplv";