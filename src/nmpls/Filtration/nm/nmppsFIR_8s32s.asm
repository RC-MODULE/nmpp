//------------------------------------------------------------------------
//
//  $Workfile:: Filter32to32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/01/26 13:23:47 $
//
//! \if file_doc
//!
//! \file   Filter16to32.asm
//! \author S. Mushkaev
//! \brief  Функии фильтрации для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//import from macros.mlb;

data ".data_nmpls_L"
mul01,mul02,mul0N:label;
mul11,mul12,mul1N:label;
mul21,mul22,mul2N:label;
mul31,mul32,mul3N:label;

	addrmul0: word[4]=(0,mul01,mul02,mul0N );
	addrmul1: word[4]=(0,mul11,mul12,mul1N);
	addrmul2: word[4]=(0,mul21,mul22,mul2N);
	addrmul3: word[4]=(0,mul31,mul32,mul3N);
	disp:word;
end ".data_nmpls_L";

begin ".text_nmpls"

    //--------------------------------------------------------------------
    //! \fn void nmppsFIR_8s32s(nm8s* pSrcVec, nm32s* pDstVec, int nSize, nm64s* pKernel)
	//!
	// \perfinclude nmppsFIR_8s32s.html
    //--------------------------------------------------------------------
extern vec_ClipMulNDNW8_AddVr:label;
extern vec_Mul2D2W8_AddVr:label;
extern vec_vsum_data_vr:label;

global _nmppsFIR_8s32s:label;
<_nmppsFIR_8s32s>
.branch;
	ar5 = sp - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	
    
	ar0 = [--ar5];	// pSrcVec
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize
	ar5 = [--ar5] with	// pKernel
	gr5 >>=3;

	sb	= 02020202h;
	gr4 = 80000000h;
	nb1 = gr4;
	f1cr= 0;
	vr  = 0;
	gr6 = 8;
	ar4=ar5+12;
	//[disp]=ar4;
	//========== mul 0 ==========
	push ar0,gr0;
	push ar6,gr6;
	gr1 = [ar5++];					// Number of arrays
	with gr7=gr1>>2;
	if > delayed goto lab0;
		ar1=mul0N;
	ar1 = addrmul0;
	ar1 = [ar1+=gr1];
	<lab0>
	delayed goto ar1;
		ar1 = [ar5++];				// Displacement to ar0
		ar4 = [ar5++];				// Pointer to weight array 
	
	<mul01>
	rep 8 wfifo=[ar4++],ftw;
	nul;
	gr0 = [ar1];
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_vsum_data_vr;
		wtw;
		nul;
	delayed goto finish0;
		pop ar6,gr6;
		pop ar0,gr0;

	<mul02>
	gr0 = [ar1];
	nul;
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_Mul2D2W8_AddVr;
		ar1=ar0+gr0 with gr1=gr0;		
		nul;

	delayed goto finish0;
		pop ar6,gr6;
		pop ar0,gr0;
	
	<mul0N>
	delayed call vec_ClipMulNDNW8_AddVr;
		gr0=2;
		
	pop ar6,gr6;
	pop ar0,gr0;
	<finish0>
	//=========== mul 1 ====================
	nul;
	ar6+=2;
	push ar0,gr0;
	push ar6,gr6;
	gr1 = [ar5++];					// Number of arrays
	with gr7=gr1>>2;
	if > delayed goto lab1;
		ar1=mul1N;
	ar1 = addrmul1;
	ar1 = [ar1+=gr1];
	<lab1>
	delayed goto ar1;
		ar1 = [ar5++];				// Displacement to ar0
		ar4 = [ar5++];				// Pointer to weight array 
	
	<mul11>
	rep 8 wfifo=[ar4++],ftw;
	gr0 = [ar1];
	nul;
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_vsum_data_vr;
		wtw;//WTW_REG_DEPRICARTED(gr4);
		nul;
	delayed goto finish1;
		pop ar6,gr6;
		pop ar0,gr0;

	<mul12>
	gr0 = [ar1];
	nul;
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_Mul2D2W8_AddVr;
		ar1=ar0+gr0 with gr1=gr0;		
		nul;

	delayed goto finish1;
		pop ar6,gr6;
		pop ar0,gr0;
	
	<mul1N>
	delayed call vec_ClipMulNDNW8_AddVr;
		gr0=2;
		
	pop ar6,gr6;
	pop ar0,gr0;
	<finish1>
	//=========== mul 2 ====================
	nul;
	ar6+= 2;
	push ar0,gr0;
	push ar6,gr6;
	gr1 = [ar5++];					// Number of arrays
	with gr7=gr1>>2;
	if > delayed goto lab2;
		ar1=mul2N;
	ar1 = addrmul2;
	ar1 = [ar1+=gr1];
	<lab2>
	delayed goto ar1;
		ar1 = [ar5++];				// Displacement to ar0
		ar4 = [ar5++];				// Pointer to weight array 
	
	<mul21>
	rep 8 wfifo=[ar4++],ftw;
	gr0 = [ar1];
	nul;
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_vsum_data_vr;
		wtw;//WTW_REG_DEPRICARTED(gr4);
		nul;
	delayed goto finish2;
		pop ar6,gr6;
		pop ar0,gr0;

	<mul22>
	gr0 = [ar1];
	nul;
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_Mul2D2W8_AddVr;
		ar1=ar0+gr0 with gr1=gr0;		
		nul;

	delayed goto finish2;
		pop ar6,gr6;
		pop ar0,gr0;
	
	<mul2N>
	delayed call vec_ClipMulNDNW8_AddVr;
		gr0=2;
		
	pop ar6,gr6;
	pop ar0,gr0;

	<finish2>
	//=========== mul 3 ====================
	ar6+=2;
	push ar0,gr0;
	push ar6,gr6;
	gr1 = [ar5++];					// Number of arrays
	with gr7=gr1>>2;
	if > delayed goto lab3;
		ar1=mul3N;
	ar1 = addrmul3;
	ar1 = [ar1+=gr1];
	<lab3>
	delayed goto ar1;
		ar1 = [ar5++];				// Displacement to ar0
		ar4 = [ar5++];				// Pointer to weight array 
	
	<mul31>
	rep 8 wfifo=[ar4++],ftw;
	gr0 = [ar1];
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_vsum_data_vr;
		wtw;//WTW_REG_DEPRICARTED(gr4);
		nul;
	delayed goto finish3;
		pop ar6,gr6;
		pop ar0,gr0;

	<mul32>
	gr0 = [ar1];
	ar0+= gr0;
	gr0 = 2;
	delayed call vec_Mul2D2W8_AddVr;
		ar1=ar0+gr0 with gr1=gr0;		
		nul;

	delayed goto finish3;
		pop ar6,gr6;
		pop ar0,gr0;
	
	<mul3N>
	delayed call vec_ClipMulNDNW8_AddVr;
		gr0=2;
		
	pop ar6,gr6;
	pop ar0,gr0;
	<finish3>
	
    pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
 
	return;

.wait;
end ".text_nmpls";
