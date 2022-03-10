//------------------------------------------------------------------------
//
//  $Workfile:: CompareMin.asm     $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_CompareMin.asm
//! \author S. Mushkaev
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"



    //------------------------------------------------------------------------
    //! \fn void vec_CompareMinNV(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr3, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6);
    //!
    //------------------------------------------------------------------------

global vec_CompareMinNV :label;
<vec_CompareMinNV>
.wait;
	push ar2,gr2 with gr2=gr5<<27 ;	
	push ar5,gr5 with gr5>>=5;
	with gr2>>=27;				// gr2- ����� ������
	gr4--;
	gr4--;
	ar4=gr4;					// const ar4-��������� ���� ������� ��������
	gr1=gr0;
	gr3=gr0;
	gr0=ar0;					// const gr0-������ �������

	<next_CompareMin_rep32>
		ar0=gr0;				// �������������� ��������� �� ������� ����������
		ar1=[ar0];				// ������ ���������� �� ������ ������
		rep 32 ram=[ar1++gr1];	// ������ ������ ������
		[ar0++]=ar1;			// ��������� ����� �������� 
		gr4=ar4;				// ��������������� ���� �������� ��������
		
		<nextArray>
			ar1=[ar0];			// ����� ��������� ���������
			ar3=ar1 with gr4--; // ��������� ������� ��������
			rep 32 data=[ar1++gr1]	with ram-data;
			[ar0++]=ar1;		// ��������� ����� �������� 
			rep 32					with activate afifo;
		if <>0 delayed goto nextArray;		
			rep 32 data=[ar3++gr3]	with mask afifo,ram,data;			
			rep 32 [ar5],ram= afifo;
		
		ar1=[ar0];
		ar3=ar1 with gr5--;
		rep 32 data=[ar1++gr1]	with ram-data;
		rep 32					with activate afifo;
		[ar0++]=ar1;
	if <>0 delayed  goto next_CompareMin_rep32;
		rep 32 data=[ar3++gr3]	with mask afifo,ram,data;			
		rep 32 [ar6++gr6]= afifo;

	pop ar5,gr5;
	pop ar2,gr2;
return;	
.wait;




end ".text_nmvcore";
