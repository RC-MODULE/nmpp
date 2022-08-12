    //--------------------------------------------------------------------
extern nmppsDupValueInVector8_: label;
extern nmppsBuildDiagWeights8_: label;
extern nmppsDataXorRamV_ActivateAfifoVr_: label;
extern _nmppsTmpBuffer64_L_: word;

begin ".text_nmplv"
    //--------------------------------------------------------------------
	//! \fn void nmppsCmpEqV_8u7b(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b chTrueFlag);
	//!
	//! \perfinclude _nmppsCmpEqV_8u7b.html
    //--------------------------------------------------------------------
global _nmppsCmpEqV_8u7b:label;
<_nmppsCmpEqV_8u7b>
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
    gr1 = [--ar5] with gr5 >>= 3;   // shTrueFlag.

        //--------------------------------
        // Заполнение матрицы и векторов.
    ar1 = _nmppsTmpBuffer64_L_;
    call nmppsBuildDiagWeights8_;
    call nmppsDupValueInVector8_;
        //--------------------------------
    
    ar1 = _nmppsTmpBuffer64_L_;
    nb1 = 0FFFFFFFFh;
	sb = 02020202h;
	rep 8 wfifo = [ar1++], ftw, wtw;
    vr = [ar1++];
    
	f1cr = 0FEFEFEFEh with gr1 = gr0;
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