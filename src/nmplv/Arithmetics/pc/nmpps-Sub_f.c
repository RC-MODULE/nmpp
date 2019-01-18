 #include "nmpp.h"

void nmppsSub_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, int nSize) {
  int i;
  for(i = 0; i < nSize; i++) {
    pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
  }
}
