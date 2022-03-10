#include <malloc.h>
#include "malloc32.h"
#include "nmplv/vSupport.h"
#include "nmplv/vInit.h"
#include "nmplv/vBitwise.h"


//#ifdef __NM__
//	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32);}
//#else 
//	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32*4);}
//#endif

//#ifdef __NM__
//	struct NmppsMallocSpec nmppsMallocSpec = {{malloc0,   malloc1,   malloc2,   malloc3},   MALLOC32_RING_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0,1};
//
//#else 
//	void* __malloc32(unsigned int sizeInt32){
//		return malloc(sizeInt32*4);
//	}
//	struct NmppsMallocSpec nmppsMallocSpec = {{__malloc32,__malloc32,__malloc32,__malloc32},MALLOC32_RING_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF,1};
//#endif 


void nmppsMallocRandomRoute(){
	nmppsRandUniform_64u(nmppsMallocSpec.route,NMPPS_MALLOC_LIMIT/16);
	nmppsAndC_32u((nm32u*)nmppsMallocSpec.route,0x33333333,(nm32u*)nmppsMallocSpec.route,NMPPS_MALLOC_LIMIT/8);
	nmppsMallocSpec.route[NMPPS_MALLOC_LIMIT/16-1]|=0xF000000000000000l;
}
	