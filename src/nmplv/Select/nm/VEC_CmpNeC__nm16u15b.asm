    //--------------------------------------------------------------------
extern nmppsDupValueInVector16_: label;
extern nmppsBuildDiagWeights16_: label;
extern nmppsDataXorRamN_ActivateAfifoVr_: label;
extern _nmppsTmpBuffer64_L_: word;

begin ".text_nmplv"
	//! \fn void nmppsCmpNeC_16u(nm16u15b* pSrcVec,  uint15b shCmpVal,   nm16s* pDstVec, int nSize, int16b shTrueFlag);
	//!
	//! \perfinclude _nmppsCmpNeC__FPUsUiPSsii_.html
global _nmppsCmpNeC__FPUsUiPSsii_: label;
global _void._.8.8nmppsCmpNeC_.1unsigned._short._.0.9._unsigned._int.9._short._.0.9._int.9._int.2 :label;
<_nmppsCmpNeC__FPUsUiPSsii_>
<_void._.8.8nmppsCmpNeC_.1unsigned._short._.0.9._unsigned._int.9._short._.0.9._int.9._int.2>
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    ar0 = gr0;
    vr = ar0, gr0;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    gr7 = [--ar5];                  // shCmpVal.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.
    gr1 = [--ar5] with gr5 >>= 2;   // shTrueFlag.

        //--------------------------------
        // Заполнение матрицы и векторов.
    ar1 = _nmppsTmpBuffer64_L_;
    call nmppsBuildDiagWeights16_;
    call nmppsDupValueInVector16_ with gr1 = gr7;
        //--------------------------------
    
    ar1 = _nmppsTmpBuffer64_L_;
    nb1 = 0FFFFFFFFh;
	sb = 020002h;
	rep 4 wfifo = [ar1++], ftw, wtw;

    delayed call nmppsDataXorRamN_ActivateAfifoVr_;
        f1cr = 0FFFEFFFEh;
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;
    //--------------------------------------------------------------------
        
end ".text_nmplv";