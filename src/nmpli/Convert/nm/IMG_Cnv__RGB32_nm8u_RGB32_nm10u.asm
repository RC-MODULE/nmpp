//------------------------------------------------------------------------
//
//  $Workfile:: ConvertRGB24_RGB30.ASM $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   ConvertRGB24_RGB30.asm
//! \author Сергей Ландышев.
//! \brief  Функция конвертирует элементы RGB из 8-ми разрядного представления
//!         в 10-ти разрядное. 
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_vsum_data_0: label;
global _nmppiConvert__F12RGB32_nm8uP13RGB32_nm10uPi: label;
global _void._.8.8nmppiConvert.1class._RGB32_nm8u._.0.9._class._RGB32_nm10u._.0.9._int.2 :label;

    //--------------------------------------------------------------------
begin ".text_nmpli"
Weights:	long[8] = (
		00000000000000001hl,
		00000000000000400hl,
		00000000000100000hl,
		00000000000000000hl,
		00000000100000000hl,
		00000040000000000hl,
		00010000000000000hl,
		00000000000000000hl);

    //--------------------------------------------------------------------
    //! \fn  void nmppiConvert(RGB32_nm8u* pSrcImg, RGB32_nm10u* pDstImg, int nSize); 
    //!
	//! \perfinclude _nmppiConvert__F10RGB32_nm8uP11RGB32_nm10uPi.html
    //--------------------------------------------------------------------
<_nmppiConvert__F12RGB32_nm8uP13RGB32_nm10uPi>
<_void._.8.8nmppiConvert.1class._RGB32_nm8u._.0.9._class._RGB32_nm10u._.0.9._int.2>
    ar5 = sp - 2;
    push ar0, gr0 with gr0 = false;
    push ar5, gr5 with gr0++;
    push ar6, gr6 with gr0++;

    ar0 = [--ar5] with gr6 = gr0;
    ar6 = [--ar5];
    gr5 = [--ar5];
    
    nb1 = 0880a0280h;
	sb = 02020202h;
	ar5 = Weights;
	rep 8 wfifo = [ar5++], ftw, wtw;

    call vec_vsum_data_0 with gr5 >>= 1;
    
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar0, gr0;
    return;
    //--------------------------------------------------------------------
end ".text_nmpli";
