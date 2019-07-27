//------------------------------------------------------------------------
//
//  $Workfile:: ResampleDown2_S15.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:08 $
//
//! \if file_doc
//!
//! \file   ResampleDown2_S15.asm
//! \author ������ �������
//! \brief  ������� ��������� �������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vResize.h"

import from macros.mlb;

data ".data_nmpls_G"
	Mask:	long = 0fffefffefffefffeh;
end ".data_nmpls_G";
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
macro MTR_AVG_REP(nVal)
		rep nVal ram = [ar3];
		rep nVal data=[ar0++gr0],ftw with vsum ,data,0;
		WTW_REG_DEPRICARTED(gr4);
 		rep nVal data=[ar1++gr1]	  with vsum ,data,afifo;
		rep nVal with mask ram,shift afifo,0;
		WTW_REG_DEPRICARTED(gr4);
		rep nVal [ar6++gr6]=afifo;	
			nul;
			nul;
			nul;
		delayed goto exit; 
			nul;
			nul;
end MTR_AVG_REP;
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
begin ".text_nmpls"
/////////////////////////////////////////////////////////////////////////////////////////

extern vec_MUL_2V4toW8_shift:label;

//! \fn void nmppsResampleDown2(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSrcVecSize, nm64s* pKernel);
//!
// \perfinclude _nmppsResampleDown2__FPUsPUsiPl.html


global _nmppsResampleDown2_16u16u:label;
<_nmppsResampleDown2_16u16u>
.branch;
					
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	ar0 = [--ar5];					// pSrc
	ar6 = [--ar5];					// pDst
	gr5 = [--ar5];					// len

	gr4 = 80008000h;
	sb  = 00020002h;
	nb1 = gr4;

	ar1 = ar0+gr0;
	
	ar5 = [--ar5] with gr5>>=3; //128bit word count
	ar3 = Mask with gr0 = gr1;// gr0=4	

//////////////////////////////////////////////////////////////
	call vec_MUL_2V4toW8_shift;
//////////////////////////////////////////////////////////////

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;

.wait;
end ".text_nmpls";
 