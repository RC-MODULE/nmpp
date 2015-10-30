//------------------------------------------------------------------------
//
//  $Workfile:: VEC_Wadd2V_set16.asm             $
//
//  <nmplv>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   VEC_Wadd2V_set16.asm
//! \author Сергей Свечников
//! \brief  <Установка двух к-тов для nmppsWeightedSum_Exe(nm16s...>
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"
global _nmppsWeightedSum_Set16__Fii12S_nmppsWeightedSumP:label;
global _void._.8.8nmppsWeightedSum_Set16.1int.9._int.9._class._S_nmppsWeightedSum._.0.2 :label;
<_nmppsWeightedSum_Set16__Fii12S_nmppsWeightedSumP>
<_void._.8.8nmppsWeightedSum_Set16.1int.9._int.9._class._S_nmppsWeightedSum._.0.2>
  ar5=ar7-2;
  push ar0,gr0;
  push ar1,gr1;
  push ar2,gr2;
  push ar6,gr6 with gr2=false;

  gr0=[--ar5];  // W1
  ar2=gr2;
  gr1=[--ar5];  // W2
  ar6=[--ar5];  // kerW

  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2; // 0,0,0,0
  [ar6++]=gr0; [ar6++]=gr2;        // w1,0
  [ar6++]=gr2; [ar6++]=gr0;        // 0,w1
  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2; // 0,0,0,0
  [ar6++]=gr1;  [ar6++]=gr2;       // w2,0
  [ar6++]=gr2;  [ar6++]=gr1;       // 0,w2
  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2; // 0,0,0,0

  pop ar6,gr6; pop ar2,gr2;pop ar1,gr1; pop ar0,gr0;
  return;

end ".text_nmplv";
