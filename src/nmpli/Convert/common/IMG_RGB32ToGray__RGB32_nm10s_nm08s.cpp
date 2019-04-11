#include "nmtype.h"
#include "nmpli/iDef.h"
#include "nmpli/iInit.h"
#include "nmplv/vSelect.h"



//!
//! \perfinclude _nmppiRGB32ToGray__F10RGB32_nm8uPPciPv.html
//!

void nmppiRGB32ToGray_8u8s(RGB32_nm8u* pRGB, nm8s* pDstGray, int nSize, void *pTmp)
{
	nmppiRGB32ToGray_8u32s(pRGB, (nm32s*) pTmp,nSize);
	nmppsClipRShiftConvertAddC_32s8s((nm32s*)pTmp, 24,16,0,(nm8s*)pDstGray,nSize);
}


//!
//! \perfinclude _nmppiRGB32ToGray__F11RGB32_nm10sPPciPv.html
//!

void nmppiRGB32ToGray_10s8s(RGB32_nm10s* pRGB, nm8s* pDstGray, int nSize, void *pTmp)
{
	nmppiRGB32ToGray_10s32s(pRGB, (nm32s*) pTmp,nSize);
	nmppsClipRShiftConvertAddC_32s8s((nm32s*)pTmp, 24,16,0,(nm8s*)pDstGray,nSize);
}