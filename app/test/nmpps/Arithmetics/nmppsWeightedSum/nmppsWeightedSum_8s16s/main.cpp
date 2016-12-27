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

    int	MaxnSize=1024;
	int nW1, nW2;
	
	unsigned int crc = 0;

	MaxnSize=MIN(MaxnSize,SizeL0*8);
	MaxnSize=MIN(MaxnSize,SizeG0*8);

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	nmppsRandUniform_32u((nm32u*)L1,SizeL0*2);

	nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,SizeG0*2);
	
	for(int nSize=0;nSize<=MaxnSize;nSize+=8*NMPP_MIN_REP)
	{
		nW1=nmppcRandMinMax(-128,127);
		nW2=nmppcRandMinMax(-128,127);
	   
		nmppsWeightedSum_8s16s((nm8s*)L0,nW1,(nm8s*)L1,nW2,(nm16s*)G0,nSize);
		nmppsCrcAcc_32u((nm32u*)G0,nSize/4+128,&crc);
	}
	//! \fn void nmppsWeightedSum_8s(nm8s* pSrcVec1,int nW1,nm8s* pSrcVec2,int nW2, nm16s* pDstVec, int nSize);

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
