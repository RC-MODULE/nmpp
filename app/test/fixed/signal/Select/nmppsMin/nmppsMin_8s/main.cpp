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

//! \fn void nmppsMin_8s(nm8s*,int, char&)	

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	maxSize=1024;
	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	int8b Min;

	for (int pow=6;pow>=1; pow--){
		nmppsClipPowC_8s((nm8s*)L0,pow,(nm8s*)L0,maxSize);
		for(int size=8;size<maxSize;size+=8*NMPP_MIN_REP){
			nmppsMin_8s7b((nm8s*)L0,size,&Min);	
			nmppsCrcAcc_32u((nm32u*)&Min,1,&crc);
		}
	}

	
	
	for(int i=0; i<127; i++){
		nmppsSet_8s(0,(nm8s*)L0,maxSize);
		for(int k=0; k<i; k++){
			nmppsPut_8s((nm8s*)L0,k,-3);
		}
		for(int size=8;size<maxSize;size+=24){
			nmppsMin_8s7b((nm8s*)L0,size,&Min);	
			nmppsCrcAcc_32u((nm32u*)&Min,1,&crc);
		}
	}
	
	for(int i=0; i<127; i++){
		nmppsSet_8s(0,(nm8s*)L0,maxSize);
		for(int k=0; k<i; k++){
			nmppsPut_8s((nm8s*)L0,k,+3);
		}
		for(int size=8;size<maxSize;size+=24){
			nmppsMin_8s7b((nm8s*)L0,size,&Min);	
			nmppsCrcAcc_32u((nm32u*)&Min,1,&crc);
		}
	}
	
	for(int i=0; i<127; i++){
		nmppsSet_8s(0,(nm8s*)L0,maxSize);
		for(int k=0; k<i; k++){
			nmppsPut_8s((nm8s*)L0,maxSize-k-1,-3);
		}
		for(int size=8;size<maxSize;size+=24){
			nmppsMin_8s7b((nm8s*)L0,size,&Min);	
			nmppsCrcAcc_32u((nm32u*)&Min,1,&crc);
		}
	}
	
	for(int i=0; i<127; i++){
		nmppsSet_8s(0,(nm8s*)L0,maxSize);
		for(int k=0; k<i; k++){
			nmppsPut_8s((nm8s*)L0,maxSize-k-1,+3);
		}
		for(int size=8;size<maxSize;size+=24){
			nmppsMin_8s7b((nm8s*)L0,size,&Min);	
			nmppsCrcAcc_32u((nm32u*)&Min,1,&crc);
		}
	}


	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

