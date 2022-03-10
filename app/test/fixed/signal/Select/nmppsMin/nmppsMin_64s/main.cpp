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

//! \fn void nmppsMin_64s(nm64s*,int,int&)	
int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	maxSize=SizeL0;
	nm64u nMask=0x7FFFFFFFFFFFFFFFl;
	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsAndC_64u((nm64u*)L0,nMask,(nm64u*)L0,maxSize);
	//nmppsClipPowC_64s((nm64s*)L0,30,(nm32s*)L0,LONG2int(SizeL0));

	int64b Min;
	
	for(int size=1;size<maxSize;size++){
		nmppsMin_64s63b((nm64s*)L0,size,&Min);	
		nmppsCrcAcc_32u((nm32u*)&Min,2,&crc);
	}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

