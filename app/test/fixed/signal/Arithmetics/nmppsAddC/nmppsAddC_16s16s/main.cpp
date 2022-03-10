#include "nmpp.h"
#include "minrep.h"


//////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=30*KB;
const int SizeL1=30*KB;

const int SizeG0=30*KB;
const int SizeG1=30*KB;

//! \fn void nmppsAddC_16s(nm16s*,short,nm16s*,int)	

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	MaxShortSize=1024;
	MaxShortSize=MIN(MaxShortSize,SizeL0*4);
	MaxShortSize=MIN(MaxShortSize,SizeG0*4);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)G0,(SizeG0*2));
	
	for(int ShortSize=0;ShortSize<=MaxShortSize;ShortSize+=4*NMPP_MIN_REP)
	{
		short nVal=nmppcRandMinMax(-255*255,255*255);
		nmppsAddC_16s((nm16s*)L0,nVal,(nm16s*)G0,ShortSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(ShortSize/2+128,SizeG0*2),&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
