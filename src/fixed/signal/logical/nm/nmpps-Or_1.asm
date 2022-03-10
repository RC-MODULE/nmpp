//------------------------------------------------------------------------
//
//  $Workfile:: Or.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file   Or.asm
//! \author ������ �������
//! \brief  ���������� ������� ��� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_Or:label;
begin ".text_nmplv"

///////////////////////////////////////////////////////////

//! \fn void nmppsOr_1(nm1* pSrcVec1, nm1* pSrcVec2, nm1* pDstVec, int nSize);
//!
//! \perfinclude _nmppsOr_1.html


global _nmppsOr_1:label;
<_nmppsOr_1>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar5,gr5	with gr0=gr7;
	push ar6,gr6	with gr1=gr7;

	ar0 = [--ar5];		//	nm1*		pSrcVec1,	// Input Buffer					:long Local[nSize]
	ar1 = [--ar5];		//	nm1*		pSrcVec2,	// Input Buffer					:long Local[nSize]
	ar6 = [--ar5];		//	nm1*		pDstVec,	// Output Buffer				:long Global[nSize
	delayed call vec_Or with gr6=gr7;
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
		gr5>>=6;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplv";
