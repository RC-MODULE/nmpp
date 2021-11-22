//------------------------------------------------------------------------
//
//  $Workfile:: Math_AccMul1D1W32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_AccMul1D1W32.asm
//! \author Сергей Мушкаев
//! \brief  Функции векторного ядра.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"



begin ".text_nmvcore"


      

	//------------------------------------------------------------------------
    //! \fn void vec_AccMul1D1W32_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0,  nmreg ar4, nmreg03 gr4, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_AccMul1D1W32_AddVr:label;
      <vec_AccMul1D1W32_AddVr>
.branch;
	rep 32 wfifo=[ar4++],ftw,wtw;
	with gr7=gr5-1;
	if =0 delayed goto Single_AccMul_rep32 with gr7--;
		nul;
		nul;

	rep 32 wfifo=[ar4++];
	rep 32 data=[ar0++gr0],ftw,wtw with vsum ,data,vr;
	<Next_AccMul_rep32>
	if  <>0 delayed  goto Next_AccMul_rep32 with gr7--; 	
		rep 32 wfifo=[ar4++];
		rep 32 data =[ar0++gr0],ftw,wtw with vsum ,data,afifo;
		

	rep 32 [ar6++gr6]=afifo;
	return;
	
	<Single_AccMul_rep32>
	delayed return;
		rep 32 data =[ar0++gr0],ftw with vsum ,data,vr;
		rep 32 [ar6++gr6]=afifo;
		nul;

.wait;


end ".text_nmvcore";
