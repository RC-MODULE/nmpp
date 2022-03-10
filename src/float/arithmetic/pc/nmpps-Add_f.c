 #include "nmtype.h"
 void nmppsAdd_32f(const nm32f* pSrc1, const nm32f* pSrc2, nm32f* pDst, int len){
	int i;
	for(i=0; i<len; i++){
		pDst[i]=pSrc1[i]+pSrc2[i];
	}
 }