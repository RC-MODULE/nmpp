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

//! \fn void nmppsMax_32s(nm32s*,int,int&)	
int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	maxSize=512;
	
	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsClipPowC_32s((nm32s*)L0,30,(nm32s*)L0,maxSize);

	int Max;
	
	for(int size=2;size<maxSize;size+=2){
		nmppsMax_32s31b((nm32s*)L0,size,&Max);	
		nmppsCrcAcc_32u((nm32u*)&Max,1,&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

