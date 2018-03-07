//------------------------------------------------------------------------
//
//  $Workfile:: Crc32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file Crc32.asm
//! \author Сергей Мушкаев
//! \brief Подсчет избыточного кода
//! 
//! \endif
//!
//------------------------------------------------------------------------

import from rtmacro.mlb;

extern _CRC32_Table: word ;
begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////////////////////

//! \fn unsigned _nmppsCrcAcc_32f(float* pSrcVec, int numBitsToClear, int nSize, unsigned int& nCrc);
//!
//! \perfinclude _nmppsCrcAcc_32f.html

global _nmppsCrcAcc_32f :label;
<_nmppsCrcAcc_32f>
 

.branch;

	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];//	nm32u*	Vec,	// Input Vector			:long Any[Size/2]
	ar1 = [--ar5];// 	numBitsToClear
	gr5 = [--ar5];//	int		nSize,	// Vector size        	:[0,1,2...]	
	ar6 = [--ar5];//	unsigned int&	Crc32	// Init/Output crc	
	
	
	gr1 = ar1;
	gr2 = -1;
	LSHIFT32 ( gr7, gr2, gr1); // mask
	ar2 = gr7;
	
	gr2 = 1;	//1
	ar1=0 with gr1--;
	if < goto skipRounder;
	LSHIFT32 ( gr7, gr2, gr1);	//rounder
	ar1 = gr7;
	
	<skipRounder>
	
	gr7 = [ar6]	with gr5;
	if =0 delayed goto End_CRC32;
		gr2 = 000000FFh;
	ar5 = _CRC32_Table;
	gr0=[ar0++];									//		a=pSrcVec[i++];
	gr1 = ar1;
	gr1 = ar2 with gr0+= gr1;
	gr0 = gr0 and gr1;
	
	ar4 = ar5;
	<Next_CRC32>	
		// checking zero and reset sign bit
		//gr7 = gr0 << 1;
		//gr7--;
		//gr7 = gr0 xor gr7;
		//gr7 A>>=31;
		//gr7--;
		//gr7 R>>=1;
		//gr0 = gr0 and gr7;
		
		gr1 = gr0 and gr2;							//		b = a & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4 = gr1 xor gr3;							//		addr=b^c;			
		gr6 = [ar4+=gr4]	with gr7>>=8; 			//		t=pTable[addr];	CRC32 >>=8; 		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 8;								//		b = a >> 8;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;					
		gr6 = [ar4+=gr4]	with gr7>>=8;			//		t=pTable[addr];	CRC32 >>=8;	
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 16;							//		b = a >> 16;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	with gr7>>= 8;			//		t=pTable[addr];	CRC32 >>= 8 ;		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^ t;		
		gr1 = gr0 >> 24;							//		b = a >> 24;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	;				//		t=pTable[addr];		
		ar4 = ar5;			
		gr0	=[ar0++] 		with gr7>>= 8;		
		gr1 = ar1			with gr5--;			
if <>0 delayed goto Next_CRC32 with gr7 = gr7 xor gr6;	//		i++			//		CRC32 >>= 8 			
		gr1 = ar2 with gr0 = gr0 + gr1	;				
		gr0 = gr0 and gr1	;						//		a=pSrcVec[i++];CRC32 = CRC32 ^ t;
	
	
	<End_CRC32>	
	gr7 = not gr7;									//	CRC32 = ~ CRC32;
	[ar6] = gr7;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
return;



end ".text_nmplv";
