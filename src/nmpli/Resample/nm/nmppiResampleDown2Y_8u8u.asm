//------------------------------------------------------------------------
//
//  $Workfile:: ResizeDown2Y_C7.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   ResizeDown2Y_C7.asm
//! \brief  Функции изменения размеров изображения.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"

import from macros.mlb;

data ".data_nmpli_G"
	Mask:	long = 0fefefefefefefefeh;
end ".data_nmpli_G";
/////////////////////////////////////////////////////////////////////////////////////////
begin ".text_nmpli"

    //--------------------------------------------------------------------
    //! \fn void nmppiResampleDown2Y(nm8u7b* pSrcImg, nm8u7b* pDstImg, int nSrcWidth, int nSrcHeight)
    //!
//! \perfinclude _nmppiResampleDown2Y__FPUcPUcii.html
    //--------------------------------------------------------------------
extern vec_Add_VV_shift:label;
global _nmppiResampleDown2Y_8u8u:label;
<_nmppiResampleDown2Y_8u8u>
.branch;
				
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr1 = gr7;
	push ar5,gr5	with gr6 = gr7;
	push ar6,gr6;

	ar0 = [--ar5];					// pSrcImg
	ar6 = [--ar5];					// pDst
	gr4 = [--ar5];					// w
	gr3 = [--ar5];					// h

	nb1 = 080808080h;
	wtw;

	ar4 = Mask;

	with gr3>>=1;
	with gr4>>=3;

	with gr3 - gr4;
	if > delayed goto VerticalScroll
		with gr0 = gr4<<1;
		ar1 = ar0 + gr0;
<HoryzintalScroll>
	with gr0 = gr7;

	with gr3--;
	if < delayed goto exit_lbl;
		nul;
		nul;
<HS_Next>	
	call vec_Add_VV_shift with gr5 = gr4;
	with gr0 = gr4<<1;
	ar0 += gr0 with gr1 = gr4<<1;
	ar1 += gr1 with gr3--;
	if >= delayed goto HS_Next;
		gr0 = gr7;
		gr1 = gr7;

	delayed goto exit_lbl;
////////////////////////////////////////////////////////////
<VerticalScroll>
	with gr6 = gr0;
	with gr1 = gr0<<1;
	with gr0<<=1;

	with gr4--;
	if < delayed goto exit_lbl;
		nul;
		nul;
<VS_Next>	
	push ar0,gr0;
	push ar1,gr1;
	push ar6,gr6;
	call vec_Add_VV_shift with gr5 = gr3;
	pop ar6,gr6;
	pop ar1,gr1;
	pop ar0,gr0;
	ar0+=2;
	ar1+=2 with gr4--;
	if >= delayed goto VS_Next;
		ar6+=2;
////////////////////////////////////////////////////////////
<exit_lbl>
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
////////////////////////////////////////////////////////////
end ".text_nmpli"; 
