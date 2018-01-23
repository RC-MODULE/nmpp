// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analog for the function nmppsConvert_32sc32fcr

#include "nmtype.h"

void nmppsConvert_32sc32fcr(const nm32sc *pSrcVec, nm32fc *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = (float)pSrcVec[i].im;
		pDstVec[i].im = (float)pSrcVec[i].re;
	}
}