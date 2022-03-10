#include "nmpp.h"
#include "minrep.h"


/////////////////////////////////////////////////////////////////////////
nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
 int KB=1024/8;
 int SizeL0=60*KB;
 int SizeL1=60*KB;

 int SizeG0=60*KB;
 int SizeG1=60*KB;

//! \fn void nmppsRandUniform_64s(nm64s*,int,int)

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	longMaxSize=2048;
	longMaxSize=MIN(longMaxSize,LONG2long(SizeL0));
	nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)L0,(SizeL0*2));
	for(int nSize=0;nSize<=longMaxSize;nSize++)
	{
		nmppsRandUniform_64s((nm64s*)L0,nSize,nSize+1);	
		nmppsCrcAcc_32u((nm32u*)L0,MIN(long2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}
