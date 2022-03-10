//#include <malloc.h>
#include "malloc32.h"

//#include "nmplv/vSupport.h"
//#include "nmplv/vInit.h"
//#include "nmplv/vBitwise.h"




void nmppsFree(void* buffer){
	free(buffer);
}

nm1*     nmppsMalloc_1     (unsigned sizeInt1)  { return (nm1*)    	malloc32((sizeInt1+63)/64*2);}
nm2s*    nmppsMalloc_2s    (unsigned sizeInt2)  { return (nm2s*)   	malloc32((sizeInt2+31)/32*2);}
nm2u*    nmppsMalloc_2u    (unsigned sizeInt2)  { return (nm2u*)   	malloc32((sizeInt2+31)/32*2);}
nm4s*    nmppsMalloc_4s    (unsigned sizeInt4)  { return (nm4s*)   	malloc32((sizeInt4+15)/16*2);}
nm4u*    nmppsMalloc_4u    (unsigned sizeInt4)  { return (nm4u*)   	malloc32((sizeInt4+15)/16*2);}
nm8s*    nmppsMalloc_8s    (unsigned sizeInt8)  { return (nm8s*)   	malloc32((sizeInt8+7)/8*2);}
nm8u*    nmppsMalloc_8u    (unsigned sizeInt8)  { return (nm8u*)   	malloc32((sizeInt8+7)/8*2);}
nm16s*   nmppsMalloc_16s   (unsigned sizeInt16) { return (nm16s*)  	malloc32((sizeInt16+3)/4*2);}
nm16u*   nmppsMalloc_16u   (unsigned sizeInt16) { return (nm16u*)  	malloc32((sizeInt16+3)/4*2);}
nm32s*   nmppsMalloc_32s   (unsigned sizeInt32) { return (nm32s*)  	malloc32(sizeInt32+(1&sizeInt32));}
float*   nmppsMalloc_32f   (unsigned size)      { return (float*)  	malloc32(size);}
double*  nmppsMalloc_64f   (unsigned size)      { return (double*) 	malloc32(size<<1);}
nm32sc*  nmppsMalloc_32sc  (unsigned size)      { return (nm32sc*) 	malloc32(size<<1);}
nm32fc*  nmppsMalloc_32fc  (unsigned size)      { return (nm32fc*) 	malloc32(size<<1);}
nm32fcr* nmppsMalloc_32fcr (unsigned size)      { return (nm32fcr*)	malloc32(size<<1);}
nm32u*   nmppsMalloc_32u   (unsigned sizeInt32) { return (nm32u*)  	malloc32(sizeInt32+(1&sizeInt32));}
nm64s*   nmppsMalloc_64s   (unsigned sizeInt64) { return (nm64s*)  	malloc32((sizeInt64)<<1);}
nm64u*   nmppsMalloc_64u   (unsigned sizeInt64) { return (nm64u*)  	malloc32((sizeInt64)<<1);}
nm64sc*  nmppsMalloc_64sc  (unsigned sizeInt128){ return (nm64sc*) 	malloc32((sizeInt128)<<2);}




nm8s*  nmppsMallocFrame_8s (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8s * pFrame){return (nm8s* )nmppsMallocFrame_64u((sizeInt8+ 7)>>3,(boundaryInt8+ 7)>>3,(NmppsFrame_64u*)pFrame);}
nm8u*  nmppsMallocFrame_8u (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8u * pFrame){return (nm8u* )nmppsMallocFrame_64u((sizeInt8+ 7)>>3,(boundaryInt8+ 7)>>3,(NmppsFrame_64u*)pFrame);}
nm16s* nmppsMallocFrame_16s(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16s* pFrame){return (nm16s*)nmppsMallocFrame_64u((sizeInt16+3)>>2,(boundaryInt16+3)>>2,(NmppsFrame_64u*)pFrame);}
nm16u* nmppsMallocFrame_16u(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16u* pFrame){return (nm16u*)nmppsMallocFrame_64u((sizeInt16+3)>>2,(boundaryInt16+3)>>2,(NmppsFrame_64u*)pFrame);}
nm32s* nmppsMallocFrame_32s(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32s* pFrame){return (nm32s*)nmppsMallocFrame_64u((sizeInt32+1)>>1,(boundaryInt32+1)>>1,(NmppsFrame_64u*)pFrame);}
nm32u* nmppsMallocFrame_32u(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32u* pFrame){return (nm32u*)nmppsMallocFrame_64u((sizeInt32+1)>>1,(boundaryInt32+1)>>1,(NmppsFrame_64u*)pFrame);}
nm64s* nmppsMallocFrame_64s(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64s* pFrame){return (nm64s*)nmppsMallocFrame_64u(sizeInt64,boundaryInt64,(NmppsFrame_64u*)pFrame);}
nm64u* nmppsMallocFrame_64u(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64u* pFrame){      
	pFrame->pull=malloc32(sizeInt64*2+boundaryInt64*4);
	pFrame->data=(nm64u*)pFrame->pull;
	if (pFrame->pull)
		pFrame->data+=boundaryInt64;
	return pFrame->data;
}
void   nmppsFreeFrame(void* buffer){
	if (((NmppsFrame_64u*)buffer)->pull)
		free(((NmppsFrame_64u*)buffer)->pull);
}