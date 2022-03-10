// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analogs for conversion functions
// This functions work on the RISC-core only

#include "nmpp.h"

void nmppsConvertRisc_8u32u(const nm8u *pSrcVec, nm32u *pDstVec, int nSize)
{
    int i;
    for(i = 0; i < nSize; i++) {
        pDstVec[i] = (nm32u)pSrcVec[i];
    }
}

void nmppsConvertRisc_32u8u(const nm32u* pSrcVec, nm8u* pDstVec, int nSize)
{
    int i;
    for(i = 0; i < nSize; i++) {
        pDstVec[i] = (nm8u)pSrcVec[i];
    }
}