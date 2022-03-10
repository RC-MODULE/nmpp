#include "nmpp.h"
#include "minrep.h"



/////////////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=30*KB;
const int SizeL1=30*KB;

const int SizeG0=30*KB;
const int SizeG1=30*KB;

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	TestSize=512;
	TestSize=MIN(TestSize,SizeL0*8);
	TestSize=MIN(TestSize,SizeG0*4);

	nmppsRandUniform_32u((nm32u*)L0,TestSize);
	nmppsSet_32s(int(0xCCCCCCCC),(nm32s*)G0,SizeG0);
	for(int size=2;size<TestSize;size+=2)
	{
		nm64s nVal =-32768;
		for(int i=0;i<10;i++)
		{
			nVal+=10000;
			nmppsMulC_32s64s((nm32s*)L0,nVal,(nm64s*)G0,size);	
			nmppsCrcAcc_32u((nm32u*)G0,size*2+66,&crc);
		}
	}
	//! \fn void nmppsMulC_32s(nm32s* pSrc,nm64s,nm64s* pDst,int)	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
