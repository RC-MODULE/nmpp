//------------------------------------------------------------------------
//
//  $Workfile:: ARSH64.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   ARSH64.asm
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
		vec_tbl_w_long_ARSH:long[3*64]=(

				//ArShr 0
				00000000000000001hl,
				00000000000000004hl,
				04000000000000000hl,

				//ArShr 1
				00000000000000001hl,
				00000000000000004hl,
				0c000000000000000hl,

				//ArShr 2
				00000000000000000hl,
				00000000000000001hl,
				01000000000000000hl,

				//ArShr 3
				00000000000000000hl,
				00000000000000001hl,
				0f000000000000000hl,

				//ArShr 4
				00000000000000000hl,
				00000000000000001hl,
				00400000000000000hl,

				//ArShr 5
				00000000000000000hl,
				00000000000000001hl,
				0fc00000000000000hl,

				//ArShr 6
				00000000000000000hl,
				00000000000000001hl,
				00100000000000000hl,

				//ArShr 7
				00000000000000000hl,
				00000000000000001hl,
				0ff00000000000000hl,

				//ArShr 8
				00000000000000000hl,
				00000000000000001hl,
				00040000000000000hl,

				//ArShr 9
				00000000000000000hl,
				00000000000000001hl,
				0ffc0000000000000hl,

				//ArShr 10
				00000000000000000hl,
				00000000000000001hl,
				00010000000000000hl,

				//ArShr 11
				00000000000000000hl,
				00000000000000001hl,
				0fff0000000000000hl,

				//ArShr 12
				00000000000000000hl,
				00000000000000001hl,
				00004000000000000hl,

				//ArShr 13
				00000000000000000hl,
				00000000000000001hl,
				0fffc000000000000hl,

				//ArShr 14
				00000000000000000hl,
				00000000000000001hl,
				00001000000000000hl,

				//ArShr 15
				00000000000000000hl,
				00000000000000001hl,
				0ffff000000000000hl,

				//ArShr 16
				00000000000000000hl,
				00000000000000001hl,
				00000400000000000hl,

				//ArShr 17
				00000000000000000hl,
				00000000000000001hl,
				0ffffc00000000000hl,

				//ArShr 18
				00000000000000000hl,
				00000000000000001hl,
				00000100000000000hl,

				//ArShr 19
				00000000000000000hl,
				00000000000000001hl,
				0fffff00000000000hl,

				//ArShr 20
				00000000000000000hl,
				00000000000000001hl,
				00000040000000000hl,

				//ArShr 21
				00000000000000000hl,
				00000000000000001hl,
				0fffffc0000000000hl,

				//ArShr 22
				00000000000000000hl,
				00000000000000001hl,
				00000010000000000hl,

				//ArShr 23
				00000000000000000hl,
				00000000000000001hl,
				0ffffff0000000000hl,

				//ArShr 24
				00000000000000000hl,
				00000000000000001hl,
				00000004000000000hl,

				//ArShr 25
				00000000000000000hl,
				00000000000000001hl,
				0ffffffc000000000hl,

				//ArShr 26
				00000000000000000hl,
				00000000000000001hl,
				00000001000000000hl,

				//ArShr 27
				00000000000000000hl,
				00000000000000001hl,
				0fffffff000000000hl,

				//ArShr 28
				00000000000000000hl,
				00000000000000001hl,
				00000000400000000hl,

				//ArShr 29
				00000000000000000hl,
				00000000000000001hl,
				0fffffffc00000000hl,

				//ArShr 30
				00000000000000000hl,
				00000000000000001hl,
				00000000100000000hl,

				//ArShr 31
				00000000000000000hl,
				00000000000000001hl,
				0ffffffff00000000hl,

				//ArShr 32
				00000000000000000hl,
				00000000000000001hl,
				00000000040000000hl,

				//ArShr 33
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffc0000000hl,

				//ArShr 34
				00000000000000000hl,
				00000000000000001hl,
				00000000010000000hl,

				//ArShr 35
				00000000000000000hl,
				00000000000000001hl,
				0fffffffff0000000hl,

				//ArShr 36
				00000000000000000hl,
				00000000000000001hl,
				00000000004000000hl,

				//ArShr 37
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffc000000hl,

				//ArShr 38
				00000000000000000hl,
				00000000000000001hl,
				00000000001000000hl,

				//ArShr 39
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffff000000hl,

				//ArShr 40
				00000000000000000hl,
				00000000000000001hl,
				00000000000400000hl,

				//ArShr 41
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffffc00000hl,

				//ArShr 42
				00000000000000000hl,
				00000000000000001hl,
				00000000000100000hl,

				//ArShr 43
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffff00000hl,

				//ArShr 44
				00000000000000000hl,
				00000000000000001hl,
				00000000000040000hl,

				//ArShr 45
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffffc0000hl,

				//ArShr 46
				00000000000000000hl,
				00000000000000001hl,
				00000000000010000hl,

				//ArShr 47
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffffff0000hl,

				//ArShr 48
				00000000000000000hl,
				00000000000000001hl,
				00000000000004000hl,

				//ArShr 49
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffffffc000hl,

				//ArShr 50
				00000000000000000hl,
				00000000000000001hl,
				00000000000001000hl,

				//ArShr 51
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffffff000hl,

				//ArShr 52
				00000000000000000hl,
				00000000000000001hl,
				00000000000000400hl,

				//ArShr 53
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffffffc00hl,

				//ArShr 54
				00000000000000000hl,
				00000000000000001hl,
				00000000000000100hl,

				//ArShr 55
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffffffff00hl,

				//ArShr 56
				00000000000000000hl,
				00000000000000001hl,
				00000000000000040hl,

				//ArShr 57
				00000000000000000hl,
				00000000000000001hl,
				0ffffffffffffffc0hl,

				//ArShr 58
				00000000000000000hl,
				00000000000000001hl,
				00000000000000010hl,

				//ArShr 59
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffffffff0hl,

				//ArShr 60
				00000000000000000hl,
				00000000000000001hl,
				00000000000000004hl,

				//ArShr 61
				00000000000000000hl,
				00000000000000001hl,
				0fffffffffffffffchl,

				//ArShr 62
				00000000000000000hl,
				00000000000000000hl,
				00000000000000001hl,

				//ArShr 63
				00000000000000000hl,
				00000000000000000hl,
				0ffffffffffffffffhl

				);


		vec_tbl_nb_sb_long_ARSH:long[64*2]=(

				02000000000000002hl,	//nb shr 0
				08000000000000008hl,	//sb shr 0

				06000000000000002hl,	//nb shr 1
				08000000000000008hl,	//sb shr 1

				08800000000000000hl,	//nb shr 2
				0800000000000000ahl,	//sb shr 2

				0f800000000000000hl,	//nb shr 3
				0800000000000000ahl,	//sb shr 3

				08200000000000000hl,	//nb shr 4
				08000000000000022hl,	//sb shr 4

				0fe00000000000000hl,	//nb shr 5
				08000000000000022hl,	//sb shr 5

				08080000000000000hl,	//nb shr 6
				08000000000000082hl,	//sb shr 6

				0ff80000000000000hl,	//nb shr 7
				08000000000000082hl,	//sb shr 7

				08020000000000000hl,	//nb shr 8
				08000000000000202hl,	//sb shr 8

				0ffe0000000000000hl,	//nb shr 9
				08000000000000202hl,	//sb shr 9

				08008000000000000hl,	//nb shr 10
				08000000000000802hl,	//sb shr 10

				0fff8000000000000hl,	//nb shr 11
				08000000000000802hl,	//sb shr 11

				08002000000000000hl,	//nb shr 12
				08000000000002002hl,	//sb shr 12

				0fffe000000000000hl,	//nb shr 13
				08000000000002002hl,	//sb shr 13

				08000800000000000hl,	//nb shr 14
				08000000000008002hl,	//sb shr 14

				0ffff800000000000hl,	//nb shr 15
				08000000000008002hl,	//sb shr 15

				08000200000000000hl,	//nb shr 16
				08000000000020002hl,	//sb shr 16

				0ffffe00000000000hl,	//nb shr 17
				08000000000020002hl,	//sb shr 17

				08000080000000000hl,	//nb shr 18
				08000000000080002hl,	//sb shr 18

				0fffff80000000000hl,	//nb shr 19
				08000000000080002hl,	//sb shr 19

				08000020000000000hl,	//nb shr 20
				08000000000200002hl,	//sb shr 20

				0fffffe0000000000hl,	//nb shr 21
				08000000000200002hl,	//sb shr 21

				08000008000000000hl,	//nb shr 22
				08000000000800002hl,	//sb shr 22

				0ffffff8000000000hl,	//nb shr 23
				08000000000800002hl,	//sb shr 23

				08000002000000000hl,	//nb shr 24
				08000000002000002hl,	//sb shr 24

				0ffffffe000000000hl,	//nb shr 25
				08000000002000002hl,	//sb shr 25

				08000000800000000hl,	//nb shr 26
				08000000008000002hl,	//sb shr 26

				0fffffff800000000hl,	//nb shr 27
				08000000008000002hl,	//sb shr 27

				08000000200000000hl,	//nb shr 28
				08000000020000002hl,	//sb shr 28

				0fffffffe00000000hl,	//nb shr 29
				08000000020000002hl,	//sb shr 29

				08000000080000000hl,	//nb shr 30
				08000000080000002hl,	//sb shr 30

				0ffffffff80000000hl,	//nb shr 31
				08000000080000002hl,	//sb shr 31

				08000000020000000hl,	//nb shr 32
				08000000200000002hl,	//sb shr 32

				0ffffffffe0000000hl,	//nb shr 33
				08000000200000002hl,	//sb shr 33

				08000000008000000hl,	//nb shr 34
				08000000800000002hl,	//sb shr 34

				0fffffffff8000000hl,	//nb shr 35
				08000000800000002hl,	//sb shr 35

				08000000002000000hl,	//nb shr 36
				08000002000000002hl,	//sb shr 36

				0fffffffffe000000hl,	//nb shr 37
				08000002000000002hl,	//sb shr 37

				08000000000800000hl,	//nb shr 38
				08000008000000002hl,	//sb shr 38

				0ffffffffff800000hl,	//nb shr 39
				08000008000000002hl,	//sb shr 39

				08000000000200000hl,	//nb shr 40
				08000020000000002hl,	//sb shr 40

				0ffffffffffe00000hl,	//nb shr 41
				08000020000000002hl,	//sb shr 41

				08000000000080000hl,	//nb shr 42
				08000080000000002hl,	//sb shr 42

				0fffffffffff80000hl,	//nb shr 43
				08000080000000002hl,	//sb shr 43

				08000000000020000hl,	//nb shr 44
				08000200000000002hl,	//sb shr 44

				0fffffffffffe0000hl,	//nb shr 45
				08000200000000002hl,	//sb shr 45

				08000000000008000hl,	//nb shr 46
				08000800000000002hl,	//sb shr 46

				0ffffffffffff8000hl,	//nb shr 47
				08000800000000002hl,	//sb shr 47

				08000000000002000hl,	//nb shr 48
				08002000000000002hl,	//sb shr 48

				0ffffffffffffe000hl,	//nb shr 49
				08002000000000002hl,	//sb shr 49

				08000000000000800hl,	//nb shr 50
				08008000000000002hl,	//sb shr 50

				0fffffffffffff800hl,	//nb shr 51
				08008000000000002hl,	//sb shr 51

				08000000000000200hl,	//nb shr 52
				08020000000000002hl,	//sb shr 52

				0fffffffffffffe00hl,	//nb shr 53
				08020000000000002hl,	//sb shr 53

				08000000000000080hl,	//nb shr 54
				08080000000000002hl,	//sb shr 54

				0ffffffffffffff80hl,	//nb shr 55
				08080000000000002hl,	//sb shr 55

				08000000000000020hl,	//nb shr 56
				08200000000000002hl,	//sb shr 56

				0ffffffffffffffe0hl,	//nb shr 57
				08200000000000002hl,	//sb shr 57

				08000000000000008hl,	//nb shr 58
				08800000000000002hl,	//sb shr 58

				0fffffffffffffff8hl,	//nb shr 59
				08800000000000002hl,	//sb shr 59

				08000000000000002hl,	//nb shr 60
				0a000000000000002hl,	//sb shr 60

				0fffffffffffffffehl,	//nb shr 61
				0a000000000000002hl,	//sb shr 61

				08000000000000000hl,	//nb shr 62
				08000000000000008hl,	//sb shr 62

				0ffffffffffffffffhl,	//nb shr 63
				08000000000000008hl 	//sb shr 63
						
				);
								
end ".data_nmplv_G";

begin ".text_nmplv"

///////////////////////////////////////////////////////////////////////////////////////
// 
//! \fn void nmppsRShiftC_64s(nm64s *pSrcVec, int nShift, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsRShiftC_64s.html

global _nmppsRShiftC_64s:label;
<_nmppsRShiftC_64s>
.branch;
	ar5 = sp - 4;
	push ar0,gr0;
	gr0 = [ar5];		//	int				Shift	 :[0, 1, 2, .., 31].
	
	ar0 = vec_tbl_nb_sb_long_ARSH set with gr0<<=2;
	ar5-=2;
	ar0+= gr0 with gr0>>=1;//gr0 = Shift*2
	nb1 = [ar0++] with gr7 = gr0<<1;//gr7 = Shift*8*2
	sb  = [ar0];
	ar0 = vec_tbl_w_long_ARSH set with gr0 += gr7;//gr0 = Shift*2*2 + Shift*2
	ar0+= gr0;			// w table select 
	rep 3 wfifo=[ar0++],ftw;

	
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
