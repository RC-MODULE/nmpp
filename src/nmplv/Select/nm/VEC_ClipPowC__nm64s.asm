//------------------------------------------------------------------------
//
//  $Workfile:: Clip.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2011/11/22 13:50:09 $
//
//! \if file_doc
//!
//! \file   Clip.asm
//! \author Сергей Мушкаев
//! \brief  Функции насышения с ограниченным множеством возможных порогов
//!         для различных типов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vClip.h"

extern vec_activate_data_add_0:label;
extern tbl_f1cr_nm64:long[64];

begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////


//! \fn void nmppsClipPowC_64s(nm64s *pSrcVec, int nClipFactor, nm64s *pDstVec, int nSize) 
//!
//! \perfinclude _nmppsClipPowC_32s.html

global _nmppsClipPowC_64s:label;
<_nmppsClipPowC_64s>
.branch;

	ar5=ar7-2;
	push ar0,gr0	with gr7=false;
	push ar5,gr5	with gr7++;
	push ar6,gr6	with gr7++;
	
	ar0 = [--ar5] with gr0=gr7;				//Src	
	gr6 = [--ar5];							//ClipIndex
	ar6 = tbl_f1cr_nm64	with gr6<<=1;		
	f1cr= [ar6+=gr6];
	delayed call vec_activate_data_add_0;
		ar6 = [--ar5] with gr6=gr7;			//Dst
		gr5 = [--ar5];						//Size
		

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar0,gr0;

	return;
.wait;



end ".text_nmplv";

