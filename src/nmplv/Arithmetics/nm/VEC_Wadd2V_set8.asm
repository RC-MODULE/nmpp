//------------------------------------------------------------------------
//
//  $Workfile:: VEC_Wadd2V_set8.asm             $
//
//  <nmplv>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   VEC_Wadd2V_set8.asm
//! \author Сергей Свечников
//! \brief  <Установка двух к-тов для nmppsWeightedSum_Exe(nm8s...>
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

global _void._.8.8nmppsWeightedSum_Set8.1int.9._int.9._class._S_nmppsWeightedSum._.0.2 :label;

<_void._.8.8nmppsWeightedSum_Set8.1int.9._int.9._class._S_nmppsWeightedSum._.0.2>
  ar5=ar7-2;
  push ar0,gr0;
  push ar1,gr1 with gr0=true;
  push ar2,gr2 with gr2=gr0>>16;
  push ar6,gr6 with gr7=false;

  gr0=[--ar5] with gr6=gr2;  // gr0=W1, gr6=ffff
  ar2=gr7 with gr2=false;

  gr1=[--ar5] with gr0=gr0 and gr6;  // W2
  ar6=[--ar5] with gr1=gr1 and gr6;  // kerW

  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;
  [ar6++]=gr0 with gr2=gr0<<16;  [ar6++]=gr7;
  [ar6++]=gr2; [ar6++]=gr7;
  [ar6++]=gr7; [ar6++]=gr0;
  [ar6++]=gr7; [ar6++]=gr2 with gr2=false;
  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;
  [ar6++]=gr1 with gr2=gr1<<16;  [ar6++]=gr7;
  [ar6++]=gr2; [ar6++]=gr7;
  [ar6++]=gr7; [ar6++]=gr1;
  [ar6++]=gr7; [ar6++]=gr2 with gr2=false;
  [ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;[ar6++]=ar2,gr2;

  pop ar6,gr6; pop ar2,gr2;pop ar1,gr1; pop ar0,gr0;
  return;

end ".text_nmplv";
