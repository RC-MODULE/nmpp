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
#include "nmpp.h"
//!
//! \perfinclude _nmppsMinIndx__FPciRiRiPvPvi_.html
//! 
void nmppsMinIndx_8s(nm8s7b   *pSrcVec, int nSize, int *pIndex, int8b *pMinValue, void *pLTmpBuff,void *pGTmpBuff, int nSearchDir)
{
	int nPos,n;
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

	nmppsMin_8s7b(pSrcVec, nSize, pMinValue);
	nmppsSubC_8s(pSrcVec,*pMinValue,(nm8s*)pTmp1,nSize);
	nmppsCmpEq0_8u7b((nm8u7b*)pTmp1,(nm1*)pTmp2,nSize,0); //Create min bitmap

	if(nSearchDir > 0){
		nPos  =nmppsFirstNonZeroIndx_32s((int*)pTmp2,nSize>>5);
		if (nPos==-1){
			*pIndex=0;
			return;
		}
		n=((int*)pTmp2)[nPos];	
		for((*pIndex)=0; (*pIndex)<32; (*pIndex)++){
			if (n&1)
				break;
			n>>=1;
		}
	} else {
		nPos  =nmppsLastNonZeroIndx_32s((int*)pTmp2,nSize>>5); 
		if (nPos==-1){
			*pIndex=nSize-1;
			return;
		}
		n=((int*)pTmp2)[nPos];	
		for((*pIndex)=31; (*pIndex)>=0; (*pIndex)--){
			if (n&0x80000000)
				break;
			n<<=1;
		}
	}
	(*pIndex)+=nPos*32;

}

