//------------------------------------------------------------------------
//
//  $Workfile:: VEC_FirstZeroPos.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
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

//!
//! \perfinclude _VEC_LastNonZeroPos__FPii.html
//! 
int VEC_LastNonZeroPos(int* pSrcVec, int nSize)
{
	for(int i=nSize-1; i>=0; i--){
		if (pSrcVec[i]!=0)
			return i;
	}
	return -1;
}