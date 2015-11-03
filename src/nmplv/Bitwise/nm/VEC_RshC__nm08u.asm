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
//! \file   RSH8.asm
//! \author Павел Лукашевич
//! \brief  Операция логического сдвига вправо для типа nm8s.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vShift.h"

	import from macros.mlb;
	extern vec_vsum_shift_data_0:label;
	extern vec_vsum_data_0:label;

data ".data_nmplv_G"
		vec_tbl_w_char_RSH:long[32]=(
			// wights for right shift=2,3,4-7
			0hl,0000000000000001hl,	
			0hl,0000000000000100hl,	
			0hl,0000000000010000hl,	
			0hl,0000000001000000hl,	
			0hl,0000000100000000hl,	
			0hl,0000010000000000hl,	
			0hl,0001000000000000hl,	
			0hl,0100000000000000hl,
			// wights for right shift=0,1
			00000000000000001hl,	00000000000000004hl,
			00000000000000100hl,	00000000000000400hl,
			00000000000010000hl,	00000000000040000hl,
			00000000001000000hl,	00000000004000000hl,
			00000000100000000hl,	00000000400000000hl,
			00000010000000000hl,	00000040000000000hl,
			00001000000000000hl,	00004000000000000hl,
			00100000000000000hl,	00400000000000000hl
			);

		vec_tbl_nb_sb_char_RSH:word[16]=(
			082828282h,// nb sh0
			00a0a0a0ah,// sb sh0
			0c2c2c2c2h,// nb sh1
			00a0a0a0ah,// sb sh1
			0a0a0a0a0h,// nb sh2	
			00a0a0a0ah,// sb sh2
			090909090h,// nb sh3	
			00a0a0a0ah,// sb sh3
			088888888h,// nb sh4
			022222222h,// sb sh4
			084848484h,// nb sh5
			022222222h,// sb sh5
			082828282h,// nb sh6
			082828282h,// sb sh6
			081818181h,// nb sh7
			082828282h // sb sh7
			);
								

								

end ".data_nmplv_G";

begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsRshC_8u(nm8u *pSrcVec, int nShift, nm8u *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsRshC_8u.html

global _nmppsRshC_8u:label;
<_nmppsRshC_8u>
.branch;
	ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, .., 7].
	
	ar0 = vec_tbl_nb_sb_char_RSH with gr0<<=1;
	ar5-=2;
	ar0+= gr0		with gr7 = gr0>>2;
	ar0,gr0 = [ar0]	with gr7--;
	sb  = gr0		with gr7 A>>=31;
	nb1 = ar0		with gr0=gr7<<5;
	ar0 = vec_tbl_w_char_RSH with gr0=-gr0;
	ar0+= gr0;			// w table select 
	rep 16 wfifo=[ar0++],ftw;

	
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


	if =0 delayed goto Even_RightShift	with gr5>>=3;// Size in 64-bit vectors
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




