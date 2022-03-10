//------------------------------------------------------------------------
//
//  $Workfile:: Not.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Not.asm
//! \author ������ �������
//! \brief  ���������� ������� ��� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_not_data:label;
begin ".text_nmplv"
///////////////////////////////////////////////////////////
//! \fn void nmppsNot_8u(nm64u* pSrcVec, nm64u* pDstVec, int nSize);
//!
//! \perfinclude _nmppsNot_8u.html

global _nmppsNot_8u:label;
<_nmppsNot_8u>
	ar5 = ar7 - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar5,gr5	with gr0=gr7+1;
	push ar6,gr6;

	ar0 = [--ar5];		//	nm64*		pSrcVec,		// Input Buffer					:long Local[nSize]
	ar6 = [--ar5];	//	nm64*		pDstVec,		// Output Buffer				:long Global[nSize
	delayed call vec_not_data with gr6=gr0;
		gr5>>=3;
		gr5 = [--ar5];	//	int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;
end ".text_nmplv";
