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

#ifdef NM6403
long MTRtmpArray;
#endif


//////////////////////////////////////////////
int main()
{
	
 
	unsigned int crc = 0;



	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;

#ifdef NM6403
	nm64s o=0x0L;
	nmppsSet_64s(&o,(nm64s*)G1,(SizeG1));
	MTRtmpArray=(int)G1;
#endif



	int	MaxLongSize=2*1024;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsRandUniform_64s((nm64s*)L1,SizeL1);

	nm64s c=0xAAAAAAAACCCCCCCCL;
	nmppsSet_64s(c,(nm64s*)G0,(SizeG0));
 
	
	for(int LongSize=0;LongSize<=MaxLongSize/2;LongSize+=(NMPP_MIN_REP+1)/2)
	{
		nmppsSub_64sc((nm64sc*)L0,(nm64sc*)L1,(nm64sc*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*4+128,SizeG0*4),&crc);
	}
	//! \fn void nmppsSub_64sc(nm64sc*,nm64sc*,nm64sc*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	


	return crc>>2;


}
