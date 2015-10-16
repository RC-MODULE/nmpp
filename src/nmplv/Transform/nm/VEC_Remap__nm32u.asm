//------------------------------------------------------------------------
//
//  $Workfile:: Remap32.asm   $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   Remap32.asm
//! \author Сергей Мушкаев
//! \brief  Функции перетаскивания по таблице для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
// #include "vDiv.h"



import from macros.mlb;

data ".data_nmplv_L"
end ".data_nmplv_L";

data ".data_nmplv_G"
end  ".data_nmplv_G";




begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_Remap(nm32u* pSrcVec, nm32u* pDstVec, nm32s* pRemapTable, int nSize);
//!
//! \perfinclude _VEC_Remap__FPUiPUiPii.html

global _VEC_Remap__FPUiPUiPii:label;
global _void._.8.8VEC_Remap.1unsigned._int._.0.9._unsigned._int._.0.9._int._.0.9._int.2 :label;
<_VEC_Remap__FPUiPUiPii>
<_void._.8.8VEC_Remap.1unsigned._int._.0.9._unsigned._int._.0.9._int._.0.9._int.2>
.branch;
    ar5 = ar7 - 2;
    PUSH_REGS();

	gr4 = [--ar5];	//	nm32u*	pSrcVec,		
	ar6 = [--ar5];	//	nm32u*	pDstVec,
	ar1 = [--ar5];	//	nm32s*			RemapTable
	gr7 = [--ar5];	//	int				nSize,

	gr7 >>=1;
	with gr3 = gr4;	//	src_base
	next_Permutation:label;
	gr5=next_Permutation with gr7--;

	<next_Permutation>
		ar4 = [ar1++];		// src_disp1  =RemapTable[i]	
		ar3 = [ar1++];		// src_disp2  =RemapTable[i+1]
		gr1 = [ar4+=gr4];	// src_val1   =pSrcVec[src_base+src_disp1]
		gr5 = [ar3+=gr3];	// src_val2   =pSrcVec[src_base+src_disp2]
    if > delayed goto next_Permutation with gr7--;
		[ar6++] = gr1;		// pDstVec[i]  =src_val1
		[ar6++] = gr5;		// pDstVec[i+1]=src_val2


    POP_REGS();
    return;
.wait;


end ".text_nmplv";
