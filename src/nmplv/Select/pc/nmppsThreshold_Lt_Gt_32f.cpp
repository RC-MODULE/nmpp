#include "nmtype.h"

void nmppsThreshold_Lt_Gt_32f(nm32f* pSrcVec, nm32f* pDstVec, float min, float max,  int size){
	for(int i=0;i<size;i++){
		if(pSrcVec[i]<min){
			pDstVec[i] = min;
		} else if (pSrcVec[i]>max) {
			pDstVec[i] = max;	
		}
		else {
			pDstVec[i] = pSrcVec[i];	
		}
	}
}
