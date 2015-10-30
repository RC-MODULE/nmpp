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
#include "nmplv.h"
//!
//! \perfinclude _VEC_MaxPos__FPSsiRiRiPvPvi.html
//! 
void VEC_MaxPos (nm16s15b *pSrcVec, int nSize, int& nIndex, int16b &nMaxValue, void *pLTmpBuff,void *pGTmpBuff, int nSearchDir)

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

	VEC_MaxVal(pSrcVec, nSize, nMaxValue);
	nmppsSubCRev(pSrcVec,nMaxValue,(nm16s*)pTmp1,nSize);
	VEC_CmpEq0((nm16u15b*)pTmp1,(nm1*)pTmp2,nSize,0); //Create Max bitmap


	if(nSearchDir > 0){
		nPos  =VEC_FirstNonZeroPos((int*)pTmp2,nSize>>5);
		int n=((int*)pTmp2)[nPos];	
		for(nIndex=0; nIndex<32; nIndex++){
			if (n&1)
				break;
			n>>=1;
		}
	} else {
		nPos  =VEC_LastNonZeroPos((int*)pTmp2,nSize>>5); 
		int n=((int*)pTmp2)[nPos];	
		for(nIndex=31; nIndex>=0; nIndex--){
			if (n&0x80000000)
				break;
			n<<=1;
		}
	}
	nIndex+=nPos*32;
}
