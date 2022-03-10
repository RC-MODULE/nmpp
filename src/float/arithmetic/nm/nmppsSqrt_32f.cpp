
#include "nmpp.h"

extern "C" __attribute__ ((section(".text_nmplv")))
void nmppsSqrt_32f_(const nm32f* pSrcVec, nm32f* pDstVec, nm32f* pTmpBuf, int nSize) {
  // pDstVec[i] = exp(0.5 * ln(pSrcVec[i]))
  // pTmpBuf - the additional buffer (have to be in the other banks from pSrcVec and pDstVec)

  nmppsLn_32f(pSrcVec, pDstVec, nSize);
  nmppsMulC_32f(pDstVec, pTmpBuf, 0.5, nSize);
  nmppsExp_32f(pTmpBuf, pDstVec, nSize);
  return;
}