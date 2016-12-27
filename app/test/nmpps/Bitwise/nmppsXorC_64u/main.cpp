#include "nmpp.h"
#include "minrep.h"



///////////////////////////////////////////////////////////////////////////////////////
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

	nmppsRandUniform_32u((nm32u*)L0,SizeL0*2);
	nmppsSet_32s((nm32s*)G0,(int)0xCCCCCCCC,(SizeG0*2));

	union
	{
		nm64u	Bits;
		int		Int[2];
	} Mask;

	
	for(int LongSize=0;LongSize<=MaxLongSize;LongSize+=NMPP_MIN_REP)
	{
		Mask.Int[0]=nmppcRand();
		Mask.Int[1]=nmppcRand();
		
		nmppsXorC_64u((nm64u*)L0,Mask.Bits,(nm64u*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize+128,SizeG0),&crc);
	}
	//! \fn void nmppsXorC_64u(nm64u*,nm64u*,nm64u*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
