#include "nmpp.h"
#include "minrep.h"


/////////////////////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=30*KB;
const int SizeL1=30*KB;

const int SizeG0=30*KB;
const int SizeG1=30*KB;

#ifndef NM6405
	#define malloc1 malloc
	#define malloc2 malloc
	#define malloc3 malloc
#endif


int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;
	int	charMaxSize=4096;
	charMaxSize=MIN(charMaxSize,LONG2char(SizeL1));
	charMaxSize=MIN(charMaxSize,LONG2char(SizeG0)/2);

	for(int i=0;i<100;i++)
		((nm32s*)L0)[i]=(int)nmppsAddr_8s((nm8s*)L1,i*8);
	nmppsRandUniform_64s((nm64s*)L1,SizeL1);
	nm64s Fill=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s(Fill,(nm64s*)G0,(SizeG0));
	
	for(int nSize=32*8;nSize<=charMaxSize;nSize+=32*8)
	{
		int n=nmppcRandMinMax(2,100);
		nmppsSumN_8s16s((nm8s**)L0,(nm16s*)G0,nSize,n);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSumN_8s(nm8s**,nm16s*,int,int)	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
