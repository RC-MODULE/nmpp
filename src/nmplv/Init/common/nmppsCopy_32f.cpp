
//*******************************************************************************************//
//* Prototype: void nmppsCopy_32f(const float* pSrcVec, float* pDstVec, int size);          *//
//* Contents: A Copying of a floating point array from src to dst                           *//
//* src - all addresses (odd, even)                                                         *//
//* dst - all addresses (odd, even)                                                         *//
//* size - all sizes except zero (1, 2, 3, 4, ...)                                          *//
//*******************************************************************************************//
#include "nmtype.h"
#include "nmpp.h"
//#include "nmplv\\vInit.h"
//extern "C" {
//void nmppsCopyOddToOdd_32f(const float* pSrcVec, float* pDstVec, int size);
//void nmppsCopyEvenToOdd_32f(const float* pSrcVec, float* pDstVec, int size);
//void nmppsCopyOddToEven_32f(const float* pSrcVec, float* pDstVec, int size);
//void nmppsCopyEvenToEven_32f(const float* pSrcVec, float* pDstVec, int size);
//
//};

typedef void (*pfn_nmppsCopy_32f)(nm32f const * pSrcVec, nm32f* pDstVec, int size);

//void test(const float* pSrcVec, float* pDstVec, int size);

extern "C"{
	
	
pfn_nmppsCopy_32f nmppsCopy_32f_array[4] = {&nmppsCopyEvenToEven_32f,
                                            &nmppsCopyEvenToOdd_32f,
											&nmppsCopyOddToEven_32f,
											&nmppsCopyOddToOdd_32f
										   };

int GetCopyingFuncNum(int src_address, int dst_address)
{
  return ((src_address & 1) << 1) | (dst_address & 1);
}

void nmppsCopy_32f(const nm32f* pSrcVec, nm32f* pDstVec, int size)
{
  int src_address = *((int*)(&pSrcVec));
  int dst_address = *((int*)(&pDstVec));

  int num = GetCopyingFuncNum(src_address, dst_address);

  (nmppsCopy_32f_array[num])(pSrcVec, pDstVec, size);  
}
};