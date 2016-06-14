//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   GetMax.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"
//!
//! \perfinclude _nmppsMaxIndx__FPiiRiRiPvPvi_.html
//! 
void nmppsMaxIndx_32s(nm32s31b *pSrcVec, int nSize, int* pIndex, int32b* pMaxValue, void *pLTmpBuff,void *pGTmpBuff, int nSearchDir)
{
	int nPos;
	void* pTmp1;
	void* pTmp2;
	
	//if ((int)pSrcVec>0){
		pTmp1=pGTmpBuff;
		pTmp2=pLTmpBuff;
	//}
	//else	{
	//	pTmp1=pLTmpBuff;
	//	pTmp2=pGTmpBuff;
	//}

	nmppsMax_32s31b(pSrcVec, nSize, pMaxValue);
	nmppsSubCRev_32s(pSrcVec,*pMaxValue,(nm32s*)pTmp1,nSize);
	nmppsCmpEq0_32u31b((nm32u31b*)pTmp1,(nm1*)pTmp2,nSize,0); //Create Max bitmap

	if(nSearchDir > 0){
		nPos  =nmppsFirstNonZeroIndx_32s((int*)pTmp2,nSize>>5);
		(*pIndex)=nmppsFirstZeroIndx_32s((int*)pTmp1+nPos*32,32);
		(*pIndex)+=nPos*32;
	} else {
		nPos  =nmppsLastNonZeroIndx_32s((int*)pTmp2,nSize>>5); 
		(*pIndex)=nmppsLastZeroIndx_32s((int*)pTmp1+nPos*32,32);
		(*pIndex)+=nPos*32;
	}
}

