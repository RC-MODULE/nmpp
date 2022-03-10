//------------------------------------------------------------------------
//
//  $Workfile:: nmppsWadd2V_set32_.asm             $
//
//  <nmplv>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   nmppsWadd2V_set32_.asm
//! \author Сергей Свечников
//! \brief  <Установка двух к-тов для nmppsWeightedSum_Exe(nm32s...>
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmplv"

global _nmppsWeightedSum_Set32 :label;

<_nmppsWeightedSum_Set32>
  ar5=ar7-2;
  push ar0,gr0;
  push ar1,gr1;
  push ar2,gr2;
  push ar6,gr6 with gr2=false;

  ar0,gr0=[--ar5];  // W1
  ar2=gr2;
  ar1,gr1=[--ar5];  // W2
  ar6=[--ar5];  // kerW

  [ar6++]=ar2,gr2;       // 0
  [ar6++]=ar0,gr0;       // w1
  [ar6++]=ar2,gr2;       // 0
  [ar6++]=ar1,gr1;       // w2
  [ar6++]=ar2,gr2;       // 0

  pop ar6,gr6; pop ar2,gr2;pop ar1,gr1; pop ar0,gr0;
  return;

end ".text_nmplv";
