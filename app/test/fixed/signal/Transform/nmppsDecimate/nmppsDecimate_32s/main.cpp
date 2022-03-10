#include "nmpp.h"
#include "time.h"
#include "test.h"

#define MAX_SIZE 1024
#define STEP 4

#define xnmppsDecimate(bits,src0,pose,step,dst,size)  nmppsDecimate_##bits##s(src0,pose,step,dst,size)
#define  nmppsDecimate(bits,src0,pose,step,dst,size) xnmppsDecimate(bits,src0,pose,step,dst,size)

#define BITS 32

int main (){
	NM_TYPE(BITS) *L0 = nmppsMalloc(BITS, MAX_SIZE*STEP);
	NM_TYPE(BITS) *G0 = nmppsMalloc(BITS, MAX_SIZE+128);
	
	nmppsSet(BITS,G0,0xCDCDCDCD,MAX_SIZE+128);
	if(L0==0 || G0==0)
		return 0xDEADB00F;
	
	nmppsRandUniform(BITS,L0,MAX_SIZE*STEP);
	
	//dump(32,src, 8, STEP);
	int dim = DIM(BITS);

	clock_t t1,t0;
	unsigned crc = 0;
	
	for (int startPos=0;startPos<dim;startPos++){
		for (int size =0;size<=MAX_SIZE;size+=dim){
			t0 = clock();
			nmppsDecimate(BITS, L0, 0, STEP, G0, size);
			t1 = clock();
			nmppsCrcAcc(BITS,G0,size+128,&crc);
		}	
	}
	
	//printf("\n");
	//dump(32,dst, 8, 1);
	
	return crc>>2;
	//return t1-t0;
	
}