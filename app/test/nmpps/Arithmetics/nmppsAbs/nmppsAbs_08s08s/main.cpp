#include "nmpp.h"
#include "minrep.h"
#include "minrep.h"
//#include "vSupport.h"
//

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
	//
	
	L0=nmppsMalloc_64s (SizeL0);
	G0=nmppsMalloc_64s (SizeG0);
	if (L0==0 || G0==0 ) return -1;
	
	unsigned int crc = 0;

	int	MaxCharSize=2048;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	//nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	//nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,SizeG0*2);

	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		nmppsAbs_8s((nm8s*)L0,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsAbs_8s(nm8s*,nm8s*,int)	

	
	nmppsFree(L0);
	nmppsFree(G0);
	
	
	
	return crc;
}
