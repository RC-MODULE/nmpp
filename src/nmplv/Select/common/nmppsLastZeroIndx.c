//------------------------------------------------------------------------
//
//  $Workfile:: nmppsFirstZeroPos_.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   nmppsFirstZeroPos_.cpp
//! \author S. Mushkaev
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------


//!
//! \perfinclude _nmppsLastZeroPos__FPii_.html
//! 
int nmppsLastZeroPos_(int* pSrcVec, int nSize)
{
	int i;
	for(i=nSize-1; i>=0; i--){
		if (pSrcVec[i]==0)
			return i;
	}
	return -1;
}