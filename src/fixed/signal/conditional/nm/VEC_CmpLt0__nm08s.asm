//------------------------------------------------------------------------
//
//  $Workfile:: Activate.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   Activate.asm
//! \author ������ �������
//! \brief  ��������� ������� ��� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------
    
data ".data_nmplv_L"
	chla:	long = 8080808080808080hl;
end ".data_nmplv_L";

extern vec_activate_data:label;
begin ".text_nmplv"

///////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsCmpLt0_8s(nm8s* pSrcVec, nm8s* pDstVec, int nSize);
//!
//! \perfinclude _nmppsCmpLt0_8s.html

global _nmppsCmpLt0_8s:	label;
<_nmppsCmpLt0_8s>
	ar5 = ar7 - 2	with gr7 = false;
	push ar0,gr0	with gr7++;
	push ar5,gr5	with gr7++;
	push ar6,gr6;
	ar0 = [--ar5]	with gr0 = gr7;	// pSrcVec,		
	ar6 = [--ar5]	with gr6 = gr7;	// pDstVec,		
	gr5 = [--ar5];					// nSize		
	f1cr = [chla]				with gr7++;
	call vec_activate_data	with gr5>>=3;
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
