//------------------------------------------------------------------------
//
//  $Workfile:: RSH8.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   RSH4.asm
//! \author Иван Жиленков
//! \brief  Операция логического сдвига вправо для типа nm4u.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vShift.h"

	import from macros.mlb;
	extern vec_vsum_shift_data_0:label;
	extern vec_vsum_data_0:label;

data ".data_nmplv_G"
		vec_tbl_w_nm4u_RSH:long[64]=(
			// weights for right shift=2,3
			0hl,00000000000000001hl,
			0hl,00000000000000010hl,
			0hl,00000000000000100hl,
			0hl,00000000000001000hl,
			0hl,00000000000010000hl,
			0hl,00000000000100000hl,
			0hl,00000000001000000hl,
			0hl,00000000010000000hl,
			0hl,00000000100000000hl,
			0hl,00000001000000000hl,
			0hl,00000010000000000hl,
			0hl,00000100000000000hl,
			0hl,00001000000000000hl,
			0hl,00010000000000000hl,
			0hl,00100000000000000hl,
			0hl,01000000000000000hl,
			
			// weights for right shift=0,1
			00000000000000001hl,00000000000000004hl,
			00000000000000010hl,00000000000000040hl,
			00000000000000100hl,00000000000000400hl,
			00000000000001000hl,00000000000004000hl,
			00000000000010000hl,00000000000040000hl,
			00000000000100000hl,00000000000400000hl,
			00000000001000000hl,00000000004000000hl,
			00000000010000000hl,00000000040000000hl,
			00000000100000000hl,00000000400000000hl,
			00000001000000000hl,00000004000000000hl,
			00000010000000000hl,00000040000000000hl,
			00000100000000000hl,00000400000000000hl,
			00001000000000000hl,00004000000000000hl,
			00010000000000000hl,00040000000000000hl,
			00100000000000000hl,00400000000000000hl,
			01000000000000000hl,04000000000000000h);
			

		vec_tbl_nb_sb_nm4u_RSH:word[8]=(
			0AAAAAAAAh,// nb sh0
			0AAAAAAAAh,// sb sh0
			0EEEEEEEEh,// nb sh1
			0AAAAAAAAh,// sb sh1
			0AAAAAAAAh,// nb sh2	
			0AAAAAAAAh,// sb sh2
			099999999h,// nb sh3	
			0AAAAAAAAh // sb sh3
			);
								

								

end ".data_nmplv_G";

begin ".text_nmplv"


///////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsRShiftC_4u(nm4u *pSrcVec, int nShift, nm4u *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsRShiftC_4u.html

global _nmppsRShiftC_4u:label;
<_nmppsRShiftC_4u>
.branch;
ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, 3].
	
	ar0 = vec_tbl_nb_sb_nm4u_RSH with gr0<<=1;
	ar5-=2;
	ar0+= gr0		with gr7 = gr0>>2;
	ar0,gr0 = [ar0]	with gr7--;
	sb  = gr0		with gr7 A>>=31;
	nb1 = ar0		with gr0=gr7<<6;
	ar0 = vec_tbl_w_nm4u_RSH with gr0=-gr0;
	ar0+= gr0;			// w table select 
	rep 32 wfifo=[ar0++],ftw;

	
	push ar5,gr5	with gr0=false;
	push ar6,gr6	with gr0++;
	
//	gr7 = [ar5++]	with gr0++;			// 	int				Shift	:[0, 1, 2, .., 7].
//	gr5 = [ar5++]	with gr6=gr0;		//	int				VecSize,	//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
//	ar6 = [ar5++]	with gr7<<=31;		//	nm8u*	DstVec,		//Output buffer		:long Global[Size/8].
//	ar0 = [ar5++];						//	nm8u*	SrcVec,		//Input buffer		:long Local [Size/8].
		
	gr5 = [ar5++]	with gr0++;			//	int				VecSize,	//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
	ar6 = [ar5++]	with gr6=gr0;		//	nm8u*	DstVec,		//Output buffer		:long Global[Size/8].
	gr7 = [ar5++]	;					// 	int				Shift	:[0, 1, 2, .., 31].
	ar0 = [ar5++] with gr7<<=31;		//	nm8u*	SrcVec,		//Input buffer		:long Local [Size/8].


	if =0 delayed goto Even_RightShift	with gr5>>=4;// Size in 64-bit vectors
		nul;
		nul;

	<Odd_RightShift>
	delayed call vec_vsum_shift_data_0;
		wtw;
		nul;
	goto End_RightShift;
	
	<Even_RightShift>
	delayed call vec_vsum_data_0;
		wtw;
		nul;

	<End_RightShift>


	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
	return;
.wait;
end ".text_nmplv";




