
#include "nmpp.h"
#include "nmtype.h"

void nmppsCmpLteC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f* C, nm1* evenFlags, nm1* oddFlags, int step, int nSize)
{
  int i;
  int index = 0;
  for(i = 0; i < nSize*step; i += step) {
    if(pSrcVec[i].v0 - C->v0 <= 0.0f) {
      nmppsPut_1(evenFlags, index, 1);
    }
    else {
      nmppsPut_1(evenFlags, index, 0);
    }

    if(pSrcVec[i].v1 - C->v1 <= 0.0f) {
      nmppsPut_1(oddFlags, index, 1);
    }
    else {
      nmppsPut_1(oddFlags, index, 0);
    }
    index++;
  }
  unsigned residue = nSize << 27;
  residue >>= 27;
  if (residue != 0) {
    int tail = 32 - residue;
    while(tail-- > 0) {
      nmppsPut_1(evenFlags, index, 0);
      nmppsPut_1(oddFlags, index++, 0);
    }
  }
}
