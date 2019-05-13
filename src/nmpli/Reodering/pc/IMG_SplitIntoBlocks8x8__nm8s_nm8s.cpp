#include "nmtl.h"
#include "nmtype.h"

extern "C" {
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nmppiSplitIntoBlocks8x8(
		nm8s*	pSrcImg,	// Source Image						:long Local[Width*Height/8]
			nm8s*	pDstBlockSeq,	// Result one-dimensional Array:	:long Global[Width*Heihgt/8]
			int		nWidth,	// Source Image Width;				:Width =[8,16,24...]
			int		nHeight	// Source Image Height;				:Height=[8,16,24...]
			)
{
	int idx=0;
	char *src=(char*)pSrcImg;
	char *dst=(char*)pDstBlockSeq;
	char *Block;
	for(int row=0;row<nHeight;row+=8)
		for(int col=0;col<nWidth;col+=8)
		{
			Block=src+row*nWidth+col;
			for(int r=0;r<8;r++)
			{
				for(int c=0;c<8;c++)
					dst[idx++]=Block[c];
				Block+=nWidth;
			}
		}

}
};
