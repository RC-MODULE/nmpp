
#include "nmpp.h"

typedef void (*pfn_nmppsCopy_32f)(const nm32f* pSrcVec, nm32f* pDstVec, int size);

pfn_nmppsCopy_32f nmppsCopy_32f_array[4] = {&nmppsCopy_32f_even_even_address,
                                            &nmppsCopy_32f_even_odd_address,
											&nmppsCopy_32f_odd_odd_address,
											&nmppsCopy_32f_odd_even_address};

int GetCopyingFuncNum(int src_address, int dst_address)
{
  return ((src_address & 1) << 1) | (dst_address & 1);
}

void nmppsCopy_32f(const nm32f* pSrcVec, nm32f* pDstVec, int size)
{
  int src_address = (int)(pSrcVec);
  int dst_address = (int)(pDstVec);

  int num = GetCopyingFuncNum(src_address, dst_address);

  (nmppsCopy_32f_array[num])(pSrcVec, pDstVec, size);  
}