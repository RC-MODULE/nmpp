#include "nmpli.h"


//!
//! \perfinclude _IMG_RGB32ToGray__F10RGB32_nm8uPPciPv.html
//!

void IMG_RGB32ToGray(RGB32_nm8u* pRGB, nm8s* pDstGray, int nSize, void *pTmp)
{
	IMG_RGB32ToGray(pRGB, (nm32s*) pTmp,nSize);
	nmppsClipRShiftConvertAddC_32s8s((nm32s*)pTmp, 24,16,0,(nm8s*)pDstGray,nSize);
}


//!
//! \perfinclude _IMG_RGB32ToGray__F11RGB32_nm10sPPciPv.html
//!

void IMG_RGB32ToGray(RGB32_nm10s* pRGB, nm8s* pDstGray, int nSize, void *pTmp)
{
	IMG_RGB32ToGray(pRGB, (nm32s*) pTmp,nSize);
	nmppsClipRShiftConvertAddC_32s8s((nm32s*)pTmp, 24,16,0,(nm8s*)pDstGray,nSize);
}