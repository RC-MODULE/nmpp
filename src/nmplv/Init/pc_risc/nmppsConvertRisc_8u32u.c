// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analog for the function nmppsConvertRisc_8u32u

#include "nmtype.h"

void nmppsConvertRisc_8u32u(const nm8u *pSrcVec, nm32u *pDstVec, int nSize)
{
    int i, j;
    nSize = nSize >> 2;
    for(i = 0, j = 0; i < nSize; i++, j += 4) {
		pDstVec[j] = pSrcVec[i] << 24;
        pDstVec[j] = pDstVec[j] >> 24;

        pDstVec[j + 1] = pSrcVec[i] << 16;
        pDstVec[j + 1] = pDstVec[j + 1] >> 24;

        pDstVec[j + 2] = pSrcVec[i] << 8;
        pDstVec[j + 2] = pDstVec[j + 2] >> 24;

        pDstVec[j + 3] = pSrcVec[i] >> 24;
    }
}