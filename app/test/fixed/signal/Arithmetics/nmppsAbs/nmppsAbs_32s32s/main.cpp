#include "nmpp.h"
#include "minrep.h"


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
	G0=nmppsMalloc_64s(SizeG0);

	
	if ((L0==0) || (G0==0)) return -1;
	


	unsigned int crc = 0;

	int	MaxIntSize=2048;
	MaxIntSize=MIN(MaxIntSize,SizeL0*2);
	MaxIntSize=MIN(MaxIntSize,SizeG0*2);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)G0,(SizeG0*2));

	for(int IntSize=0;IntSize<=MaxIntSize;IntSize+=2*NMPP_MIN_REP)
	{
		nmppsAbs_32s((nm32s*)L0,(nm32s*)G0,IntSize);	
		nmppsCrcAcc_32u((nm32u*)G0,IntSize+128,&crc);
	}
	//! \fn void nmppsAbs_32s(nm32s*,nm32s*,int)	

	nmppsFree(L0);
	nmppsFree(G0);
	
	

	return crc>>2;
}
