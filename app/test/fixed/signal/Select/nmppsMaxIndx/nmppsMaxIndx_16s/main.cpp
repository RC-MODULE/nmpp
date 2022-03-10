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

//! \fn void nmppsMaxIndx_16s(nm16s *, int, int&, int& , void *,void*, int)
int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;

	

	uint32b crc = 0;
	int		nMax;
	int 	nIndex;
	
	int maxSize=1024;//SizeL0*4;
	

	for(int fill=-2; fill<3; fill++){
		nmppsSet_16s(fill,(nm16s*)L0,maxSize);
		for(int val=-2; val<2; val++){
			for(int pos=0; pos<64; pos++){
				nmppsPut_16s((nm16s*)L0,pos,val);	
				//for(int size=64; size<maxSize; size+=64){
				for(int size=128; size<maxSize; size+=128){
				//for(int size=64; size<maxSize; size+=2*NMPP_MIN_REP){
					nmppsMaxIndx_16s((nm16s*)L0,size,&nIndex, &nMax,L1,G1,1);
					nmppsCrcAcc_32u((nm32u*)&nIndex,1,&crc);
					nmppsCrcAcc_32u((nm32u*)&nMax,1,&crc);
				}
			}
		}
	}

	for(int fill=-2; fill<3; fill++){
		nmppsSet_16s(fill,(nm16s*)L0,maxSize);
		for(int val=-2; val<2; val++){
			for(int pos=0; pos<64; pos++){
				nmppsPut_16s((nm16s*)L0,maxSize-1-pos,val);	
				//for(int size=64; size<maxSize; size+=64){
				for(int size=128; size<maxSize; size+=128){  // for NMPP_MIN_REP=32
					nmppsMaxIndx_16s((nm16s*)L0,size,&nIndex, &nMax,L1,G1,1);
					nmppsCrcAcc_32u((nm32u*)&nIndex,1,&crc);
					nmppsCrcAcc_32u((nm32u*)&nMax,1,&crc);
				}
			}
		}
	}
	
	
	
	
	for(int fill=-2; fill<3; fill++){
		nmppsRandUniform_64s((nm64s*)L0,maxSize/4);
		nmppsClipPowC_16s((nm16s*)L0,14,(nm16s*)L0,maxSize);
		for(int val=-2; val<2; val++){
			for(int pos=0; pos<64; pos++){
				nmppsPut_16s((nm16s*)L0,maxSize-1-pos,val);	
				//for(int size=64; size<maxSize; size+=64){
				for(int size=128; size<maxSize; size+=128){
					nmppsMaxIndx_16s((nm16s*)L0,size,&nIndex, &nMax,L1,G1,1);
					nmppsCrcAcc_32u((nm32u*)&nIndex,1,&crc);
					nmppsCrcAcc_32u((nm32u*)&nMax,1,&crc);
				}
			}
		}
	}
	
	
	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

