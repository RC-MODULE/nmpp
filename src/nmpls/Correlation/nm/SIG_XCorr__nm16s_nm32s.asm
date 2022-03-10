//------------------------------------------------------------------------
//
//  $Workfile:: Convolution16to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   Convolution16to32.asm
//! \author Сергей Мушкаев
//! \brief  Функции свертки для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmpls"
/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation
// pDstVec[i]=pSrcVec[i]*pKernel[i]+pSrcVec[i+1]*pKernel[i%n+1]+...+pSrcVec[i+n]*pKernel[i%n+n]
//void SIG_XCorr(
//		nm32s*			pSrcVec			// input buffer		:long Local	[nSrcVecSize/2]
//		nm32s*			pKernel		// input buffer		:long Any   [nKernelSize/2]
//		nm64s*			pTmpBuff		// output buffer	:long Global[nKernelSize + 6]
//		nm32s*			pDstVec				// output buffer	:long Local	[(nSrcVecSize - nKernelSize)/2]
//		int				nKernelSize		// size of input buffer in 32 bit elements. nSize=[1,2,3...]
//		int				nSrcVecSize			// size of input buffer in 16 bit elements. nSize=[0,4,8...]
//		);
//
//  STATUS:
//		Test						: 
//		Core low level optimization : 
//		Function code  optimization	: 
//

//
//! \fn void SIG_XCorr(nm16s* pSrcVec, int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
//!
//! \n


global _SIG_XCorr__FPSsiPiiPiPv:label;
global _void._.8.8SIG_XCorr.1short._.0.9._int.9._int._.0.9._int.9._int._.0.9._void._.0.2 :label;
<_SIG_XCorr__FPSsiPiiPiPv>
<_void._.8.8SIG_XCorr.1short._.0.9._int.9._int._.0.9._int.9._int._.0.9._void._.0.2>
.branch;
	ar5 = sp - 2;

    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;


	ar0 = [--ar5];	// pSrcVec
	gr3 = [--ar5];	// nSrcVecSize
	ar1 = [--ar5];	// pKernel
	gr1 = [--ar5];	// nKernelSize
	ar6 = [--ar5];	// pDstVec
	ar4 = [--ar5];	// pTmpBuff


//Create matrix start

	sb	= 00020002h;
	nb1 = 80000000h;

//Create matrix start

	ar5 = ar4 + 4 with gr6 = gr1 - 1;// pTmpBuff

	gr2 = 0;
	ar2 = [ar1];

<CreateMatrix>
	[ar5++] = ar2,gr2;
	if > delayed goto CreateMatrix;
		gr2 = [ar1++] with gr6--;
		ar2 = [ar1];

	ar2 = 0;
	[ar5++] = ar2,gr2;

	gr2 = ar2;
.repeat 3;
	[ar5++] = ar2,gr2;// pTmpBuff(low)
.endrepeat;

	ar5 = ar4;// pTmpBuff
.repeat 2;
	[ar5++] = ar2,gr2;// pTmpBuff(High)
.endrepeat;
	
//Create matrix end

//Convolution calculation start
/////////////////////////////////////////////////////////////////////////////////////////
// Convolution Additional Function
/////////////////////////////////////////////////////////////////////////////////////////
//		ar0			pSrcVec		//Changed
//		ar4			pTmpBuff	//Not Changed
//		ar6			pDstVec			//Changed
//		gr1			nKernelSize	//Not Changed
//		gr3			nSrcVecSize		//Not Changed
//		gr6			SpacingSize		//Not Changed
/////////////////////////////////////////////////////////////////////////////////////////
	gr6 = 3;
	gr3 -= gr1;
	gr3 ++;
	gr3+= gr6;
	
	
	
	gr6 = 4;
	ar4 += 4;

	gr3 >>=2;
	
	push ar0,gr0;
	push ar6,gr6;

call SIG_XCorr_16to32;

	pop ar6,gr6;
	pop ar0,gr0;
	
	gr1 ++;	//Correct calculating with 
	gr1 ++;	//any convolution window

	ar4 -= 4;
	ar6 += 2;

call SIG_XCorr_16to32;
//Convolution calculation end

    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;

	return;

.wait;

/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation macro (nVal<32)
/////////////////////////////////////////////////////////////////////////////////////////
macro ConvolutionN(nVal)

own NextAddisionN:label;

	rep nVal data=[ar5] with data xor data;	//Put in afifo nulls

<NextAddisionN>
	rep 4 wfifo=[ar5++],ftw,wtw;

	ar3 = ar2;
	with gr4--;

	if >= delayed goto NextAddisionN;
	ar2 += gr2;
	rep nVal data=[ar3++] with vsum ,data,afifo;

	rep nVal [ar6++gr6] = afifo;	//Data output

	delayed goto EndConvolutionN;
		ar0 += 2*nVal;

end ConvolutionN;
/////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// Convolution Additional Function
/////////////////////////////////////////////////////////////////////////////////////////
//		ar0			pSrcVec		//Changed
//		ar4			pTmpBuff	//Not Changed
//		ar6			pDstVec			//Changed
//		gr1			nKernelSize	//Not Changed
//		gr3			nSrcVecSize		//Not Changed
//		gr6			SpacingSize		//Not Changed
/////////////////////////////////////////////////////////////////////////////////////////
<SIG_XCorr_16to32>
.branch;
//Convolution calculation start
	gr0 = 64;
	gr2 = 2;
	with gr5 = gr3;

		if <= delayed goto EndConvolutionN;
			gr7 = 80000000h;

		//with gr5>>=7;		//32  * 64bit word
		with gr5>>=5;		//32  * 64bit word

		if <= delayed goto EndConvolution32;
<StartConvolution>

  	ar5 = ar4 ;// pTmpBuff

	ar2 = ar0 with gr4 =gr1>>2;

	rep 32 data=[ar5] with data xor data;	//Put in afifo nulls

<NextAddision>
		rep 4 wfifo=[ar5++],ftw;
	
		.wait;
			nb1 = gr7;
			wtw;
		.branch;
	
		ar3 = ar2 with gr4--;
		if >= delayed goto NextAddision;
			ar2 += gr2;
			rep 32 data=[ar3++] with vsum ,data,afifo;
	
	with gr5--;
	if > delayed goto StartConvolution;
		ar0 += gr0;
		rep 32 [ar6++gr6] = afifo;	//Data output

<EndConvolution32>
//EndConvolution32

	gr5 = gr3;
	gr5 >>=5;
	gr5 <<=5;
	gr5 = gr3-gr5;	// столько осталось необработнных после rep 32
	
	
	//gr5 = gr3;
	//gr5 <<=25;		//	nVal%128*2^26
	//gr5 >>=27;		//	(nVal%128)/4

<StartConvolutionN>
local Start:label;
	ar5 = Start with gr5 <<=4;	//	((nVal%64)/2)*2^4
	ar5 += gr5 ;
	delayed goto ar5;
		ar2 = ar0  with gr4 = gr1>>2;
	  	ar5 = ar4;	// pTmpBuff

<Start>
	delayed goto EndConvolutionN;
		nul;
		nul;
		.repeat 12;
			nul;
		.endrepeat;

	ConvolutionN(1);
	ConvolutionN(2);
	ConvolutionN(3);
	ConvolutionN(4);
	ConvolutionN(5);
	ConvolutionN(6);
	ConvolutionN(7);
	ConvolutionN(8);
	ConvolutionN(9);
	ConvolutionN(10);
	ConvolutionN(11);
	ConvolutionN(12);
	ConvolutionN(13);
	ConvolutionN(14);
	ConvolutionN(15);
	ConvolutionN(16);
	ConvolutionN(17);
	ConvolutionN(18);
	ConvolutionN(19);
	ConvolutionN(20);
	ConvolutionN(21);
	ConvolutionN(22);
	ConvolutionN(23);
	ConvolutionN(24);
	ConvolutionN(25);
	ConvolutionN(26);
	ConvolutionN(27);
	ConvolutionN(28);
	ConvolutionN(29);
	ConvolutionN(30);
	ConvolutionN(31);

<EndConvolutionN>


//EndConvolutionN
	return;
//Convolution calculation end
.wait;


end ".text_nmpls";
