//------------------------------------------------------------------------
//
//  $Workfile:: nmppsFirstZeroPos.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   nmppsFirstZeroPos.cpp
//! \author S. Mushkaev
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------
int nmppsFirstZeroPos(int* pSrcVec, int nSize)
{
	int i;
	for(i=0;i<nSize;i++){
		if (pSrcVec[i]==0)
			return i;
	}
	return -1;
}