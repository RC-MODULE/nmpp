//------------------------------------------------------------------------
//
//  $Workfile:: Mul_V32N32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Mul_V32N32.asm
//! \author Сергей Мушкаев
//! \brief  Функции поэлементного умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//import from macros.mlb;


begin ".text_nmplv"

.if .nm64revision == 5;


/////////////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsMul_AddC_64s (nm64s *pSrcVec1,nm64s *pSrcVec2, nm64s* pnAddVal, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude nmppsMul_AddC_64s.html

global _nmppsMul_AddC_64s:label;
<_nmppsMul_AddC_64s>
 
.branch;


	ar5 = sp-2;
	push ar0,gr0 with gr7 = false;
	push ar1,gr1;
	push ar2,gr2;
	push ar6,gr6;
	
	nb1 = gr7;
	sb  = gr7;

	ar0 = [--ar5];			// pSrcVec1
	ar1 = [--ar5];			// pSrcVec2
	ar2 = [--ar5];			// pAddN
	ar6 = [--ar5]; 			// pDstVec
	gr7 = [--ar5];			// size
	vr	= [ar2] with gr7--;
	NextMul:label;
	ar2 = NextMul set;
	<NextMul>
	if <>0  delayed goto ar2 with gr7--;
		rep 1 wfifo=[ar1++],ftw,wtw;
		rep 1 data=[ar0++] with vsum ,data,vr;
		rep 1 [ar6++]=afifo;

	
	//-----------------------------------------
	
	
	pop ar6,gr6;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

.endif;
end ".text_nmplv";

