//------------------------------------------------------------------------
//
//  $Workfile:: BuildDiagWeights8.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   BuildDiagWeights8.asm
//! \author ������ ��������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmvcore"
    //--------------------------------------------------------------------
    // ����:
    //      ar1 - ����� �����.
    //      gr1 - �������� (8 ���).
    // �������� ��������: ar1.
    //--------------------------------------------------------------------
global nmppsBuildDiagWeights8_: label;
<nmppsBuildDiagWeights8_>
    push ar0, gr0 with gr0 = false;
    ar0 = gr0 with gr1 <<= 24;
    gr0 = gr1 >> 24;
    [ar1++] = gr0 with gr1 = gr0;
    [ar1++] = ar0 with gr0 <<= 8;
    [ar1++] = gr0;
    [ar1++] = ar0 with gr0 <<= 8;
    [ar1++] = gr0;
    [ar1++] = ar0 with gr0 <<= 8;
    [ar1++] = gr0;
    [ar1++] = ar0 with gr0 >>= 24;
    [ar1++] = ar0, gr0 with gr0 <<= 8;
    [ar1++] = ar0, gr0 with gr0 <<= 8;
    [ar1++] = ar0, gr0 with gr0 <<= 8;
    [ar1++] = ar0, gr0;
    pop ar0, gr0;
    return;
    //--------------------------------------------------------------------
end ".text_nmvcore";