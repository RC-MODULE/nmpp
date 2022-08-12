    //--------------------------------------------------------------------
extern nmppsDupValueInVector16_: label;
extern nmppsBuildDiagWeights16_: label;
extern nmppsDataXorRamV_ActivateAfifoVr_: label;
extern _nmppsTmpBuffer64_L_: word;

begin ".text_nmplv"
	//! \fn void nmppsCmpEqV_16u15b(nm16u15b* pSrcVec1, nm16u15b* pSrcVec2, nm16s* pDstVec, int nSize, int16b shTrueFlag);
	//!
	//! \perfinclude _nmppsCmpEqV_16u15b.html
global _nmppsCmpEqV_16u15b:label;
<_nmppsCmpEqV_16u15b>
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec1.
    gr7 = [--ar5];                  // pSrcVec2.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.
    gr1 = [--ar5] with gr5 >>= 2;   // shTrueFlag.

        //--------------------------------
        // Заполнение матрицы и векторов.
    ar1 = _nmppsTmpBuffer64_L_;
    call nmppsBuildDiagWeights16_;
    call nmppsDupValueInVector16_;
        //--------------------------------
    
    ar1 = _nmppsTmpBuffer64_L_;
    nb1 = 0FFFFFFFFh;
	sb = 020002h;
	rep 4 wfifo = [ar1++], ftw, wtw;
    vr = [ar1++];
    
	f1cr = 0FFFEFFFEh with gr1 = gr0;
    delayed call nmppsDataXorRamV_ActivateAfifoVr_;
		ar1 = gr7;    
		nul;
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;
    //--------------------------------------------------------------------
end ".text_nmplv";