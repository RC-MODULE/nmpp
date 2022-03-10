#include "nmpp.h"
#include "minrep.h"



/////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
 int KB=1024/8/2;
 int SizeL0=60*KB;
 int SizeL1=60*KB;

 int SizeG0=60*KB;
 int SizeG1=60*KB;

//! \fn void nmppsConvert_8u(nm8u* pSrc,nm64u* pDst,int)
int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	charTestSize=2048;
	charTestSize=MIN(charTestSize,LONG2char(SizeL0));
	charTestSize=MIN(charTestSize,LONG2char(SizeG0));

	nmppsRandUniform_32u((nm32u*)L0,LONG2INT(SizeL0));
	nmppsSet_32u((0xCCCCCCCC),(nm32u*)G0,(LONG2INT(SizeG0)));
	for(int nSize=0;nSize<charTestSize;nSize+=8*NMPP_MIN_REP)
	{
		nmppsConvert_8u64u(( nm8u*)L0,(nm64u*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(long2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

