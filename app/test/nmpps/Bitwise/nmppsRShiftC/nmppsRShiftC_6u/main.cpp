#include "nmpp.h"



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

	int	shortTestSize=512;
	shortTestSize=MIN(shortTestSize,LONG2short(SizeL0));
	shortTestSize=MIN(shortTestSize,LONG2short(SizeG0));
	shortTestSize=MIN(shortTestSize,LONG2short(SizeL1));
	shortTestSize=MIN(shortTestSize,LONG2short(SizeG1));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	for(int Size=0;Size<=shortTestSize;Size+=4)
	{
		int Shift=nmppcRandMinMax(0,15);
		nmppsRShiftC_16u((nm16u*)L0,Shift,(nm16u*)G0,Size);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(Size)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsRShiftC_16u(nm16u*,int,nm16u*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

