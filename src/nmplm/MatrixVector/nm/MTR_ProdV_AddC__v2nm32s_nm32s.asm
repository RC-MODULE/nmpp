//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulV2_AddV2_nm32s.asm             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulV2_AddV2_nm32s.asm
//! \author Sergey Landyshev
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplm"
extern vec_Mul2D2W2_AddVr:label;
extern _nmppsTmpBuffer64_G_:long;
extern _nmppsTmpBuffer64_L_:long;

//--------------------------------------------------------------------
//! \fn void nmppmMul_mv__AddC(v2nm32s* pSrcMtr, v2nm32s* pSrcVec2, int nAddVal, nm32s* pDstVec, int nHeight);
//!
//! \perfinclude _nmppmMul_mv__AddC__F7v2nm32sP7v2nm32sPiPii.html
//--------------------------------------------------------------------
global _nmppmMul_mv__AddC__F7v2nm32sP7v2nm32sPiPii:label;
global _void._.8.8nmppmMul_mv__AddC.1class._v2nm32s._.0.9._class._v2nm32s._.0.9._int.9._int._.0.9._int.2 :label;
<_nmppmMul_mv__AddC__F7v2nm32sP7v2nm32sPiPii>
<_void._.8.8nmppmMul_mv__AddC.1class._v2nm32s._.0.9._class._v2nm32s._.0.9._int.9._int._.0.9._int.2>
 


    ar5=ar7-2;
    push ar0,gr0 with gr7=false;
    push ar1,gr1;
    push ar2,gr2; 
    push ar3,gr3;
    push ar4,gr4 with gr4=true; 
    push ar5,gr5;
    push ar6,gr6 with gr4<<=31;

    ar0 = [--ar5];//      nm32s* pSrcMtr, 
    ar2 = [--ar5];//      nm32s* pSrcVec2, 
    gr2 = [--ar5];//      int nAddVal, 
    ar6 = [--ar5];//      nm32s* pDstVec, 
    gr5 = [--ar5];//      int nHeight, 

    nb1 = gr4;
    vr  = gr2 with gr5 >>= 1;
    ar1 = ar0 + 2;
    gr0 = ar0;
    with gr0;
    if < delayed goto L0;
        ar4=_nmppsTmpBuffer64_L_;
    ar4=_nmppsTmpBuffer64_G_;
    <L0>

    ar3,gr3 = [ar2++];
    [ar4++]=ar3;
    [ar4++]=gr7;
    [ar4++]=gr3;
    [ar4++]=gr7;
    
    [ar4++]=gr7;
    [ar4++]=ar3;
    [ar4++]=gr7;
    [ar4++]=gr3;
    
    ar4 -= 8;
    gr0 = 4;
    
	sb=2;    // 2x32 
    delayed call vec_Mul2D2W2_AddVr;
		gr1 = gr0;
		gr6 = gr0>>1;
       

  
    pop ar6,gr6; 
    pop ar5,gr5;
    pop ar4,gr4; 
    pop ar3,gr3;
    pop ar2,gr2;
    pop ar1,gr1; 
    pop ar0,gr0;
    
  return;
end ".text_nmplm";
