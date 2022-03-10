#include "nmpp.h"
#include "minrep.h"



///////////////////////////////////////////////////
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
	int	intTestSize=2048;
	intTestSize=MIN(intTestSize,LONG2int(SizeL0));
	intTestSize=MIN(intTestSize,LONG2int(SizeG0));
	intTestSize=MIN(intTestSize,LONG2int(SizeL1));
	intTestSize=MIN(intTestSize,LONG2int(SizeG1));

	//nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	//nmppsInitConst_32s((nm32s*)L0,SizeL0*2,4095);
//	nmppsRShiftC_32s((nm32s*)L0,24,(nm32s*)L0,SizeL0*2);
/*
	for(int j=0,i=-4095;i<4096;i++, j++)
	{
		int c=nmppcRandMinMax(0,
 1);
		if(!c)
			c=-1;
		((nm32s*)L0)[j]=i*c;
	}
*/
	for(int j=0,i=-intTestSize/2+1;i<=intTestSize/2;i++, j++)
	{
		((nm32s*)L0)[j]=i;
	}
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s(c,(nm64s*)G0,(SizeG0));

	int nSize=152;
	for(int nSize=0;nSize<=intTestSize ;nSize+=2*NMPP_MIN_REP)
		for(int Divisor=1;Divisor<=145;Divisor++)
		{
			nmppsDivC_32s((nm32s*)L0,Divisor,(nm32s*)G0,nSize,L1,G1);	
			nmppsCrcAcc_32u((nm32u*)G0,MIN(char2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
		}
	//! \fn void nmppsDivC_32s(nm32s*,int,nm32s*,int,void*,void*)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
