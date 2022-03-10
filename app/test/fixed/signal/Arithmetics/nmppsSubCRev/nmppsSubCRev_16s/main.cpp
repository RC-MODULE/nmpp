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

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	shortMaxSize=1024;
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeL0));
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s(c,(nm64s*)G0,(SizeG0));
	
	for(int nSize=0;nSize<=shortMaxSize;nSize+=4*NMPP_MIN_REP)
	{
		short nVal=nmppcRand();
		nmppsSubCRev_16s((nm16s*)L0,nVal,(nm16s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubCRev_16s(nm16s*,short,nm16s*,int)	

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;

}

