
#include "nmpp.h"


/////////////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=20*KB;
const int SizeL1=20*KB;
                 
const int SizeG0=20*KB;
const int SizeG1=20*KB;

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	//G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)) return -1;


	unsigned int crc = 0;

	int	TestSize=512;
	TestSize=MIN(TestSize,SizeL0*4);
	TestSize=MIN(TestSize,SizeG0*4);
	nmppsSet_64s((nm64s*)G0,0xCCCCCCCCCCCCCCCC,SizeG0);
	nmppsRandUniform_64u((nm64u*)L0,SizeL0);
	int64b ret64;

	
	for(int size=4;size<TestSize;size+=4){
		nmppsDotProd_16s16sm((nm16s*)L0,(nm16s*)G0,size,&ret64,L1);	
		nmppsCrcAcc_32u((nm32u*)&ret64,2,&crc);
	}
	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	//nmppsFree(G1);

	

	return crc>>2;
}
