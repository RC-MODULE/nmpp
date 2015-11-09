#include "nmpp.h"

void IMG_DeinterlaceSplit(nm8u* pSrcImg, int nSrcWidth, int nSrcHeight, nm8u* pDstEven, nm8u* pDstOdd)
{
	int i, j, IndSrc; // i - string index, j - column index

	nm32u* pSrcImg32 =(nm32u*) pSrcImg;
	nm32u* pDstEven32=(nm32u*) pDstEven;
	nm32u* pDstOdd32 =(nm32u*) pDstOdd;

	for (i = 0; i < nSrcHeight ; i++)
		for (j = 0; j < nSrcWidth/4 ; j++) {
			IndSrc 	= i * nSrcWidth/4 + j;
			if (i % 2 == 0){
				pDstEven32[(i/2)*nSrcWidth/4 + j] = pSrcImg32[IndSrc];
				
			}
			else {
				pDstOdd32[((i-1)/2)*nSrcWidth/4 + j] = pSrcImg32[IndSrc];	
			}
		}
};