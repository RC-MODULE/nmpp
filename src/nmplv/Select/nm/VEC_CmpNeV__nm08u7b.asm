    //--------------------------------------------------------------------
extern VEC_BuildDiagWeights8: label;
extern VEC_DataXorRamV_ActivateAfifoVr: label;
extern _VEC_TmpBuffer64_L: word;

begin ".text_nmplv"
	//! \fn void VEC_CmpNeV(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b chTrueFlag);
	//!
	//! \perfinclude _VEC_CmpNeV__FPUcPUcPcii.html
global _VEC_CmpNeV__FPUcPUcPcii: label;
global _void._.8.8VEC_CmpNeV.1unsigned._char._.0.9._unsigned._char._.0.9._char._.0.9._int.9._int.2 :label;
<_VEC_CmpNeV__FPUcPUcPcii>
<_void._.8.8VEC_CmpNeV.1unsigned._char._.0.9._unsigned._char._.0.9._char._.0.9._int.9._int.2>
.branch;    
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    ar0 = gr0;
    vr = ar0, gr0;
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
    ar1 = _VEC_TmpBuffer64_L;
    call VEC_BuildDiagWeights8;
        //--------------------------------
    
    ar1 = _VEC_TmpBuffer64_L;
    nb1 = 0FFFFFFFFh;
	sb = 02020202h;
	rep 8 wfifo = [ar1++], ftw, wtw;
    ar1 = gr7;

    delayed call VEC_DataXorRamV_ActivateAfifoVr;
        f1cr = 0FEFEFEFEh with gr1 = gr0;
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

    //--------------------------------------------------------------------
end ".text_nmplv";