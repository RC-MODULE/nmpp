// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analog for the function nmppsConvert_32s32fcr

#include "nmtype.h"

void nmppsConvert_32s32fcr(const nm32s* pSrcVec, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = (nm32f)(pSrcVec[i]);
		pDstVec[i].im = 0;
	}
}