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

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int *pL0=(int*)L0; 
	int *pG0=(int*)G0;
	int	longTestSize=4*2048;
	longTestSize=MIN(longTestSize,SizeL0);
	longTestSize=MIN(longTestSize,SizeG0);

	nmppsRandUniform_64s(L0,SizeL0);
	nmppsSet_64s(G0,-1,SizeG0);
	
	for(int nSize=64*32;nSize<longTestSize;nSize+=64*32)
	{
		nmppsConvert_1s2s((nm1*)L0,(nm2s*)G0,nSize);
		nmppsCrcAcc_32u((nm32u*)G0,(nSize)/64*2,&crc);
	}
	//! \fn void nmppsConvert_1*(nm1* pSrc,nm2s* pDst,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

