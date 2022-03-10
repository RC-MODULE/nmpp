#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


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
{  int nSize;
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;

    
	unsigned int crc = 0;
	int index;
	
	
	//-------------------------------------
	for(int size=2*NMPP_MIN_REP;size<1024; size+=2*NMPP_MIN_REP){
		//int size=1024;
		nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)L0,size);
		//nmppsSet_32s((int)0,(nm32s*)L0,size);
		//nmppsPut_32u((nm32u*)L0,size-1,1);	
		for(int nonZeroPos=0; nonZeroPos<size; nonZeroPos++){
			index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,size);	
			//printf("%d %d\n",nonZeroPos,index);
			if (index!=nonZeroPos)
				return -1;
			nmppsPut_32u((nm32u*)L0,nonZeroPos,0);	
		}
		index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,size);	
		if (index!=-1)
			return -2;
		
		for(int nonZeroPos=size-1; nonZeroPos>=0; nonZeroPos--){
			nmppsPut_32u((nm32u*)L0,nonZeroPos,1);	
			index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,size);	
			//printf("%d %d\n",nonZeroPos,index);
			if (index!=nonZeroPos)
				return -1;
		}
	}
		
			
			//if (index!=zeroPos)
			//	return -1;

		//}
		//index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,size);	
		//nmppsPut_32u((nm32u*)L0,zeroPos,0);	
		
	//}
		
//			 
//		
//		nmppsCrcAcc_32u((nm32u*)&index,1,&crc);
//		
//		index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,2);
//		nmppsCrcAcc_32u((nm32u*)&index,1,&crc);
//		
//		index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,3);
//		nmppsCrcAcc_32u((nm32u*)&index,1,&crc);
//	}
//	//-------------------------------------
//	for(int indx=0;indx<4;indx++){
//		nmppsSet_32u(0,(nm32u*)L0,4);
//		nmppsPut_32s((nm32s*)L0,indx,1);
//		index=nmppsFirstNonZeroIndx_32s((nm32s*)L0,3);
//		nmppsCrcAcc_32u((nm32u*)&index,1,&crc);
//	}
	
	
	//for( nSize=1;nSize<=1024;nSize++)
	//{
	//	nmppsFirstNonZeroIndex_32s((nm32s*)L0+nSize,nSize);
	//	nmppsCrcAcc_32u((nm32u*)G0,64,&crc);
	//}
	//! \fn int nmppsFirstNonZeroPos_(int*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}