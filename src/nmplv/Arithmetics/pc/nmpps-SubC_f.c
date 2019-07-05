//------------------------------------------------------------------------
//
//  $Workfile:: SubC.cpp  $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   SubC_f.cpp
//! \author ���� ��������
//! \brief  �������������� ������� 
//!
//! \endif
//!
//------------------------------------------------------------------------


#include "nmtype.h"


void nmppsSubC_32f(const nm32f* pSrcVec, nm32f* pDstVec, float C, int nSize){
	for(int i=0;i<nSize;i++){
		pDstVec[i] = pSrcVec[i] - C;
	}	
}


