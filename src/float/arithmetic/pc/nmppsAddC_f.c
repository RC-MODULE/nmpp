//------------------------------------------------------------------------
//
//  $Workfile:: nmppsAdd_f.c    $
//
//  Р’РµРєС‚РѕСЂРЅРѕ-РјР°С‚СЂРёС‡РЅР°СЏ Р±РёР±Р»РёРѕС‚РµРєР°
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2019/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   nmppsAdd_f.c
//! \author РђРЅРґСЂРµР№ Р‘СЂРѕРґСЏР¶РµРЅРєРѕ
//! \brief  РђСЂРёС„РјРµС‚РёС‡РµСЃРєРёРµ С„СѓРЅРєС†РёРё
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
void nmppsAddC_32fcr(
const	nm32fcr *pSrcVec,
		nm32fcr *pDstVec,
		float nVal,
		int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = pSrcVec[i].re + nVal;
	}
}

void nmppsAddC_32f(const nm32f* pSrcVec, nm32f* pDstVec, float C, int nSize){
	int i;
	for(i=0;i<nSize;i++){
		pDstVec[i] = pSrcVec[i] + C;
	}	
}