//------------------------------------------------------------------------
//
//  $Workfile:: nmppsClip_Arsh_Cnv_AddC_Ext_16s8s_ $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:08 $
//
//! \if file_doc
//!
//! \file  nmppsClipArshCnv_AddC_Ext_.asm
//! \author Sergey Landyshev
//! \brief  \ru Функции преобразования елементов вектора.
//!			\en Element conversion functions
//!
//! \endif
//!
//------------------------------------------------------------------------
extern vec_ClipMul2D2W8_AddVr_Ext:label; 
//------------------------------------------------------------------------
data ".data_nmplv_L"
    ClipTable: word[16] = (
            0fffeh, 0fffch, 0fff8h, 0fff0h, 
            0ffe0h, 0ffc0h, 0ff80h, 0ff00h, 
            0fe00h, 0fc00h, 0f800h, 0f000h, 
            0e000h, 0c000h, 08000h, 00000h
            ); 
    ShiftTable: word[8] = (
            0202h, 000ah, 0022h, 0082h,
            0202h, 0802h, 2002h, 8002h
            );
    WeightTable: long[8] = (
            0000000000000001hl,
            0000000000000100hl,
            0000000000010000hl,
            0000000001000000hl,
            0000000100000000hl,
            0000010000000000hl,
            0001000000000000hl,
            0100000000000000hl
            );
end ".data_nmplv_L";
//------------------------------------------------------------------------
macro SUBST_DEC()
    gr0 = [ar1++];
    ar0 = ar4 with gr0--;
    gr1 = [ar0+=gr0];
    gr0 = [ar1++];
    ar0 = ar4 with gr0--;
    gr2 = [ar0+=gr0];
    gr2 <<= 16;
    gr2 = gr1 or gr2;
end SUBST_DEC;
macro SUBST_SHIFT()
    gr0 = [ar1++];
    ar0 = ar4 with gr0 >>= 1;
    gr1 = [ar0+=gr0];
    gr0 = [ar1++];
    ar0 = ar4 with gr0 >>= 1;
    gr2 = [ar0+=gr0];
    gr2 <<= 16;
    gr2 = gr1 or gr2;
end SUBST_SHIFT;
//------------------------------------------------------------------------
begin ".text_nmplv"
pnShift: word;
pnC: word;
Params: long[21];
//------------------------------------------------------------------------
//! \fn void nmppsClipArshCnv_AddC_Ext_(v8nm16s* pSrcVec, v8nm32s* pnClipFactor, v8nm32s* pnShift, v8nm8s* pnAdd,  v8nm8s* pDstVec, int nSize);
//! \
//! \perfinclude _nmppsClipArshCnv_AddC_Ext__F7v8nm16sP7v8nm32sP7v8nm32sP6v8nm8sP6v8nm8sPi_.html
//------------------------------------------------------------------------
global _void._.8.8nmppsClipArshCnv_AddC_Ext_.1class._v8nm16s._.0.9._class._v8nm32s._.0.9._class._v8nm32s._.0.9._class._v8nm32s._.0.9._class._v8nm8s._.0.9._int.2 :label;
<_void._.8.8nmppsClipArshCnv_AddC_Ext_.1class._v8nm16s._.0.9._class._v8nm32s._.0.9._class._v8nm32s._.0.9._class._v8nm32s._.0.9._class._v8nm8s._.0.9._int.2>
.branch;
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;

    gr3 = [--ar5];  // pshSrc.
    gr1 = [--ar5];  // pnClip.
    ar1 = [--ar5];  // pnShift.
    gr0 = [--ar5];  // pshAdd.
    gr2 = [--ar5];  // pchDst.
    ar2 = [--ar5];  // nSrcSize.

    ar0 = Params;
    push ar0, gr0;
    push ar1, gr1;
    call _nmppsClipArshCnv_AddC_Ext_Set_32s;
    pop ar1, gr1;
    pop ar0, gr0;
    
    ar3 = Params;
    push ar2, gr2;
    push ar3, gr3;
    call _nmppsClipArshCnv_AddC_Ext_Exe_16s;
    pop ar3, gr3;
    pop ar2, gr2;
    
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
 return;
 .wait;
//------------------------------------------------------------------------
// void nmppsClipArshCnv_AddC_Ext_Set_(int *pnClip, int *pnShift, char *pchC, S_Clip_Arsh_Cnv_AddC_Ext *pParams);
//
// 
<_nmppsClipArshCnv_AddC_Ext_Set_32s>
.branch;
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

    ar1 = [--ar5];  // pnClip.
    ar0 = [--ar5];  // pnShift.
    ar2 = [--ar5];  // pchC.
    ar3 = [--ar5];  // pParams
    
    [pnShift] = ar0;
    [pnC] = ar2;
        
        // Detect pParamss->lF1cr1.
    ar4 = ClipTable;
    SUBST_DEC();
    ar2 = gr2;
    SUBST_DEC();
    [ar3++] = ar2, gr2;
        
        // Detect pParams->lF1cr2.
    SUBST_DEC();
    ar2 = gr2;
    SUBST_DEC();
    [ar3++] = ar2, gr2;
    
        // Detect pParamss->lSb1.
    ar4 = ShiftTable;
    ar1 = [pnShift];
    SUBST_SHIFT();
    ar2 = gr2;
    SUBST_SHIFT();
    [ar3++] = ar2, gr2;
        
        // Detect pParams->lSb2.
    SUBST_SHIFT();
    ar2 = gr2;
    SUBST_SHIFT();
    [ar3++] = ar2, gr2;

    
        // Detect pParams->lVr.
    ar0 = [pnC];
    gr0 = [ar0++];
    gr1 = [ar0++] with gr0 <<= 24;
    gr2 = [ar0++] with gr0 >>= 24;
    gr3 = [ar0++] with gr1 <<= 24;
    gr4 = [ar0++] with gr1 >>= 16;
    gr5 = [ar0++] with gr1 = gr0 or gr1;
    gr6 = [ar0++] with gr2 <<= 24;
    gr7 = [ar0++] with gr2 >>= 8;
    gr1 = gr1 or gr2;
    gr3 <<= 24;
    gr1 = gr1 or gr3;
    ar1 = gr1 with gr1 = gr4 << 24;
    gr1 >>= 24;
    gr5 <<= 24;
    gr5 >>= 16;
    gr1 = gr1 or gr5;
    gr6 <<= 24;
    gr6 >>= 8;
    gr1 = gr1 or gr6;
    gr7 <<= 24;
    gr1 = gr1 or gr7;
    [ar3++] = ar1, gr1;
    
        // Detect weights.
    ar0 = WeightTable with gr1 = false;
    ar1 = gr1;    
.repeat 8;
    ar2, gr2 = [ar0++];    
    [ar3++] = ar1, gr1;
    [ar3++] = ar2, gr2;
.endrepeat;

    gr3 = 4;
    ar3 -= 32;
    ar0 = [pnShift] with gr4 = gr3 << 1;
    gr0 = [ar0++];
    gr0;
    
<lab_WeightReplace>    
    if <>0 delayed goto lab_WeightReplace_Escape with gr4--;
        ar2 = ar3;
        ar1 = ar3;

    ar5, gr5 = [ar1++];
    ar6, gr6 = [ar1++];
    [ar2++] = ar6, gr6;
    [ar2++] = ar5, gr5;
<lab_WeightReplace_Escape>
    if > delayed goto lab_WeightReplace;
        gr0 = [ar0++];
        ar3 += gr3 with gr0;        

    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
return;
.wait;
//------------------------------------------------------------------------
// void nmppsClipArshCnv_AddC_Ext_Aux_(short *pshSrc, S_Clip_Arsh_Cnv_AddC_Ext *pParams, char *pchDst, int nSrcSize);
//
<_nmppsClipArshCnv_AddC_Ext_Exe_16s>
.branch;
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4 with gr4 = false;
    push ar5, gr5 with gr4++;
    push ar6, gr6 with gr4++;

    ar0 = [--ar5] with gr0 = gr4 << 1;  // pshSrc;
    ar4 = [--ar5] with gr1 = gr0;       // pParams.
    ar6 = [--ar5] with gr6 = gr4;       // pchDst;
    gr5 = [--ar5];                      // nSrcSize in short.

    ar2 = ar4; ar4 += gr4;  // F1cr1.
    gr2 = ar4; ar4 += gr4;  // F1cr2.
    ar3 = ar4; ar4 += gr4;  // sb1.
    gr3 = ar4; ar4 += gr4;  // sb2.

    vr = [ar4++];
    gr4 = 80808080h;
    nb1 = gr4;

    //ar4 -> WFIFO matrix

<LoadLocalMatrix>

	delayed call vec_ClipMul2D2W8_AddVr_Ext	with gr5;
		ar1 = ar0 + 2;	

	
	pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;

return;
.wait;

end ".text_nmplv";
