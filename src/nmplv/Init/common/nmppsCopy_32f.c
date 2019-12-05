
#include "nmpp.h"

int IsEvenAddress(int address)
{
  if(address & 1 == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

void nmppsCopy_32f(const nm32f* pSrcVec, nm32f* pDstVec, int size)
{
  int src_address = (int)(pSrcVec);
  int dst_address = (int)(pDstVec);

  int src_even_address = IsEvenAddress(src_address);
  int dst_even_address = IsEvenAddress(dst_address);

  if(src_even_address == 1 && dst_even_address == 1) {
	Copy_32f(pSrcVec, pDstVec, size);	 
  }
  else if(src_even_address == 0 && dst_even_address == 0) {
	pDstVec[0] = pSrcVec[0];
	Copy_32f(pSrcVec + 1, pDstVec + 1, size - 1);
  }
  else {
	nmppsCopyRisc_32f(pSrcVec, pDstVec, size);
  }
}