//------------------------------------------------------------------------
//
//  $Workfile:: Convolution32to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   Convolution32to32.asm
//! \author Сергей Мушкаев
//! \brief  Функции свертки для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation macro (nVal<32)
macro ConvolutionN(nVal)

own NextAddisionN:label;

	rep nVal data=[ar4] with data xor data;	//Put in afifo nulls

<NextAddisionN>
	rep 2 wfifo=[ar4++],ftw,wtw;

	ar3 = ar2;
	with gr4--;

	if >= delayed goto NextAddisionN;
	ar2 += gr2;
	rep nVal data=[ar3++] with vsum ,data,afifo;

	rep nVal [ar6++] = afifo;	//Data output

	delayed goto EndConvolutionN;
		ar0 += 2*nVal;

end ConvolutionN;
/////////////////////////////////////////////


begin ".text_nmpls"
/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation
// pDstVec[i]=pSrcVec[i]*pKernel[i]+pSrcVec[i+1]*pKernel[i%n+1]+...+pSrcVec[i+n]*pKernel[i%n+n]
//void nmppsXCorr_32s(
//		nm32s*			pSrcVec			// input buffer		:long Local	[nSrcVecSize/2]
//		nm32s*			pKernel		// input buffer		:long Any   [nKernelSize/2]	//If = -1 => Use Existing pTmpBuff matrix
//		nm64s*			pTmpBuff		// output buffer	:long Global[nKernelSize + 2]
//		nm32s*			pDstVec				// output buffer	:long Local	[(nSrcVecSize - nKernelSize)/2]
//		int				nKernelSize		// size of input buffer in 32 bit elements. nSize=[1,2,3...]
//		int				nSrcVecSize			// size of input buffer in 32 bit elements. nSize=[2,4,6...]
//		);
//
//  STATUS:
//		Test						: 
//		Core low level optimization : 
//		Function code  optimization	: 
//

//
//! \fn void nmppsXCorr_32s(nm32s* pSrcVec, int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
//!
//! \n

//void nmppsXCorr_32s(nm32s* pSrcVec, int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
global _nmppsXCorr_32s:label;
<_nmppsXCorr_32s>
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
	gr6 = [--ar5];	// nSrcVecSize
	ar1 = [--ar5];	// pKernel
	gr1 = [--ar5];	// nKernelSize
	ar6 = [--ar5];	// pDstVec
	ar4 = [--ar5];	// pTmpBuff


//Start//Start//Start//Start//Start//Start//Start//Start//Start//Start

	sb	= 00000002h;
	nb1 = 80000000h;

		gr7 = ar1;
		gr7++;//If = -1 => Use pTmpBuff matrix
	if =0 delayed goto StartConvolutionCalculation;
//Create matrix start//Create matrix start//Create matrix start

	ar5 = ar4 with gr2 = gr1 - 1;// pTmpBuff

	gr3 = 0;
	ar3 = [ar1];
<CreateMatrix>
	[ar5++] = ar3,gr3;
	if > delayed goto CreateMatrix;
		gr3 = [ar1++] with gr2--;
		ar3 = [ar1];

	ar3 = 0;
	[ar5++] = ar3,gr3;

	gr3 = ar3;
	[ar5++] = ar3,gr3;
	
//Create matrix end//Create matrix end//Create matrix end

<StartConvolutionCalculation>
//Convolution calculation start//Convolution calculation start//Convolution calculation start
	gr0 = 64;
	gr2 = 2;
	with gr5 = gr6 - gr1;
	gr5++;
	gr5++;
	
		if <= delayed goto EndConvolutionN;
			gr7 = 80000000h;
	
		with gr5>>=6;		//32  * 64bit word


		if <= delayed goto EndConvolution32;
<StartConvolution>
  	ar5 = ar4 with gr4 = gr1>>1;// pTmpBuff

	ar2 = ar0;

	rep 32 data=[ar4] with data xor data;	//Put in afifo nulls

	<NextAddision>
		rep 2 wfifo=[ar5++],ftw;
	
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
		rep 32 [ar6++] = afifo;	//Data output

<EndConvolution32>
//EndConvolution32//EndConvolution32//EndConvolution32//EndConvolution32

	gr5 = gr6 - gr1;
	gr5++;
	gr5++;
	
	gr5 <<=26;		//	nVal%64*2^26
	gr5 >>=27;		//	(nVal%64)/2

<StartConvolutionN>
local Start:label;
	ar5 = Start with gr5 <<=4;	//	((nVal%64)/2)*2^4
	ar5 += gr5;
	delayed goto ar5;
		ar2 = ar0 with gr4 = gr1>>1;
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
//EndConvolutionN//EndConvolutionN//EndConvolutionN//EndConvolutionN//EndConvolutionN

//Convolution calculation end//Convolution calculation end//Convolution calculation end//Convolution calculation end

    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;

	return; 

.wait;

end ".text_nmpls";
