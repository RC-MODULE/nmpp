//------------------------------------------------------------------------
//
//  $Workfile:: GetMin.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   GetMin.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"
//!
//! \perfinclude _nmppsMinPos__FPciRiRiPvPvi_.html
//! 
void nmppsMinPos_8s(nm8s7b   *pSrcVec, int nSize, int& nIndex, int8b &nMinValue, void *pLTmpBuff,void *pGTmpBuff, int nSearchDir)
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

	nmppsMinVal_8s(pSrcVec, nSize, nMinValue);
	nmppsSubC_8s(pSrcVec,nMinValue,(nm8s*)pTmp1,nSize);
	nmppsCmpEq0_8u((nm8u7b*)pTmp1,(nm1*)pTmp2,nSize,0); //Create min bitmap

	if(nSearchDir > 0){
		nPos  =nmppsFirstNonZeroPos_((int*)pTmp2,nSize>>5);
		int n=((int*)pTmp2)[nPos];	
		for(nIndex=0; nIndex<32; nIndex++){
			if (n&1)
				break;
			n>>=1;
		}
	} else {
		nPos  =nmppsLastNonZeroPos_((int*)pTmp2,nSize>>5); 
		int n=((int*)pTmp2)[nPos];	
		for(nIndex=31; nIndex>=0; nIndex--){
			if (n&0x80000000)
				break;
			n<<=1;
		}
	}

	nIndex+=nPos*32;

}

