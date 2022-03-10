//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinV_8s.asm             $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   CompareMinV_8s.asm
//! \author S. Mushkaev
//! \brief  Elementwise min comparision
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmplv"

extern vec_CompareMinNV:label;
/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMinNV_8s(nm8s7b**  pSrcVec1, nm8s7b* pSrcVec2, int numVecs, nm8s7b*  pDstMin, int nSize);
//!
//! \perfinclude _nmppsMinEvery_8s.html

global _void._.8.8nmppsMinNV_.1char._.0.0.9._int.9._char._.0.9._int.2 :label;
<_void._.8.8nmppsMinNV_.1char._.0.0.9._int.9._char._.0.9._int.2>
.branch;
	ar5=sp-2;
	push ar0,gr0	with gr0=false;
	push ar1,gr1	with gr0++;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5	with gr0++;
	push ar6,gr6	with gr1=gr0;

	ar6 = [--ar5] with gr6=gr0;		    // pSrcVec1
	gr4 = [--ar5];						// numVecs
	
								
	ar0=ar7 with gr7=gr4>>1;			// �������� ������ pSrcVec1 � ����, ������ ��� �� ��� ������

	<CopyPtr>
	if > delayed goto CopyPtr with gr7--;
		ar2,gr2=[ar6++];
		push ar2,gr2;
	
	
	ar6 = [--ar5];						// pDstMin
	gr5 = [--ar5];						// nSize
	ar5 = ar7;							// fast 64-bit buffer 
	ar7 +=2;
	
	push ar0,gr0;						// save sp=ar0
	
	nb1 =80808080h with gr5>>=3;
	f1cr=80808080h;
	delayed call vec_CompareMinNV;
		wtw;
		ar3 = ar1 with gr3 = gr1;
		
	//ar7-=2;
	pop ar0,gr0;
	ar7=ar0;
	

		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmplv";
