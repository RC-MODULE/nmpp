//------------------------------------------------------------------------
//
//  $Workfile:: MultipleAdd8.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   MultipleAdd8.Asm
//! \author ������ �������
//! \brief  ������� ��������� � ����������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"

data ".data_nmplv_G"
	WeightsMultipeAdd:long[16]=(
				0000000000000001hl,
				0000000000010000hl,
				0000000100000000hl,
				0001000000000000hl,
				0000000000000000hl dup 8,
				0000000000000001hl,
				0000000000010000hl,
				0000000100000000hl,
				0001000000000000hl
					  );

end ".data_nmplv_G";

import from macros.mlb;

begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void nmppsSumN_8s16s (nm8s **ppSrcVec, nm16s *pDstVec, int nSize, int nNumberOfVectors) 
//!
//! \perfinclude _nmppsSumN_8s16s.html

global _nmppsSumN_8s16s:label;
<_nmppsSumN_8s16s>

.branch;
	ar5 = sp - 2;

	
	PUSH_REGS();
	gr0 = [--ar5];	// Buffers
	ar6 = [--ar5];	// DstBuffer
	gr4 = [--ar5];	// SizeOfBuffers
	gr5 = [--ar5];	// NumbersOfBuffers
	
	nb1 = 80008000h with gr4>>=3;	// nSize in 64-bit longs
	sb  = 02020202h;
	ar4 = WeightsMultipeAdd;
	rep 16 wfifo=[ar4++],ftw;
	wtw;
    
	gr4>>=5;
	gr5--;
	gr6 = 4;
	gr1 = 0;
	gr2 = 64;
	push ar6,gr6;
	push ar4,gr4;
	<Next_SelectBlock0123_rep32>
		ar0 = gr0;
		gr7 = gr5-1;
		ar1 =[ar0++];
		nul;
		ar1 +=gr1;
		rep 32 data=[ar1++] with vsum ,data,0;			// Buffer[0] 
		<Next_BufferAdd0123_rep32>
			ar1=[ar0++];								// ar1=Buffer[i]
			nul;
		if <>0 delayed  goto Next_BufferAdd0123_rep32 with gr7--; 
			ar1+=gr1;									// ar1=Buffer[i]+i*32*2;
			rep 32 data=[ar1++] with vsum ,data,afifo;	// +=Buffer[i]
		
		rep 32 [ar6++gr6]=afifo;
	
		gr1+=gr2;
		with gr4--;										// Buffer nSize in rep32
	if<>0 delayed goto Next_SelectBlock0123_rep32;
		nul;
		nul;

	ftw;
	wtw;
	
	pop ar4,gr4;
	pop ar6,gr6;
	nul;
	ar6+=2;
	gr1=0;
	<Next_SelectBlock4567_rep32>
		ar0=gr0;
		gr7 = gr5-1;
		ar1 =[ar0++];
		nul;
		ar1 +=gr1;
		rep 32 data=[ar1++] with vsum ,data,0;			// Buffer[0] 
		<Next_BufferAdd4567_rep32>
			ar1=[ar0++];								// ar1=Buffer[i]
			nul;
		if <>0 delayed  goto Next_BufferAdd4567_rep32 with gr7--; 
			ar1+=gr1;									// ar1=Buffer[i]+i*32*2;
			rep 32 data=[ar1++] with vsum ,data,afifo;	// +=Buffer[i]
		
		rep 32 [ar6++gr6]=afifo;
	
		gr1+=gr2;
		with gr4--;										// Buffer nSize in rep32
	if<>0 delayed goto Next_SelectBlock4567_rep32;
		nul;
		nul;

	
	<Finish>
	
	POP_REGS();
	return with gr7=false;
.wait;
end ".text_nmplv";
