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

	int	longTestSize=128;
	longTestSize=MIN(longTestSize,LONG2long(SizeL0));
	longTestSize=MIN(longTestSize,LONG2long(SizeG0));
	longTestSize=MIN(longTestSize,LONG2long(SizeL1));
	longTestSize=MIN(longTestSize,LONG2long(SizeG1));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	for(int Size=0;Size<=longTestSize;Size+=2)
	{
 		int Shift=nmppcRandMinMax(0,63);
		nmppsRShiftC_64u((nm64u*)L0,Shift,(nm64u*)G0,Size);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(long2INT(Size)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsRShiftC_64u(nm64u*,int,nm64u*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

