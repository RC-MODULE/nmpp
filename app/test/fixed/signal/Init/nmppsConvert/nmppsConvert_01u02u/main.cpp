#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


/////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
 int KB=1024/8;
 int SizeL0=30*KB;
 int SizeL1=30*KB;
 int SizeG0=30*KB;
 int SizeG1=30*KB;

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0+1);
	L1=nmppsMalloc_64s(SizeL1+1);
	G0=nmppsMalloc_64s(SizeG0+1);
	G1=nmppsMalloc_64s(SizeG1+1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int *pL0=(int*)L0;
	int *pG0=(int*)G0;
	int	longTestSize=4*2048;
	longTestSize=MIN(longTestSize,SizeL0);
	longTestSize=MIN(longTestSize,SizeG0);

	nmppsRandUniform_32u((nm32u*)L0,LONG2INT(SizeL0));
	nmppsSet_32u((0xCCCCCCCC),(nm32u*)G0,(LONG2INT(SizeG0))+2);
	
	for(int nSize=0;nSize<=longTestSize;nSize+=64)
	{
		nmppsConvert_1u2u((nm1*)L0,(nm2u*)G0,nSize);
		nmppsCrcAcc_32u((nm32u*)G0,(nSize)/16+2,&crc);
	}
	//! \fn void nmppsConvert_1*(nm1*pSrc ,nm2u* pDst,int)
	//printf ("0x%x\n",G0[longTestSize/32-1]+2);
	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

