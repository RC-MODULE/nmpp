//------------------------------------------------------------------------
//
//  $Workfile:: RSH16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   RSH16.asm
//! \author Павел Лукашевич
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vShift.h"

	extern vec_vsum_shift_data_0:label;
	extern vec_vsum_data_0:label;

data ".data_nmplv_G"
		vec_tbl_w_short_RSH:long[16]=(
			// wights for right shift=2,3,4-7
			0hl,0000000000000001hl,	
			0hl,0000000000010000hl,	
			0hl,0000000100000000hl,	
			0hl,0001000000000000hl,	
			// wights for right shift=0,1
			00000000000000001hl,	00000000000000004hl,
			00000000000010000hl,	00000000000040000hl,
			00000000100000000hl,	00000000400000000hl,
			00001000000000000hl,	00004000000000000hl
			);

		vec_tbl_nb_sb_short_RSH:word[32]=(
			80028002h,// nb sh0
			000a000ah,// sb sh0
				0c002c002h,// nb sh1
				0000a000ah,// sb sh1
			0a000a000h,// nb sh2	
			0000a000ah,// sb sh2
				90009000h,// nb sh3	
				000a000ah,// sb sh3
			88008800h,// nb sh4
			00220022h,// sb sh4
				84008400h,// nb sh5
				00220022h,// sb sh5
			82008200h,// nb sh6
			00820082h,// sb sh6
				81008100h,// nb sh7
				00820082h,// sb sh7
			80808080h,// nb sh8
			02020202h,// sb sh8
				80408040h,// nb sh9
				02020202h,// sb sh9
			80208020h,// nb sh10	
			08020802h,// sb sh10
				80108010h,// nb sh11
				08020802h,// sb sh11
			80088008h,// nb sh12
			20022002h,// sb sh12
				80048004h,// nb sh13
				20022002h,// sb sh13
			80028002h,// nb sh14
			80028002h,// sb sh14
				80018001h,// nb sh15
				80028002h // sb sh15
			
			);
								

								

end ".data_nmplv_G";

import from macros.mlb;

begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsRshC_16u(nm16u *pSrcVec, int nShift, nm16u *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsRshC_16u.html

global _nmppsRshC_16u:label;
<_nmppsRshC_16u>
.branch;
	ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, .., 7].
	
	ar0 = vec_tbl_nb_sb_short_RSH with gr0<<=1;
	ar5-=2;
	ar0+= gr0		with gr7 = gr0>>2;
	ar0,gr0 = [ar0]	with gr7--;
	sb  = gr0		with gr7 A>>=31;
	nb1 = ar0		with gr0=gr7<<4;
	ar0 = vec_tbl_w_short_RSH with gr0=-gr0;
	ar0+= gr0;			// w table select 
	rep 8 wfifo=[ar0++],ftw;

	
	push ar5,gr5	with gr0=false;
	push ar6,gr6	with gr0++;
	
//	gr7 = [ar5++]	with gr0++;			// 	int				Shift	:[0, 1, 2, .., 7].
//	gr5 = [ar5++]	with gr6=gr0;		//	int				nSize,	//Size of input buffer in 8 bit elements. nSize=[256, 512, .., n*256].
//	ar6 = [ar5++]	with gr7<<=31;		//	nm16u*	pDstVec,		//Output buffer		:long Global[Size/8].
//	ar0 = [ar5++];						//	nm16u*	pSrcVec,		//Input buffer		:long Local [Size/8].
		

	gr5 = [ar5++]	with gr0++;			//	int				nSize,	//Size of input buffer in 8 bit elements. nSize=[256, 512, .., n*256].
	ar6 = [ar5++]	with gr6=gr0;		//	nm16u*	pDstVec,		//Output buffer		:long Global[Size/8].
	gr7 = [ar5++]	;					// 	int				Shift	:[0, 1, 2, .., 31].
	ar0 = [ar5++] with gr7<<=31;		//	nm16u*	pSrcVec,		//Input buffer		:long Local [Size/8].


	if =0 delayed goto Even_RightShift	with gr5>>=2;// nSize in 64-bit vectors
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




