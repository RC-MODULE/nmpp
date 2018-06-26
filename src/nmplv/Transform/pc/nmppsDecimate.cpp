#include "nmpp.h"

void nmppsDecimate_16s(nm16s* pSrc, int startPos, int step, nm16s* pDst, int nSize){
	for(int i=0;i<nSize;i++){
		pDst[i] = pSrc[step*i+startPos];
	}
}

void nmppsDecimate_32s(nm32s* pSrc, int startPos, int step, nm32s* pDst, int nSize){
	for(int i=0;i<nSize;i++){
		pDst[i] = pSrc[step*i+startPos];
	}
}