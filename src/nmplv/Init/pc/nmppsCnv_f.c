// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analogs for conversion functions (floating point)

#include "nmpp.h"

void nmppsConvert_32u32fcr(const nm32u* pSrcVec, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = (nm32f)(pSrcVec[i]);
		pDstVec[i].im = 0;
	}
}

void nmppsConvert_32s32fcr(const nm32s* pSrcVec, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = (nm32f)(pSrcVec[i]);
		pDstVec[i].im = 0;
	}
}

void nmppsConvert_32f32fcr(const nm32f* pSrcVec, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = pSrcVec[i];
		pDstVec[i].im = 0;
	}
}

void nmppsConvert_32sc32fcr(const nm32sc *pSrcVec, nm32fcr *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = (nm32f)pSrcVec[i].im;
		pDstVec[i].im = (nm32f)pSrcVec[i].re;
	}
}