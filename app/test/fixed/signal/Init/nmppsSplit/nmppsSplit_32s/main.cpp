#include "nmpp.h"
#include "minrep.h"
#include "test.h"


#define xnmppsSplit(bits,src,dst0,dst1,size)  nmppsSplit_##bits##s(src,dst0,dst1,size) 
#define  nmppsSplit(bits,src,dst0,dst1,size) xnmppsSplit(bits,src,dst0,dst1,size) 

#define BITS 32

int main()
{
	int maxSize = 1024;
	NM_TYPE(BITS) *L0 = nmppsMalloc(BITS, maxSize);
	NM_TYPE(BITS) *G0 = nmppsMalloc(BITS, maxSize+128);
	NM_TYPE(BITS) *G1 = nmppsMalloc(BITS, maxSize+128);
	
	if ((L0==0)||(G0==0)||(G1==0)) return -1;
	
	nmppsRamp_32s( L0, 0,1, maxSize);
	nmppsSet(BITS, -1, G0,  maxSize + 128);
	nmppsSet(BITS, -1, G1,  maxSize + 128);
	

	int dim = DIM(BITS);
	unsigned int crc = 0;
	for(int size=dim*2; size<maxSize; size+=dim*2*NMPP_MIN_REP)
	{
		nmppsSplit (BITS, L0, G0, G1, size);
		nmppsCrcAcc(BITS, G0,size/2 + 128, &crc);
		nmppsCrcAcc(BITS, G1,size/2 + 128, &crc);
	}

	dump(32, L0, 8,8);	printf("\n");
	dump(32, G0, 8,8);	printf("\n");
	dump(32, G1, 8,8);	printf("\n");

	nmppsFree(L0);
	nmppsFree(G0);
	nmppsFree(G1);
	return crc>>2;
}

