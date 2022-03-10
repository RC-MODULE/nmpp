#include "nmpp.h"

int main()
{
	int size=1000;
	unsigned crc=0;
	nm64u* x=nmppsMalloc_64u(size);
	
	
	for(int shift=0;shift<64;shift++){
		nmppsRandUniform_64u(x,size);
		nmppsRShiftC_64u(x,shift,x,size);
		for(int i=0; i<1000; i++){	
			unsigned int res=nmppcSqrt_64u(x[i]);
			nmppsCrcAcc_32u((nm32u*)&res,1,&crc);
		}
	}
	nmppsFree(x);

	return crc>>2;
}

