//------------------------------------------------------------------------
//
//  $Workfile:: RSH64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   RSH64.asm
//! \author Павел Лукашевич
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vShift.h"
	import from macros.mlb;

	extern vec_vsum_shift_data_0:label;
	extern vec_vsum_data_0:label;

data ".data_nmplv_G"
		vec_tbl_w_long_RSH:long[4]=(
			// wights for right shift=2,3,4-7
			00000000000000000hl,	0000000000000001hl,	
			// wights for right shift=0,1
			00000000000000001hl,	00000000000000004hl
			);

		vec_tbl_nb_sb_long_RSH:long[128]=(
			
			8000000000000002hl,	//nb shr 0
			0000000000000008hl,	//sb shr 0
			
			4000000000000002hl,	//nb shr 1
			0000000000000008hl,	//sb shr 1

			2000000000000000hl,	//nb shr 2
			0000000000000008hl,	//sb shr 2

			1000000000000000hl,	//nb shr 3
			0000000000000008hl,	//sb shr 3

			0800000000000000hl,	//nb shr 4
			0000000000000020hl,	//sb shr 4

			0400000000000000hl,	//nb shr 5
			0000000000000020hl,	//sb shr 5

			0200000000000000hl,	//nb shr 6
			0000000000000080hl,	//sb shr 6

			0100000000000000hl,	//nb shr 7
			0000000000000080hl,	//sb shr 7

			0080000000000000hl,	//nb shr 8
			0000000000000200hl,	//sb shr 8

			0040000000000000hl,	//nb shr 9
			0000000000000200hl,	//sb shr 9

			0020000000000000hl,	//nb shr 10
			0000000000000800hl,	//sb shr 10

			0010000000000000hl,	//nb shr 11
			0000000000000800hl,	//sb shr 11

			0008000000000000hl,	//nb shr 12
			0000000000002000hl,	//sb shr 12

			0004000000000000hl,	//nb shr 13
			0000000000002000hl,	//sb shr 13

			0002000000000000hl,	//nb shr 14
			0000000000008000hl,	//sb shr 14

			0001000000000000hl,	//nb shr 15
			0000000000008000hl,	//sb shr 15

			0000800000000000hl,	//nb shr 16
			0000000000020000hl,	//sb shr 16

			0000400000000000hl,	//nb shr 17
			0000000000020000hl,	//sb shr 17

			0000200000000000hl,	//nb shr 18
			0000000000080000hl,	//sb shr 18

			0000100000000000hl,	//nb shr 19
			0000000000080000hl,	//sb shr 19

			0000080000000000hl,	//nb shr 20
			0000000000200000hl,	//sb shr 20

			0000040000000000hl,	//nb shr 21
			0000000000200000hl,	//sb shr 21

			0000020000000000hl,	//nb shr 22
			0000000000800000hl,	//sb shr 22

			0000010000000000hl,	//nb shr 23
			0000000000800000hl,	//sb shr 23

			0000008000000000hl,	//nb shr 24
			0000000002000000hl,	//sb shr 24

			0000004000000000hl,	//nb shr 25
			0000000002000000hl,	//sb shr 25

			0000002000000000hl,	//nb shr 26
			0000000008000000hl,	//sb shr 26

			0000001000000000hl,	//nb shr 27
			0000000008000000hl,	//sb shr 27

			0000000800000000hl,	//nb shr 28
			0000000020000000hl,	//sb shr 28

			0000000400000000hl,	//nb shr 29
			0000000020000000hl,	//sb shr 29

			0000000200000000hl,	//nb shr 30
			0000000080000000hl,	//sb shr 30

			0000000100000000hl,	//nb shr 31
			0000000080000000hl,	//sb shr 31

			0000000080000000hl,	//nb shr 32
			0000000200000000hl,	//sb shr 32

			0000000040000000hl,	//nb shr 33
			0000000200000000hl,	//sb shr 33

			0000000020000000hl,	//nb shr 34
			0000000800000000hl,	//sb shr 34

			0000000010000000hl,	//nb shr 35
			0000000800000000hl,	//sb shr 35

			0000000008000000hl,	//nb shr 36
			0000002000000000hl,	//sb shr 36

			0000000004000000hl,	//nb shr 37
			0000002000000000hl,	//sb shr 37

			0000000002000000hl,	//nb shr 38
			0000008000000000hl,	//sb shr 38

			0000000001000000hl,	//nb shr 39
			0000008000000000hl,	//sb shr 39

			0000000000800000hl,	//nb shr 40
			0000020000000000hl,	//sb shr 40

			0000000000400000hl,	//nb shr 41
			0000020000000000hl,	//sb shr 41

			0000000000200000hl,	//nb shr 42
			0000080000000000hl,	//sb shr 42

			0000000000100000hl,	//nb shr 43
			0000080000000000hl,	//sb shr 43

			0000000000080000hl,	//nb shr 44
			0000200000000000hl,	//sb shr 44

			0000000000040000hl,	//nb shr 45
			0000200000000000hl,	//sb shr 45

			0000000000020000hl,	//nb shr 46
			0000800000000000hl,	//sb shr 46

			0000000000010000hl,	//nb shr 47
			0000800000000000hl,	//sb shr 47

			0000000000008000hl,	//nb shr 48
			0002000000000000hl,	//sb shr 48

			0000000000004000hl,	//nb shr 49
			0002000000000000hl,	//sb shr 49

			0000000000002000hl,	//nb shr 50
			0008000000000000hl,	//sb shr 50

			0000000000001000hl,	//nb shr 51
			0008000000000000hl,	//sb shr 51

			0000000000000800hl,	//nb shr 52
			0020000000000000hl,	//sb shr 52

			0000000000000400hl,	//nb shr 53
			0020000000000000hl,	//sb shr 53

			0000000000000200hl,	//nb shr 54
			0080000000000000hl,	//sb shr 54

			0000000000000100hl,	//nb shr 55
			0080000000000000hl,	//sb shr 55

			0000000000000080hl,	//nb shr 56
			0200000000000000hl,	//sb shr 56

			0000000000000040hl,	//nb shr 57
			0200000000000000hl,	//sb shr 57

			0000000000000020hl,	//nb shr 58
			0800000000000000hl,	//sb shr 58

			0000000000000010hl,	//nb shr 59
			0800000000000000hl,	//sb shr 59

			0000000000000008hl,	//nb shr 60
			2000000000000000hl,	//sb shr 60

			0000000000000004hl,	//nb shr 61
			2000000000000000hl,	//sb shr 61

			0000000000000002hl,	//nb shr 62
			8000000000000000hl,	//sb shr 62

			0000000000000001hl,	//nb shr 63
			8000000000000000hl	//sb shr 63
			);
								

								

end ".data_nmplv_G";

begin ".text_nmplv"



///////////////////////////////////////////////////////////////////////////////////////
// 
//! \fn void VEC_RshC (nm64u *pSrcVec, int nShift, nm64u *pDstVec, int nSize) 
//!
//! \perfinclude _VEC_RshC__FPUliPUli.html

global _VEC_RshC__FPUliPUli:label;
global _void._.8.8VEC_RshC.1unsigned._long._.0.9._int.9._unsigned._long._.0.9._int.2 :label;
<_VEC_RshC__FPUliPUli>
<_void._.8.8VEC_RshC.1unsigned._long._.0.9._int.9._unsigned._long._.0.9._int.2>
.branch;
	ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, .., 31].
	
	ar0 = vec_tbl_nb_sb_long_RSH with gr0<<=2;
	ar5-=2;
	ar0+= gr0		with gr7 = gr0>>3;
	nb1 = [ar0++]	with gr7--;
	sb  = [ar0]		with gr7 A>>=31;
	with gr0=gr7<< 2;
	ar0 = vec_tbl_w_long_RSH with gr0=-gr0;
	ar0+= gr0;			// w table select 
	rep 2 wfifo=[ar0++],ftw;

	
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


	if =0 delayed goto Even_RightShift	with gr5;// Size in 64-bit vectors
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
