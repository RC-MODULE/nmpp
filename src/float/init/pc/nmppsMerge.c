//------------------------------------------------------------------------
//
//  $Workfile:: pcConvert.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcConvert.cpp
//! \author ������ �������
//! \brief  ������� ��� �������������� ������������ ������.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpp.h"

void nmppsMerge_32f(const nm32f* src0, const nm32f* src1, nm32f* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}

