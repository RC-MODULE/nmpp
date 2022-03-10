//------------------------------------------------------------------------
//
//  $Workfile:: Sub.as $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file Sub.Asm
//! \author ������ ������� 
//! \brief ��������� ������� � ��������� �� �������.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_Sub:label;

begin ".text_nmplv"




/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSub (nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsSub_16s.html

global _nmppsSub_16s:label;
<_nmppsSub_16s>
.branch;
	ar5 = sp - 2 with gr7=false;
	push ar0,gr0 with gr7++;
	push ar1,gr1 with gr0=gr7+1;	// gr0=2
	push ar5,gr5 with gr1=gr0;		// gr1=2 
	push ar6,gr6 with gr6=gr0;		// gr6=2
	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 16-bit elements
	
	nb1 = 80008000h with gr5>>=2;	// nSize in 64-bit words
	delayed call vec_Sub;
		nul;
		wtw;						

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;



end ".text_nmplv";
