//------------------------------------------------------------------------
//
//  $Workfile:: Find_First_Zero_Fwd.asm             $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   Find_First_Zero_Fwd.asm
//! \author S. Mushkaev
//! \brief  <������� ��������>
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

//! \fn int nmppsFirstZeroIndx_32s(int* pSrcVec, int nSize)
//!
//! \perfinclude _nmppsFirstZeroIndx_32s.html 

global _nmppsFirstZeroIndx_32s:label;
<_nmppsFirstZeroIndx_32s>	
 
 	ar5=ar7-2;
 	push ar0,gr0 	with gr0=false;
 	push ar1,gr1	with gr0--;
 	push ar2,gr2	with gr0--;
 	ar0 = [--ar5]; 	// pSrcVec
 	gr7 = [--ar5];	// nSize
  	gr2 = [ar0++] 	with gr7+=gr0;
 	ar5 = gr7 	 	with gr2;
 	
 	<Loop>
 	if <>0 delayed goto Loop with gr7--;
 		gr2=[ar0++] with gr1=gr7 A>>31;
 		with gr2 and not gr1;
 	
 	// gr7 = -2 ���� �������� ������ ��� ���� ���� � �����
 	// gr7+2 - �����c ���� ������������ ����� �������
 	// ar5 = - ������ ������������� �������� � �������
	gr1 = ar5		with gr7++;
	gr0 =[ar0+=gr0] with gr7 = gr1-gr7;
					with gr0 = -gr0;
	pop ar2,gr2 	with gr0 = gr0 C>>1;
  	pop ar1,gr1 	with gr0 A>>= 31;
  	pop ar0,gr0 	with gr7 = gr7 or not gr0;
return;
end ".text_nmplv";
