//------------------------------------------------------------------------
//
//  $Workfile:: data_and_ram.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   data_and_ram.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

 
		
		

//------------------------------------------------------------------------
//
//  $Workfile:: ARSH32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   ARSH32.asm
//! \author Сергей Мушкаев
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vShift.h"

extern vec_vsum_shift_data_0:label;
extern vec_vsum_data_0:label;

extern vec_tbl_nb_int_EvenRightShift:long[16];
extern vec_tbl_sb_int_EvenRightShift:long[16];
extern vec_tbl_w_int_EvenRightShift:long[4*16];
extern vec_tbl_sb_int_OddRightShift:long[16];
extern vec_tbl_nb_int_OddRightShift:long[16];
extern vec_tbl_w_int_OddRightShift:long[6*16];
// This data for VEC_ARSH32_aaRC macros
extern Table_sb_nb_woper_even:long[6*16];
						   // This data for VEC_ARSH32_aaRC macros
extern Table_sb_nb_woper_odd:long[8*16];
   

begin ".text_nmplv"


	//------------------------------------------------------------------------
    //! \fn void vec_RShift32s(nmreg ar0, nmreg gr0, nmreg ar6, nmreg gr6, nmreg gr4, nmreg gr5);
    //!
    //------------------------------------------------------------------------
	
global vec_RShift32s:label;
<vec_RShift32s>
.branch;
	//ar0 = [--ar5];	// pSrcVec
	//gr4 = [--ar5];	// Shift
	//ar6 = [--ar5];	// pDstVec
	//gr5 = [--ar5];	// nSize
	push ar4,gr4 with gr7=gr4<<31;
	if =0 delayed goto arsh32_Even_by32	with gr5>>=1;// nSize in 64-bit vectors
		nul;
		nul;
	/////////////////////////////////////////////////////////////
	// Shifting by odd number of bits to the right
	ar4 = vec_tbl_sb_int_OddRightShift	with gr4--;
	sb  = [ar4+=gr4]					with gr7 =gr4<<1;
	ar4 = vec_tbl_nb_int_OddRightShift  with gr7+=gr4;
	gr7 = [ar4+=gr4]					with gr4=gr7<<1;
	nb1 = gr7;											
	ar4 = vec_tbl_w_int_OddRightShift;
	delayed call vec_vsum_shift_data_0;
		ar4+= gr4;		
		rep 6 wfifo=[ar4++],ftw,wtw;
	
	pop ar4,gr4; 
	return;
	
	<arsh32_Even_by32>
	/////////////////////////////////////////////////////////////
	// Shifting by Even number of bits to the right
	ar4 = vec_tbl_sb_int_EvenRightShift;
	sb  = [ar4+=gr4];
	ar4 = vec_tbl_nb_int_EvenRightShift;
	gr7 = [ar4+=gr4];
	nb1 = gr7;											
	ar4 = vec_tbl_w_int_EvenRightShift with gr4<<=2;
	delayed call vec_vsum_data_0;
		ar4+= gr4;		
		rep 4 wfifo=[ar4++],ftw,wtw;

	pop ar4,gr4;
	return;
.wait;

end ".text_nmplv";