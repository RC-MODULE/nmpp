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
 
//! \fn int nmppsFirstNonZeroIndx_32s(int* pSrcVec, int nSize)
//!
//! \perfinclude nmppsFirstNonZeroIndx_32s.html 

global _nmppsFirstNonZeroIndx_32s:label;
<_nmppsFirstNonZeroIndx_32s>	
 
 	ar5=ar7-2;
 	push ar0,gr0 	with gr0=false;
 	push ar1,gr1	with gr0--;
 	push ar2,gr2	with gr0--;
 	ar0 = [--ar5]; 	// pSrcVec
 	gr7 = [--ar5];	// nSize
  	gr2 = [ar0++] 	with gr7+=gr0;
 	ar5 = gr7 	 	with -gr2;	
					with gr2 C>>=1;  // if gr2==0 carry=1
Loop:label;
	ar1 = Loop		with gr7 or not gr2;

	<Loop>
		gr2=[ar0++] with gr7-- noflags;
 	if >= delayed goto ar1 with -gr2	;	// if gr2==0 carry=1
 		with gr2 C>>=1;					// if gr2==0 gr2=80000000 else gr2=000000000 
		with gr7 or not gr2;			// if > ���� ����� ��� gr7=-1 ��� gr2!=0
 	
 	// gr7 = -2 ���� �������� ������ ��� ���� �� ���� � �����
 	// gr7+2 - �����c ���� ������������ ����� �������
 	// ar5 = - ������ ������������� �������� � �������
	gr1 = ar5		with gr7++;
	gr0 =[ar0+=gr0] with gr7 = gr1-gr7;
					with gr0 = -gr0;
	pop ar2,gr2 	with gr0 = gr0 C>>1;
  	pop ar1,gr1 	with gr0 A>>= 31;	// gr0=FFFFFFFF ���� gr0=0
  	pop ar0,gr0 	with gr7 = gr7 or gr0;
return;
end ".text_nmplv";
