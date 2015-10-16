//------------------------------------------------------------------------
//
//  $Workfile:: VEC_Wadd2V_exe32.asm             $
//
//  <nmplv>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   VEC_Wadd2V_exe32.asm 
//! \author Сергей Свечников
//! \brief  <Взвешенная сумма двух векторов типа nm32s>
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmplv"
extern vec_Mul2D2W2_AddVr:label;

// void VEC_WAdd2V_Exe(nm8s* pSrcVec1,nm8s* pSrcVec2, S_VEC_WAdd2V* kerW, nm16s* pDstVec, int nSize);
global _void._.8.8VEC_WAdd2V_Exe.1int._.0.9._int._.0.9._class._S_VEC_WAdd2V._.0.9._long._.0.9._int.2 :label;
<_void._.8.8VEC_WAdd2V_Exe.1int._.0.9._int._.0.9._class._S_VEC_WAdd2V._.0.9._long._.0.9._int.2>
  ar5=ar7-2;
  push ar0,gr0; push ar1,gr1; push ar2,gr2; push ar4,gr4; push ar6,gr6;
  ar0=[--ar5]with gr4=false;  // pSrcVec1
  ar1=[--ar5]with gr0=gr4+1;  // pSrcVec2
  ar4=[--ar5]with gr0<<=1;    // kerW
  ar6=[--ar5]with gr1=gr0;    // pDstVec
      push ar5,gr5;
  gr5=[--ar5]with gr6=gr0<<1; // nSize, gr6=4
  vr=gr4 with gr5>>=1;
//  gr4=0h;
  nb1=gr4;  // 1x64 on Y Vport
  ar5=ar6;ar2=ar0;gr2=ar1;ar4=ar4+2;
delayed call vec_Mul2D2W2_AddVr;
  sb=2;    // 2x32 on X Vport
  
  ar0=ar2;ar1=gr2;ar6=ar5+2;
delayed call vec_Mul2D2W2_AddVr;
  ar4=ar4-2;
  pop ar5,gr5;
  pop ar6,gr6; pop ar4,gr4; 
  pop ar2,gr2;
  pop ar1,gr1; pop ar0,gr0;
  return;
end ".text_nmplv";