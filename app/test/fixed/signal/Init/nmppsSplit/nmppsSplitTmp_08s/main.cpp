#include "nmpp.h"
#include "minrep.h"
#include "test.h"
#include "stdio.h"

#define xnmppsSplitTmp(bits,src,dst0,dst1,size,tmp)  nmppsSplitTmp_##bits##s(src,dst0,dst1,size,tmp) 
#define  nmppsSplitTmp(bits,src,dst0,dst1,size,tmp) xnmppsSplitTmp(bits,src,dst0,dst1,size,tmp) 

#define BITS 8

int main()
{
	int maxSize = 1024;
	NM_TYPE(BITS) *L0 = nmppsMalloc(BITS, maxSize);
	NM_TYPE(BITS) *L1 = nmppsMalloc(BITS, maxSize/2);
	NM_TYPE(BITS) *G0 = nmppsMalloc(BITS, maxSize/2+128);
	NM_TYPE(BITS) *G1 = nmppsMalloc(BITS, maxSize/2+128);
	
	if ((L0==0)||(G0==0)||(G1==0)) return -1;
	
	nmppsRandUniform(BITS, L0, maxSize);
	nmppsSet(BITS, G0, -1, maxSize/2 + 128);
	nmppsSet(BITS, G1, -1, maxSize/2 + 128);
	

	int dim = DIM(BITS);
	unsigned int crc = 0;
	for (int size = dim * 2; size<maxSize; size += dim * 2 * NMPP_MIN_REP)
	{
		nmppsSplitTmp(BITS, L0, G0, G1,size , L1);
		nmppsCrcAcc(BITS, G0,size/2 + 128, &crc);
		nmppsCrcAcc(BITS, G1,size/2 + 128, &crc);
	}
	
	dump(BITS, L0, 8,8);	printf("\n");
	dump(BITS, G0, 8,8);	printf("\n");
	dump(BITS, G1, 8,8);	printf("\n");

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);
	return crc>>2;
}

