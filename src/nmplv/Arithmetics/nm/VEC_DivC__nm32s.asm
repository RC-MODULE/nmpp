//------------------------------------------------------------------------
//
//  $Workfile:: Div32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Div32.asm
//! \author Сергей Мушкаев
//! \brief  Функции деления для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

extern DivS4095byU145:long;
extern vec_vsum_data_0:label;
extern vec_IncNeg:label;
import from macros.mlb;


begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////
// Elementwise division of 32-bit signed

//! \fn void nmppsDivC (nm32s *pSrcVec, int nDivisor, nm32s *pDstVec, int nSize, void *pTmpBuf1, void *pTmpBuf2) 
//!
//! \perfinclude _nmppsDivC__FPiiPiiPvPv.html

global _nmppsDivC__FPiiPiiPvPv :label;
global _void._.8.8nmppsDivC.1int._.0.9._int.9._int._.0.9._int.9._void._.0.9._void._.0.2 :label;
<_nmppsDivC__FPiiPiiPvPv>
<_void._.8.8nmppsDivC.1int._.0.9._int.9._int._.0.9._int.9._void._.0.9._void._.0.2>
.branch;

	//ar5 = ar7-6		with gr7 = false;
	ar5 = ar7-4		with gr7 = false;
	push ar0,gr0	with gr7++;
	
	gr0 = [ar5++]		with gr7++;					//	int		Divisor
	ar0 = DivS4095byU145; 		
	sb  = gr7		with gr7<<=30;				// sb=2 gr7=80000000h
	nb1 = gr7		with gr0<<= 2;				// nb1=80000000h 
	
	// 1/X Divisors Loading 
	ar0 += gr0;
	rep 2 wfifo=[ar0++],ftw;

	f1cr= gr7;
	//ar5 = ar5+6-2;
	push ar1,gr1	with gr7>>=30;				// gr7=2
	push ar5,gr5	with gr0=gr7;				// gr0=2
	push ar6,gr6	with gr6=gr7;				// gr6=2
	

	ar0 = [ar5];								//	nm32s*	pSrcVec
	gr1 = [--ar5];								//	int		Divisor
	ar6 = [--ar5];								//	nm32s*	pDstVec,		
	gr5 = [--ar5];								//	int		nSize
	
	
	// nb,sb,f1cr Initialization
	
	ar1	= [--ar5];	//	void*	pTmpBuf1			// Temporary buffer
	gr1	= [--ar5];	//	void*	pTmpBuf2			// Temporary buffer 

	push ar6,gr6;
	///////////////////////////////////////////////////////////////
	// 1/x multiplication	
	// [pSrcVec] => [pTmpBuf1]

	delayed call vec_vsum_data_0	with gr5>>=1;
		wtw;
		ar6 = ar1;

	
	//////////////////////////////////////////////////////////////
	// Right shift scaling
	// [pTmpBuf1] => [pTmpBuf2]

	gr7 = 19 with gr5<<=1;
//	VEC_ARSH32_RRRR(ar1,gr1,gr5,gr7);				




	extern _void._.8.8nmppsArshC_.1int._.0.9._int.9._int._.0.9._int.2:label;
	ar5 = ar7;
	ar7 += 4;
	[ ar5++ ] = gr5;			// int nSize
	[ ar5++ ] = gr1;			// nm32s* pDstVec
	delayed call _void._.8.8nmppsArshC_.1int._.0.9._int.9._int._.0.9._int.2;
		[ ar5++ ] = gr7;		// int nShift
		[ ar5++ ] = ar1;		// nm32s* pSrcVec
	nul;
	ar7-=4; 

	///////////////////////////////////////////////////////////////
	// Result Correction
	// [pTmpBuf2] => [pDstVec]
	ar0 = gr1		with gr7=true;
	pop ar6,gr6		with gr7<<=31;
	delayed call vec_IncNeg with gr5>>=1;
		nb1 = gr7;
		wtw;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;


/////////////////////////////////////////////////////////////////////////////////
// void nmppsDiv_By2Int_(
//			nm32s*	pSrcVec,			// Input array 					:long Global[NumbersOfPairs*SrcPairReadStep/2]
//			nm32s*	pDstVec,			// Output qunatized array		:long Local [NumbersOfPairs*DstPairWriteStep/2]
//			nm32s*	PairOfDivisors,		// pArray of two Divisors		:long Local [2/2]; PairOfDivisors[0,1]=[1,2,3...128]
//			int		NumberOfPairs,		// Number of input pairs should be quantized: =[1,2,3...]
//			void*	pTmpBuf1,			// First  Temporary array		:long Local [NumbersOfPairs]
//			void*	pTmpBuf2,			// Second Temporary array		:long Local [NumbersOfPairs]
//			int		SrcReadStep=2,		// From pair to pair reading step (in 32-bit words): =[2,4,6...]
//			int		DstWriteStep=2		// From pair to pair writing step (in 32-bit words): =[2,4,6...] 
//			);							
//
// DESCRIPTION:
//
// Division of 32-bit signed words of array by pair of divisors, packed in 64-bit words.
// Numbers placed at even addresses are divided by first  divisor.
// Numbers placed at odd  addresses are divided by second divisor.
// Division may be performed by sampling in source array with specified spacing between pairs.
// Results are stored also by pair, packed in 64-bit words.
// The write step of pairs also can be specified.
// By default both steps are equal to 2.
// Operation of this  function may be descibed in next equivalent form:
// for(int i=0,j=0,n=0;n<NumbersOfPairs;n++,i+=SrcReadStep,j+=DstWriteSpep)
// {
//		pDstVec[j]  =pSrcVec[i]  /PairOfDivisors[0];
//		pDstVec[j+1]=pSrcVec[i+1]/PairOfDivisors[1];
// }
//
//  RETURN: 0
//
//  PERFORMANCE:
//		The performance of function depends on memory allocation for  
//		input, output  and temporary buffers.
//		For the maximum speed performance it is recommended  
//		to use the following configuration:
//
//		Configuration I:
//			pSrcVec		: Local		SRAM
//			pDstVec		: Global	SRAM
//			TempBuffer1		: Global	SRAM
//			TempBuffer2		: Local		SRAM
//
//			4659 clocks per 1024 int pairs with C++ call (2.27 clocks per 32bit word)
//
//		Configuration II:	
//			pSrcVec		: Global	SRAM
//			pDstVec		: Local		SRAM
//			TempBuffer1		: Local		SRAM
//			TempBuffer2		: Global	SRAM
//
//			4666 clocks per 1024 int pairs with C++ call (2.28 clocks per 32bit word)
//
//		For the others configurations the following results were achieved: 
//
//
//	COMMENTS:
//		The order of intermediate data transmissions in function is:
//			pSrcVec[]		=> pTmpBuf1[]		    - 1/x Multiplying	(in-place is supported only if SrcReadStep=2)
//			pTmpBuf1[]	=> pTmpBuf2[]			- Normalization		(in-place is supported)
//			pTmpBuf2[]	=> pDstVec[]			- Sign Correction	(in-place is supported only if DstReadStep=2)
// 
//		Consider this sequence to use same buffer pointers and support in-place
//			Examples of some allowable calls:
//				Div32_By2Int(pSrcVec,pDstVec,64,QuantizerTable,3,pDstVec,pDstVec)
//				Div32_By2Int(pSrcVec,pSrcVec,64,QuantizerTable,3,pSrcVec,pSrcVec)
//
//		Note that the using same buffer pointers can reduce function performance.


global _nmppsDiv_By2Int__FPiPiPiiPvPvii_ :label;
global _void._.8.8nmppsDiv_By2Int_.1int._.0.9._int._.0.9._int._.0.9._int.9._void._.0.9._void._.0.9._int.9._int.2 :label;
<_nmppsDiv_By2Int__FPiPiPiiPvPvii_>
<_void._.8.8nmppsDiv_By2Int_.1int._.0.9._int._.0.9._int._.0.9._int.9._void._.0.9._void._.0.9._int.9._int.2>
 

.branch;

	ar5 = ar7-2;
	PUSH_REGS();

	ar0 = [--ar5];		//			nm32s*	pSrcVec,			
	ar6 = [--ar5];		//			nm32s*	pDstVec,			
	ar1 = [--ar5];		//			nm32s*	PairOfDivisors,	
	gr5 = [--ar5];		//			int		NumbersOfPairs,		
	ar2 = [--ar5];		//			void*	pTmpBuf1,			
	ar3 = [--ar5];		//			void*	pTmpBuf2,			
	gr0 = [--ar5];		//			int		SrcReadStep=2,	
	gr6 = [--ar5];		//			int		DstWriteStep=2,	
	ar5 = ar2;


	with gr7 = false;
	with gr7++;
	
	// sb,nb,f1cr Initialization
	ar4 = DivS4095byU145		with gr4=gr7<<31;	// gr4= 80000000h 
	nb1 = gr4				with gr7<<=1;		// gr7= 2
	sb  = gr7;									// sb = 2 
	
	// Lower Quntizer Loading 
	gr2 = [ar1++];
	ar2 = ar4 with gr2 <<= 2;
	rep 1 wfifo=[ar2+=gr2];
	
	// Hight Quntizer Loading 
	gr2 = [ar1++];
	ar2 = ar4 with gr2 <<= 2;
	gr2+= gr7;
	rep 1 wfifo=[ar2+=gr2],ftw;

	WTW_REG(gr4);
	
	///////////////////////////////////////////////////////////////
	// 1/x multiplication	
	// [pSrcVec] => [TmpBufeffer1]

	push ar5,gr5;	//  pTmpBuf1
	push ar6,gr6;
	
	delayed call vec_vsum_data_0;
	
	pop ar6,gr6;
	pop ar5,gr5;	// pTmpBuf1

	//////////////////////////////////////////////////////////////
	// Right shift scaling down
	// [pTmpBuf1] => [TmpBufeffer2]

	push ar3,gr3;	// pTmpBuf2
		
	gr0 = 19 with gr7 = gr5 << 1;
	//[tmp]=gr7;
	//CRC32_RRC(ar5,gr7,CRC);
	VEC_ARSH32_RRRR(ar5,ar3,gr7,gr0);				

	//gr7=[tmp];
	//CRC32_RRC(ar5,gr7,CRC);
	pop ar3,gr3;	// pTmpBuf2
	
	///////////////////////////////////////////////////////////////
	// Result Correction
	// [pTmpBuf2] => [pDstVec]
	push ar6,gr6;
	WTW_REG(gr4);
	with gr7 = gr5>> 5;
	if =0 delayed goto ResultCorrection_rep1 with gr7--;
		f1cr=gr4;
		nul;
	
	<NextResultCorrection_rep32>
		rep 32 data,ram = [ar3++]	with activate data;				
		rep 32					with ram - afifo;				
	if <>0 delayed goto NextResultCorrection_rep32 with gr7--;
		nul;
		rep 32 [ar6++gr6] = afifo;								

	<ResultCorrection_rep1>
	with gr7 = gr5<< 27;
	with gr7 >>=27;
	if =0 delayed goto EndResultCorrection with gr7--;
		nul;
		nul;

	<NextResultCorrection_rep1>
		rep 1 data,ram = [ar3++]	with activate data;				
		rep 1				with ram - afifo;				
	if <>0 delayed goto NextResultCorrection_rep1 with gr7--;
		nul;
		rep 1 [ar6++gr6] = afifo;								

		
	<EndResultCorrection>
	pop ar6,gr6;
	//gr7=[tmp];
	//CRC32_RRC(ar6,gr7,CRC);

	POP_REGS();
	return;
.wait;



end ".text_nmplv";
