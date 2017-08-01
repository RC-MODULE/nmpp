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

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	MaxLongSize=1024;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0);
	nmppsRandUniform_32u((nm32u*)L1,SizeL1);
	nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,(SizeG0*2));
	
	for(int LongSize=0;LongSize<=MaxLongSize/3;LongSize+=NMPP_MIN_REP)
	{
		nmppsAddEx_64s((nm64s*)L0,3,(nm64s*)L1,2,(nm64s*)G0,1,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsAdd_64s(nm64s*,nm64s*,nm64s*,int)	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
