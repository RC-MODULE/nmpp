#ifdef __cplusplus
		extern "C" {
#endif
#include "nmtype.h"
#define NmppiFilterState nm64s

void nmppiFilter_8s16s( nm8s * pSrcImg, nm16s* pDstImg, int nWidth, int nHeight, NmppiFilterState* pKernel);
int  nmppiFilterInit_8s16s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, NmppiFilterState* pKernel);
int  nmppiFilterInitAlloc_8s16s(NmppiFilterState** ppState, int* pKernel, int kerWidth, int kerHeight, int imgWidth);
void nmppiFilterFree(NmppiFilterState* pState);

#ifdef __cplusplus
		};
#endif
