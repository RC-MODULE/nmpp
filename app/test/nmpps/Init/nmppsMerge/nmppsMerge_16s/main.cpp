#include "nmpp.h"
#include "minrep.h"
#include "test.h"


#define xnmppsMerge(bits,src0,src1,dst,size)  nmppsMerge_##bits##s(src0,src1,dst,size)
#define  nmppsMerge(bits,src0,src1,dst,size) xnmppsMerge(bits,src0,src1,dst,size)

#define BITS 16

int main()
{
	int maxSize = 1024;
	NM_TYPE(BITS) *L0 = nmppsMalloc(BITS, maxSize/2);
	NM_TYPE(BITS) *L1 = nmppsMalloc(BITS, maxSize/2);
	NM_TYPE(BITS) *G0 = nmppsMalloc(BITS, maxSize+128);
	
	if ((L0==0)||(L1==0)||(G0==0)) return -1;
	
	nmppsRandUniform(BITS, L0, maxSize/2);
	nmppsRandUniform(BITS, L1, maxSize/2);
	nmppsSet(BITS, G0, -1, maxSize + 128);
	

	int dim = DIM(BITS);
	unsigned int crc = 0;
	for(int size=dim; size<maxSize/2; size+=dim*NMPP_MIN_REP)
	{
		nmppsMerge (BITS, L0,L1,G0,  size);
		nmppsCrcAcc(BITS, G0,2*size + 128, &crc);
		
	}
		
	dump(BITS, L0, 8,8);	printf("\n");
	dump(BITS, L1, 8,8);	printf("\n");
	dump(BITS, G0, 8,16);	printf("\n");

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	return crc>>2;
}

