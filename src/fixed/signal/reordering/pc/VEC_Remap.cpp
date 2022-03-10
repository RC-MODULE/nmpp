//------------------------------------------------------------------------
//
//  $Workfile:: pcRemap. $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   Remap.cpp
//! \author ������ �������
//! \brief  ������� �������������� �� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vec.h"
//#include "splib.h"
#include "nmpp.h"


void nmppsRemap_32u(nm32u*	pSrcVec,		
	nm32u*	pDstVec,
	nm32s*			pRemapTable,
	int				nDstVecSize
	)
{
	int t;
	for(int i=0;i<nDstVecSize;i++)
	{
		t=pSrcVec[pRemapTable[i]];
		pDstVec[i]=t;
	}
	
}
 
