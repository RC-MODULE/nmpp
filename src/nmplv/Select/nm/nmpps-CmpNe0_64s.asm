begin ".text_nmplv"

	//! \fn void nmppsCmpNe0_64s(nm64s* pSrcVec, nm64s* pDstVec, int nSize);
	//!
	//! \perfinclude _nmppsCmpNe0_64s.html
extern vec_CmpNe0:label;
global _nmppsCmpNe0_64s:label;
<_nmppsCmpNe0_64s>
 
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.

	nb1h  = 80000000h;
	nb1l  = 00000000h;wtw;
	f1crl = 0FFFEFFFEh;
	f1crh = 0FFFFFFFFh;
	f2crl = 0FFFEFFFEh;
	delayed call vec_CmpNe0 ;
		f2crh = 0FFFFFFFFh;	
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

end ".text_nmplv";