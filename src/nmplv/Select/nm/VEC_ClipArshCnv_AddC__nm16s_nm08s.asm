//------------------------------------------------------------------------
//
//  $Workfile:: ClipRShiftConvertAdd_16s8s.asm    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file  ClipRShiftConvertAdd_16s8s.asm
//! \author Сергей Мушкаев
//! \brief  Функции преобразования елементов вектора.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vConvert.h"

extern vec_ClipMul2D2W8_AddVr:label;
import from macros.mlb;
extern tbl_f1cr_nm16:long;

data ".data_nmplv_L"


global	vec_tbl_sb_2x4rows:  long[8] = (
			0002000200020002hl, //(0,16)x4 - 4 Rows ONLY !!!
			000a000a000a000ahl, //(2,14)x4
			0022002200220022hl, //(4,12)x4
			0082008200820082hl, //(6,10)x4
			0202020202020202hl, //(8,8 )x4
			0802080208020802hl, //(10,6)x4
			2002200220022002hl, //(12,4)x4
			8002800280028002hl	//(14,2)x4
					   );




	LWRShiftConvert16to8:  long[8*2] = (
						0000000000000000hl,
						0000000000000001hl,
						0000000000000000hl,
						0000000000000100hl,
						0000000000000000hl,
						0000000000010000hl,
						0000000000000000hl,
						0000000001000000hl,
						0000000000000000hl,
						0000000100000000hl,
						0000000000000000hl,
						0000010000000000hl,
						0000000000000000hl,
						0001000000000000hl,
						0000000000000000hl,
						0100000000000000hl);


end ".data_nmplv_L";


data ".data_nmplv_G"
	GWRShiftConvert16to8:  long[8*2] = ( 
						0000000000000000hl,
						0000000000000001hl,
						0000000000000000hl,
						0000000000000100hl,
						0000000000000000hl,
						0000000000010000hl,
						0000000000000000hl,
						0000000001000000hl,
						0000000000000000hl,
						0000000100000000hl,
						0000000000000000hl,
						0000010000000000hl,
						0000000000000000hl,
						0001000000000000hl,
						0000000000000000hl,
						0100000000000000hl);

end ".data_nmplv_G";
begin ".text_nmplv"
    
    //--------------------------------------------------------------------
    //! \fn void nmppsClipRShiftConvertAddC_16s(nm16s* pSrcVec, int nClipFactor,int nShift, int8b nAddValue,nm8s* pDstVec, int nSize);
	//!
	//! \perfinclude _nmppsClipRShiftConvertAddC_16s.html
    //--------------------------------------------------------------------

global _nmppsClipRShiftConvertAddC_16s8s:label;
<_nmppsClipRShiftConvertAddC_16s8s>
.branch;
	ar5 = sp - 2	with gr7=false;
	push ar0,gr0	with gr7++;
	push ar1,gr1	with gr7++;		// gr7=2
	push ar4,gr4	with gr0=gr7;	// gr0=2
	push ar5,gr5	with gr1=gr7<<1;// gr1=4;
	push ar6,gr6	with gr6=gr7;	// gr6=2

	
	gr5 = [--ar5];					// pSrcVec
	gr0 = [--ar5];					// ClipFactor
	ar0 = tbl_f1cr_nm16 with gr0<<=1;
	f1cr= [ar0+=gr0];
	gr0 = [--ar5];					// Shift
	ar0 = vec_tbl_sb_2x4rows;
	sb  = [ar0+=gr0];
	gr4 = 80808080h;
	nb1 = gr4;
	gr0 = [--ar5];					// AddValue
	gr0<<=24;
	gr7 = gr0>>8;
	gr7 = gr7 or gr0;
	gr0 = gr7 >> 16;
	gr7 = gr0 or gr7;
	vr  = gr7;
	
	ar0 = gr5		with gr5;
	
	if < delayed goto LoadLocalMatrix;
		ar4 = LWRShiftConvert16to8;
	
	ar4 = GWRShiftConvert16to8;
	<LoadLocalMatrix>

	ar6 = [--ar5];					// pDstVec
	gr5 = [--ar5];					// nSize 
	delayed call vec_ClipMul2D2W8_AddVr	with gr5>>=3;
		gr0 = gr1 >> 1;
		ar1 = ar0+gr0 with gr0 = gr1;// gr0=4	

	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;



end ".text_nmplv";
