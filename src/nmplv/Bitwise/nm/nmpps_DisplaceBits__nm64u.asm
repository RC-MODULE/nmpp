//------------------------------------------------------------------------
//
//  $Workfile:: PushBits.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   PushBits.asm
//! \author Сергей Мушкаев
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
// "vShift.h"

macro WTW_REG2(Reg1,Reg2)
	.wait;
		nb1l = Reg1;
		nb1h = Reg2;
		wtw;
	.branch;
end WTW_REG2;
import from rtmacro.mlb;
import from macros.mlb;

data ".data_nmplv_G"
	PushWoper:long[4]=(0hl,0hl,0hl,1hl);
	Tmp:long;
end ".data_nmplv_G";


begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
// Pushes nBits highest bits of  64-bit word-pBits into the begining of buffer-pSrcVec. 
// Buffer pSrcVec is considered as a bitstream being contained in 64-bit array 
// and bits are moving by continuous shift.
// In 64-bit word-pBits the lower bits are moved to the higher positions. 
// And within pSrcVec buffer hightest bits are moved to lowest positions of the next 64-bit word
// Example : 
// pushing of 8 bits: pBits=[AB00000000000000]
// into                 pSrcVec=[0807060504030201][FF0F0E0D0C0B0A09]....... will give
//						pDstVec=[07060504030201AB][0F0E0D0C0B0A0908]....... (last 8 bits of pSrcVec will be lost)
// If you point pBits to the last 64-bit word of pSrcVec buffer you will get the cyclical bit shift
//
// void nmppsPushBits_(
//	const   nm1*	pSrcVec,		//Input buffer					:long Local [Size/8].
//			nm1*	pDstVec,		//Output buffer					:long Global[Size/8].
//			nm1*	pBits,		//Being pushed bits				:long Variable
//			int		nBits,		//Number of being pushed bits	:nBits=[2,4,6....62].
//			int		nSize		//Size of input buffer in 64-bit long elements. nSize=[1,2,3....].
//	);
//
// RETURN: 0
//
//
//  PERFORMANCE:
//
//	nmppsPushBits_1*((nm1*)L0,(nm1*)L0,(nm1*)L0,8,352*288/8);//56061 (temu) 0.553 clocks per pixel
//	nmppsPushBits_1*((nm1*)L0,(nm1*)G0,(nm1*)L0,8,352*288/8);//55263 (temu)
//	nmppsPushBits_1*((nm1*)G0,(nm1*)L0,(nm1*)L0,8,352*288/8);//56457 (temu)
//	nmppsPushBits_1*((nm1*)G0,(nm1*)G0,(nm1*)L0,8,352*288/8);//56055 (temu)
// 	
//		The function performance  depends on memory allocation for  
//		input and output buffers.
//		For the maximum speed performance it is recommended  
//		to use the following configurations:
//		Configuration I.
//			pSrcVec:		Global SRAM
//			pDstVec:		Local  SRAM
//			  ticks per 256   elements with C++ call 
//			 ticks per 10240 elements with C++ call (0.582 clocks per element)
//		Configuration II.	
//			pSrcVec:		local  SRAM
//			pDstVec:		Global SRAM
//			  ticks per 256   elements with C++ call 
//			 ticks per 10240 elements with C++ call (0.550 clocks per element)
//
//	COMMENTS:
//		The order of intermediate data transmissions in function is:
//			pSrcVec[]			=> pDstVec[]				- Conversion	(in-place is forbidden)
//
// STATUS:
//	Test		:Done
//	Optimization:

///////////////////////////////////////////////////////////
//! \fn void nmppsDisplaceBits_(const nm64u* pSrcVec, nm64u* pDstVec, nm64u* pnBits, int nBits, int nSize)
//!
//! \perfinclude _nmppsDisplaceBits__FPCUlPUlPUlii_.html
//! \todo Needs in optimization


global _nmppsFwdShiftBitstream:label;
<_nmppsFwdShiftBitstream>
.branch;
	ar5 = sp - 2;

	PUSH_REGS();
	
	ar0 = [--ar5];	// pSrcVec
	ar6 = [--ar5];	// pDstVec
	ar2 = [--ar5];	// pnBits
	gr6 = [--ar5];	// nBits
	ar1 = [--ar5];	// nSize
	
	ar3,gr3=[ar2];
	[Tmp]=ar3,gr3;
	
	//	nb1	0000000000000002hl	gr0,gr1
	//	sb	2000000000000000hl  gr2,gr0
	//	wo	0000000000000001hl  gr0,gr3

	//gr0 = 0;
	//gr1 = 40000000h;
	//gr2 = 4;
	//gr3 = 80000000h;

	gr0 = 0;
	gr1 = 2;
	gr2 = 80000000h;
	gr3 = 4h;

	
	gr6--;
	gr6--;
	
//	nb1	4000000000000000hl	gr1,gr0
//	sb	0000000000000004hl  gr0,gr2
//	wo	8000000000000000hl  gr3,gr0
	ar4 = PushWoper;
	
	LSHIFT64(gr4,gr5,gr3,gr0,gr6);
	[ar4++] = gr4;
	[ar4++] = gr5;
	ar4 -= 2;
	RSHIFT64(gr4,gr5,gr0,gr2,gr6);
	sbl = gr4;
	sbh = gr5;
	LSHIFT64(gr4,gr5,gr1,gr0,gr6);
	
	nb1l=gr4;
	nb1h=gr5;
	
	gr6 = ar1;
	//with gr6>>=6; //size in longs
	
	/////////////////////////////////////////////////////////////
	push ar6,gr6;
	with gr7 = gr6 >> 5;
	if =0 delayed goto PushBits_even_rep1 with gr7 --;
		ar1 = ar0-2;
	
	<Next_PushBits_even_rep32>
		ar4 = PushWoper;
		rep 4 wfifo=[ar4++], ftw;
		WTW_REG2(gr4,gr5);
		rep 32 data=[ar0++],ftw with vsum ,data,0;
		WTW_REG2(gr4,gr5);
	if <>0 delayed goto Next_PushBits_even_rep32 with gr7--;
		rep 32 data=[ar1++] with vsum ,data,afifo;
		rep 32 [ar6++]=afifo;

	<PushBits_even_rep1>
	with gr7 = gr6 << 27;
	with gr7 >>= 27;
	if =0 delayed goto PushBits_Finish with gr7 --;
		nul;
		nul;
	<Next_PushBits_even_rep1>
		ar4 = PushWoper;
		rep 4 wfifo=[ar4++],ftw;
		WTW_REG2(gr4,gr5);
		rep 1 data=[ar0++],ftw with vsum ,data,0;
		WTW_REG2(gr4,gr5);
	if <>0 delayed goto Next_PushBits_even_rep1 with gr7--;
		rep 1 data=[ar1++] with vsum ,data,afifo;
		rep 1 [ar6++]=afifo;

	<PushBits_Finish>

	// Pushing start bits
	pop ar6,gr6;
	ar3 = Tmp;
	rep 1 with 0-1;
	rep 1 with vsum ,afifo,0;
	rep 1 data =[ar6] with mask afifo,0,data;
	rep 1 data =[ar3] with vsum ,data,afifo;
	rep 1 [ar6]=afifo;


POP_REGS();
	return;
.wait;
end ".text_nmplv"; 
