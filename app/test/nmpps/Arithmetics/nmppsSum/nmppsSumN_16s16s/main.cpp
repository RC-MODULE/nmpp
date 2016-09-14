#include "nmpp.h"


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

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	shortMaxSize=2048;
	shortMaxSize=MIN(shortMaxSize,SizeL1*4);
	shortMaxSize=MIN(shortMaxSize,SizeG0*4);
	for(int i=0;i<100;i++)
		((nm32s*)L0)[i]=(int)nmppsAddr_16s((nm16s*)L1,i*4);
	
	nmppsRandUniform_64s((nm64s*)L1,SizeL1);
	nm64s val=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,val,(SizeG0));
	
	for(int nSize=64;nSize<shortMaxSize;nSize+=64)
	{
		int n=nmppcRandMinMax(2,99);
		nmppsSumN_16s((nm16s**)L0,(nm16s*)G0,nSize,n);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(nSize)+64,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSumN_16s(nm16s**,nm16s*,int,int)	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
