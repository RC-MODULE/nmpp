//------------------------------------------------------------------------
//
//  $Workfile:: Sub.as $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:04 $
//
//! \if file_doc
//!
//! \file Sub.Asm
//! \author Сергей Мушкаев 
//! \brief Вычитание вектора и константы из вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------


extern vec_Sub:label;

begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsSub (nm64s *pSrcVec1, nm64s *pSrcVec2, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsSub_64s.html

global _nmppsSub_64s:label;
global _nmppsSub64s:label;
<_nmppsSub_64s>
<_nmppsSub64s>
.branch;
	ar5 = sp - 2 with gr7=false;
	nb1 = gr7;			
	push ar0,gr0 with gr7++;
	push ar1,gr1 with gr0=gr7+1;	// gr0=2
	push ar5,gr5 with gr1=gr0;		// gr1=2 
	push ar6,gr6 with gr6=gr0;		// gr6=2

	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 64-bit elements
	
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
