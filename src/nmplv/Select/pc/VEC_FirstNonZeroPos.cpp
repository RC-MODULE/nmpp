//------------------------------------------------------------------------
//
//  $Workfile:: VEC_FirstZeroPos.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   VEC_FirstZeroPos.cpp
//! \author S. Mushkaev
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------
int VEC_FirstNonZeroPos(int* pSrcVec, int nSize)
{
	for(int i=0;i<nSize;i++){
		if (pSrcVec[i]!=0)
			return i;
	}
	return -1;
}