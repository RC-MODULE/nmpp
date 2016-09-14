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

//! \fn void nmppsRShiftC_32s(nm32s*,int,nm32s*,int)

int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	MaxIntSize=256;
	MaxIntSize=MIN(MaxIntSize,SizeL0/2);
	MaxIntSize=MIN(MaxIntSize,SizeG0/2);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)L0,MaxIntSize);

	for(int shift=0;shift<32;shift++)
	
		for(int IntSize=0;IntSize<MaxIntSize;IntSize+=2)
		{
			nmppsRShiftC_32s((nm32s*)	L0,			// Input array 					:long Global[NumbersOfPairs*SrcPairReadStep/2]
				shift,				// Numbers of input pairs should be quantized: =[1,2,3...]
				(nm32s*)	G0,			// Output qunatized array		:long Local [NumbersOfPairs*DstPairWriteStep/2]
				IntSize);			// Array of two quantizers		:long Local [2/2]; PairOfQuantizers[0,1]=[1,2,3...128]
			nmppsCrcAcc_32u((nm32u*)G0,IntSize,&crc);
	
		}

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;
}

