    //--------------------------------------------------------------------
extern nmppsDupValueInVector8_: label;
extern nmppsBuildDiagWeights8_: label;
extern nmppsDataXorRamN_ActivateAfifoVr_: label;
extern _nmppsTmpBuffer64_L_: word;

    //--------------------------------------------------------------------
data ".data_nmplv_L"
end ".data_nmplv_L";
data ".data_nmplv_G"
end ".data_nmplv_G";

    //--------------------------------------------------------------------
begin ".text_nmplv"

	//! \fn void nmppsCmpEqC_8u7b(nm8u7b* pSrcVec,  uint7b chCmpVal,  nm8s* pDstVec, int nSize, int8b chTrueFlag);
	//!
	//! \perfinclude _nmppsCmpEqC_8u7b.html

global _nmppsCmpEqC_8u7b:label;
<_nmppsCmpEqC_8u7b>
 
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar1, gr1 with gr0++;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr6 = gr0;
    ar0 = [--ar5];                  // pSrcVec.
    gr7 = [--ar5];                  // shCmpVal.
    ar6 = [--ar5];                  // pDstVec.
    gr5 = [--ar5];                  // nSize.
    gr1 = [--ar5] with gr5 >>= 3;   // shTrueFlag.

        //--------------------------------
        // Заполнение матрицы и векторов.
    ar1 = _nmppsTmpBuffer64_L_;
    call nmppsBuildDiagWeights8_;
    call nmppsDupValueInVector8_;
    call nmppsDupValueInVector8_ with gr1 = gr7;
        //--------------------------------
    
    ar1 = _nmppsTmpBuffer64_L_;
    nb1 = 0FFFFFFFFh;
	sb = 02020202h;
	rep 8 wfifo = [ar1++], ftw, wtw;
    vr = [ar1++];
	f1cr = 0FEFEFEFEh;
    call nmppsDataXorRamN_ActivateAfifoVr_;
        
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

    //--------------------------------------------------------------------
end ".text_nmplv";