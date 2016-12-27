#include "nmpp.h"
#include "minrep.h"


//////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=10*KB;
const int SizeL1=10*KB;
                 
const int SizeG0=10*KB;
const int SizeG1=10*KB;

//! \fn void nmppsAddC_8s(nm8s*, char, nm8s*,int)
int main()
{
	
	
	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	
	int	MaxCharSize=1024;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	return 1;
	nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,(SizeG0*2));
	
	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		char nVal=nmppcRandMinMax(-128,127);
		nmppsAddC_8s((nm8s*)L0,nVal,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
