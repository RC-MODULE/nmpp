//------------------------------------------------------------------------
//
//  $Workfile:: DupValueInVector8.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   DupValueInVector8.asm
//! \author ������ ��������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------
begin ".text_nmvcore"
    //--------------------------------------------------------------------
    // ����:
    //      ar1 - ������.
    //      gr1 - �������� (8 ���).
    // �������� ��������: ar1, gr1.
    //--------------------------------------------------------------------
global nmppsDupValueInVector4_: label;
<nmppsDupValueInVector4_>
    push ar0, gr0 with gr0 = gr1 << 28;
    gr1 = gr0 with gr0 >>= 4;
    gr1 = gr0 or gr1;
    gr0 >>= 4;
    gr1 = gr0 or gr1;
    gr0 >>= 4;
	gr1 = gr0 or gr1;
    gr0 >>= 4;
	gr1 = gr0 or gr1;
    gr0 >>= 4;
	gr1 = gr0 or gr1;
    gr0 >>= 4;
	gr1 = gr0 or gr1;
    gr0 >>= 4;
    pop ar0, gr0 with gr1 = gr0 or gr1;
    delayed return;
        [ar1++] = gr1;
        [ar1++] = gr1 with gr1 >>= 28;
    //--------------------------------------------------------------------
end ".text_nmvcore";