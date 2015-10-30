//------------------------------------------------------------------------
//
//  $Workfile:: RSH32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   RSH32.asm
//! \author Павел Лукашевич 
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Vector Processing  Library                                            */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   $Workfile:: RSH32.asm                                                $*/
//*                                                                         */
//*   Contents:        Shift routines                                       */
//*                                                                         */
//*   Software design: Lukashevich                                           */
//*                                                                         */
//*   Version          1.0                                                  */
//*   Start date:      17.0.2002                                            */
//*   Release  $Date: 2004/11/22 13:50:05 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
//#include "vShift.h"

	import from macros.mlb;
	extern vec_vsum_shift_data_0:label;
	extern vec_vsum_data_0:label;

data ".data_nmplv_G"
		vec_tbl_w_int_RSH:long[8]=(
			// wights for right shift=2,3,4-7
			0hl,0000000000000001hl,	
			0hl,0000000100000000hl,	
			// wights for right shift=0,1
			00000000000000001hl,	00000000000000004hl,
			00000000100000000hl,	00000000400000000hl
			);

		vec_tbl_nb_sb_int_RSH:word[64]=(
			80000002h,// nb sh0
			0000000ah,// sb sh0
				0c0000002h,// nb sh1
				00000000ah,// sb sh1
			0a0000000h,// nb sh2	
			00000000ah,// sb sh2
				90000000h,// nb sh3	
				0000000ah,// sb sh3
			88000000h,// nb sh4
			00000022h,// sb sh4
				84000000h,// nb sh5
				00000022h,// sb sh5
			82000000h,// nb sh6
			00000082h,// sb sh6
				81000000h,// nb sh7
				00000082h,// sb sh7
			80800000h,// nb sh8
			00000202h,// sb sh8
				80400000h,// nb sh9
				00000202h,// sb sh9
			80200000h,// nb sh10	
			00000802h,// sb sh10
				80100000h,// nb sh11
				00000802h,// sb sh11
			80080000h,// nb sh12
			00002002h,// sb sh12
				80040000h,// nb sh13
				00002002h,// sb sh13
			80020000h,// nb sh14
			00008002h,// sb sh14
				80010000h,// nb sh15
				00008002h, // sb sh15
			80008000h,// nb sh16
			00020002h,// sb sh16
				80004000h,// nb sh17
				00020002h,// sb sh17
			80002000h,// nb sh18
			00080002h,// sb sh18
				80001000h,// nb sh19
				00080002h,// sb sh19
			80000800h,// nb sh20
			00200002h,// sb sh20
				80000400h,// nb sh21
				00200002h,// sb sh21
			80000200h,// nb sh22
			00800002h,// sb sh22
				80000100h,// nb sh23
				00800002h,// sb sh23
			80000080h,// nb sh24
			02000002h,// sb sh24
				80000040h,// nb sh25
				02000002h,// sb sh25
			80000020h,// nb sh26
			08000002h,// sb sh26
				80000010h,// nb sh27
				08000002h,// sb sh27
			80000008h,// nb sh28
			20000002h,// sb sh28
				80000004h,// nb sh29
				20000002h,// sb sh29
			80000002h,// nb sh30
			80000002h,// sb sh30
				80000001h,// nb sh31
				80000002h// sb sh31
			);
								

								

end ".data_nmplv_G";

begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////
// 
//! \fn void nmppsRshC_32u(nm32u *pSrcVec, int nShift, nm32u *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsRshC__FPUiiPUii_.html

global _nmppsRshC__FPUiiPUii_:label;
global _void._.8.8nmppsRshC_.1unsigned._int._.0.9._int.9._unsigned._int._.0.9._int.2 :label;
<_nmppsRshC__FPUiiPUii_>
<_void._.8.8nmppsRshC_.1unsigned._int._.0.9._int.9._unsigned._int._.0.9._int.2>
.branch;
	ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, .., 31].
	
	ar0 = vec_tbl_nb_sb_int_RSH with gr0<<=1;
	ar5-=2;
	ar0+= gr0		with gr7 = gr0>>2;
	ar0,gr0 = [ar0]	with gr7--;
	sb  = gr0		with gr7 A>>=31;
	nb1 = ar0		with gr0=gr7<< 3;
	ar0 = vec_tbl_w_int_RSH with gr0=-gr0;
	ar0+= gr0;			// w table select 
	rep 4 wfifo=[ar0++],ftw;

	
	push ar5,gr5	with gr0=false;
	push ar6,gr6	with gr0++;
	
//	gr7 = [ar5++]	with gr0++;			// 	int				Shift	:[0, 1, 2, .., 31].
//	gr5 = [ar5++]	with gr6=gr0;		//	int				VecSize,	//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
//	ar6 = [ar5++]	with gr7<<=31;		//	nm32u*	DstVec,		//Output buffer		:long Global[Size/8].
//	ar0 = [ar5++];						//	nm32u*	SrcVec,		//Input buffer		:long Local [Size/8].
		
	gr5 = [ar5++]	with gr0++;			//	int				VecSize,	//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
	ar6 = [ar5++]	with gr6=gr0;		//	nm32u*	DstVec,		//Output buffer		:long Global[Size/8].
	gr7 = [ar5++]	;					// 	int				Shift	:[0, 1, 2, .., 31].
	ar0 = [ar5++] with gr7<<=31;		//	nm32u*	SrcVec,		//Input buffer		:long Local [Size/8].


	if =0 delayed goto Even_RightShift	with gr5>>=1;// Size in 64-bit vectors
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




