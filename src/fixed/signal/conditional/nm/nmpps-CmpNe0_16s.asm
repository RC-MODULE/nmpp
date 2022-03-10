begin ".text_nmplv"

	//! \fn void nmppsCmpNe0_16s(nm16s* pSrcVec, nm16s* pDstVec, int nSize);
	//!
	//! \perfinclude _nmppsCmpNe0_16s.html
extern vec_CmpNe0:label;
global _nmppsCmpNe0_16s:label;
<_nmppsCmpNe0_16s>
 
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.

	nb1  = 80008000h;wtw;
	f1cr = 0FFFEFFFEh;
	f2cr = 0FFFEFFFEh;  
    call vec_CmpNe0 with gr5>>=2;
		
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

end ".text_nmplv";