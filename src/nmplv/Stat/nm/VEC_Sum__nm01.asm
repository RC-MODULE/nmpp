//------------------------------------------------------------------------
//
//  $Workfile:: Sum.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   Sum.Asm
//! \author ������ �������
//! \brief  �������������� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"

extern _nmppsTmpBuffer16_G_:long;
extern _VEC_TBL_One_G:long;
data ".data_nmplv_G"
//	GTmpLong:long;
//	GTmpLong2:long[2];
	GData_55:	long = 05555555555555555hl;
	GData_AA:	long = 0aaaaaaaaaaaaaaaahl;
//	pSrcVec:word;
//	pTmpBuf:word;
end ".data_nmplv_G";

const GTmpLong =_nmppsTmpBuffer16_G_;
const GTmpLong2=_nmppsTmpBuffer16_G_+2;
const pSrcVec  =_nmppsTmpBuffer16_G_+6;
const pTmpBuf  =_nmppsTmpBuffer16_G_+8;

extern vec_vsum_data_afifo:label;
extern vec_vsum_shift_data_afifo:label;
extern vec_data_add_afifo:label;
extern vec_data_and_ram:label;
begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSum_1(nm1* pSrcVec, int nSize, int32b* pnRes, void* pTmpBuf);
//!
//! \perfinclude nmppsSum_1.html

global _nmppsSum_1:label;
<_nmppsSum_1>
.branch;
	ar5 = sp - 2;
	push ar0,gr0 with gr0=false;
	nb1 = gr0;
	sb  = 0aaaaaaaah;
	ar0 = _VEC_TBL_One_G;
	rep 32 wfifo=[ar0],ftw;
	
	push ar1,gr1;		 
	push ar5,gr5  with gr0++;		
	push ar6,gr6  with gr0++;		// gr0=2 
	ar0 = [--ar5] with gr6=gr0;		// pSrcVec
	gr5 = [--ar5];					// nSize in bits
	gr7 = [--ar5];				// *pnRes
	ar6 = [--ar5];					// pTmpBuf
	ar5 = gr7 with			// ar5 may be used!!!! 
	gr5>>=6;						// nSize in 64-bit elements
	[pSrcVec]=ar0;
	[pTmpBuf]=ar6;

	wtw;
	delayed call vec_data_and_ram;
		ar1 = GData_55;
	
	ar0 = [pTmpBuf];
	delayed call vec_vsum_data_afifo;
		ar6 = GTmpLong2;
	
	ar0 = [pSrcVec];
	ar6 = [pTmpBuf];
	delayed call vec_data_and_ram;
		ar1 = GData_AA;
	
	ar0 = [pTmpBuf];
	delayed call vec_vsum_shift_data_afifo;
		ar6 = GTmpLong2+2;
	

	ar0 = GTmpLong2;
	ar6 = GTmpLong;

	rep 1 data=[ar0++] with data;
	rep 1 data=[ar0++] with data+afifo;
	rep 1 [ar6]=afifo;

	gr7=[ar6];
	[ar5]=gr7;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;




end ".text_nmplv";
