#include "nmpp.h"



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

	int	MaxIntSize=1024;
	MaxIntSize=MIN(MaxIntSize,SizeL0*8);
	MaxIntSize=MIN(MaxIntSize,SizeG0*8);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,(SizeG0*2));
	
	for(int size=1;size<128;size++)
	for(int stepSrc=1;stepSrc<5;stepSrc++)
	for(int stepDst=1;stepDst<5;stepDst++)
	{
		int32x2 MulN;
		MulN.lo=1;//nmppsRandUniform_();
		MulN.hi=2;//nmppsRandUniform_();
		
		int32x2 AddN;
		AddN.lo=3;//nmppsRandUniform_();
		AddN.hi=4;//nmppsRandUniform_();

		
		nmppsMulC_AddC_2x32s((int32x2*)L0,&MulN,&AddN,(int32x2*)G0,size,1,1);	
		nmppsCrc_64u((nm64u*)G0,size*5,&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
