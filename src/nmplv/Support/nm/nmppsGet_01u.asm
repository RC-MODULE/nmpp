//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   CharShortAccess.asm
//! \author ������ �������
//! \brief  ������� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

begin ".text_nmplv"

//! \fn uint1 nmppsGet_1 (nm1 *pVec, int nIndex) 
//!
//! \perfinclude _nmppsGet_1.html

macro EXTRACT(n)
	delayed return with	gr7<<=n;
		gr7 >>=31;
		nul;
		nul;
end EXTRACT;

global _nmppsGet_1:label;
<_nmppsGet_1>

.branch;
	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5];	// pVec				
	gr7 = [--ar5];	// nIndex				
	gr0 = gr7>>5;
	gr7 = [ar0+=gr0] with gr0=gr7<<27;
	with gr0>>=25;
	gr0++;
	gr0++;
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;
	EXTRACT(31);
	EXTRACT(30);
	EXTRACT(29);	
	EXTRACT(28);
	EXTRACT(27);	
	EXTRACT(26);
	EXTRACT(25);	
	EXTRACT(24);
	EXTRACT(23);	
	EXTRACT(22);
	EXTRACT(21);	
	EXTRACT(20);
	EXTRACT(19);	
	EXTRACT(18);
	EXTRACT(17);	
	EXTRACT(16);
	EXTRACT(15);	
	EXTRACT(14);
	EXTRACT(13);	
	EXTRACT(12);
	EXTRACT(11);
	EXTRACT(10);	
	EXTRACT(9);	
	EXTRACT(8);	
	EXTRACT(7);	
	EXTRACT(6);
	EXTRACT(5);	
	EXTRACT(4);
	EXTRACT(3);	
	EXTRACT(2);
	EXTRACT(1);	
	delayed return with	gr7;
		gr7 >>=31;
		nul;
		nul;	
	
.wait;




end ".text_nmplv";
