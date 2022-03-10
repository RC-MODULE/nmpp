    //--------------------------------------------------------------------
extern nmppsDupValueInVector4_: label;
extern nmppsBuildDiagWeights4_: label;
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

global _nmppsCmpEqC_4u3b:label;
<_nmppsCmpEqC_4u3b>
 
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
    gr1 = [--ar5] with gr5 >>= 4;   // shTrueFlag.

        //--------------------------------
        // Заполнение матрицы и векторов.
    ar1 = _nmppsTmpBuffer64_L_;
    call nmppsBuildDiagWeights4_;     			//      ar1 - Буфер весов.   	//      gr1 - значение (8 бит) (shTrueFlag)	// Изменяет регистры: ar1.
    call nmppsDupValueInVector4_;     			//      ar1 - Вектор.   		//      gr1 - значение (8 бит) (shTrueFlag)	// Изменяет регистры: ar1, 
    call nmppsDupValueInVector4_ with gr1 = gr7;//      ar1 - Вектор.   		//      gr1 - значение (8 бит) (shCmpVal)   // Изменяет регистры: ar1, 
        //--------------------------------
    
    ar1 = _nmppsTmpBuffer64_L_;
    nb1 = 0FFFFFFFFh;
	sb =  022222222h;
	rep 16 wfifo = [ar1++], ftw, wtw;
    vr = [ar1++];
	f1cr = 0EEEEEEEEh;
    call nmppsDataXorRamN_ActivateAfifoVr_;
        
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
.wait;

    //--------------------------------------------------------------------
end ".text_nmplv";