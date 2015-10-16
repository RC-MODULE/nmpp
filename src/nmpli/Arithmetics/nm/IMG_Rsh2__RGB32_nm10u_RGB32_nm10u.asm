//------------------------------------------------------------------------
//
//  $Workfile:: ShrRGB32nm10u.asm             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   ShrRGB32nm10u.asm
//! \author S. Mushkaev
//! \brief  Функция сдвигает элементы RGB32_nm10u на 2 разряда вправо
//!
//! \endif
//!
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//
//  $Workfile:: CnvRGB30_RGB24.ASM $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   CnvRGB30_RGB24.asm
//! \author Сергей Ландышев.
//! \brief  Функция конвертирует элементы RGB из 10-ти разрядного представления
//!         в 8-ми разрядное. 
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_vsum_data_0: label;

    //--------------------------------------------------------------------
begin ".text_nmpli"
    Weights:    long[14] = (
        00000000000000000hl,
        00000000000000001hl,
        00000000000000000hl,
        00000000000000400hl,
        00000000000000000hl,
        00000000000100000hl,
        00000000000000000hl,
        00000000000000000hl,
        00000000100000000hl,
        00000000000000000hl,
        00000040000000000hl,
        00000000000000000hl,
        00010000000000000hl,
        00000000000000000hl);

//! \fn  void IMG_Rsh2(RGB32_nm10u* pSrcImg, RGB32_nm10u* pDstImg, int nSize); 
//!
//! \n
//! \perfinclude _IMG_Rsh2__F11RGB32_nm10uP11RGB32_nm10uPi.html

global _IMG_Rsh2__F13RGB32_nm10uP13RGB32_nm10uPi: label;
global _void._.8.8IMG_Rsh2.1class._RGB32_nm10u._.0.9._class._RGB32_nm10u._.0.9._int.2 :label;
<_IMG_Rsh2__F13RGB32_nm10uP13RGB32_nm10uPi>
<_void._.8.8IMG_Rsh2.1class._RGB32_nm10u._.0.9._class._RGB32_nm10u._.0.9._int.2>
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr0++;

    ar0 = [--ar5] with gr6 = gr0;
    ar6 = [--ar5];
    gr5 = [--ar5];
    
    nb1 = 0a80a0280h;
	sb  = 080a0280ah;
	ar5 = Weights;
	rep 14 wfifo = [ar5++], ftw, wtw;

    call vec_vsum_data_0 with gr5 >>= 1;
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar0, gr0;
    return;
    //--------------------------------------------------------------------
end ".text_nmpli";
