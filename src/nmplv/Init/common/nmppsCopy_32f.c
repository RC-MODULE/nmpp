
#include "nmpp.h"

// extern "C" {
// 	int IsOddAddressRisc(float* address);
// };

int IsOddAddress(int address)
{
    return address & 1;
}



void nmppsCopy_32f(const nm32f* pSrcVec, nm32f* pDstVec, int size)
{
  int src_address = (int)(pSrcVec);
  int dst_address = (int)(pDstVec);

  int src_odd_address = IsOddAddress(src_address);
  int dst_odd_address = IsOddAddress(dst_address);

  if(src_odd_address == 0 && dst_odd_address == 0) {
	nmppsCopy_32f_even_even_address(pSrcVec, pDstVec, size);	 
  }
  else if(src_odd_address == 1 && dst_odd_address == 1) {
	nmppsCopy_32f_odd_odd_address(pSrcVec, pDstVec, size);
  }
  else if(src_odd_address == 0 && dst_odd_address == 1) {
	nmppsCopy_32f_even_odd_address(pSrcVec, pDstVec, size);
  }
  else {
	nmppsCopyRisc_32f(pSrcVec, pDstVec, size);
  }
}