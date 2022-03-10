//------------------------------------------------------------------------
//
//  $Workfile:: Or.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
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
   

extern vec_Or3V:label;

begin ".text_nmplv"
///////////////////////////////////////////////////////////
//! \fn void nmppsOr_64u(nm64u* pSrcVec1, nm64u* pSrcVec2, nm64u* pSrcVec3, nm64u* pSrcVec4, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsOr_64u.html

global _nmppsOr3V_64u:label;
<_nmppsOr3V_64u>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;
	push ar2,gr2	;
	push ar3,gr3	with gr0=gr7;
	push ar4,gr4	with gr1=gr7;
	push ar5,gr5	with gr2=gr7;
	push ar6,gr6	with gr3=gr7;

	ar0 = [--ar5];		//	nm64*		pSrcVec1,	// Input Buffer					:long Local[nSize]
	ar1 = [--ar5];		//	nm64*		pSrcVec2,	// Input Buffer					:long Local[nSize]
	ar2 = [--ar5];		//	nm64*		pSrcVec3,	// Input Buffer					:long Local[nSize]
	delayed call vec_Or3V with gr6=gr7;
		ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";