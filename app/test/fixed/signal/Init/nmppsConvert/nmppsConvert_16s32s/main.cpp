#include "nmpp.h"
#include "minrep.h"



/////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
 int KB=1024/8;
 int SizeL0=60*KB;
 int SizeL1=60*KB;

 int SizeG0=60*KB;
 int SizeG1=60*KB;

//! \fn void nmppsConvert_16s(nm16s* pSrc,nm32s* pDst,int)

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	shortTestSize=2048;
	shortTestSize=MIN(shortTestSize,LONG2short(SizeL0));
	shortTestSize=MIN(shortTestSize,LONG2short(SizeG0));

	nmppsRandUniform_32u((nm32u*)L0,LONG2INT(SizeL0));
	nmppsSet_32u((0xCCCCCCCC),(nm32u*)G0,(LONG2INT(SizeG0)));
	for(int nSize=0;nSize<shortTestSize;nSize+=4*NMPP_MIN_REP)
	{
		nmppsConvert_16s32s(( nm16s*)L0,(nm32s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(int2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

