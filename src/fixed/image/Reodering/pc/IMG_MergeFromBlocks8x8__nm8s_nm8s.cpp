#include "nmtl.h"
#include "nmtype.h"

extern "C" {
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nmppiMergeFromBlocks8x8(
		nm8s*	pSrcBlockSeq,	// Source one-dimensional Array	:long Local[Width*Height/8]
			nm8s*	pDstImg,	// Result Image					:long Global[Width*Height/8]
			int		nWidth,	// Source Image Width;			:Width=[8,16,24...]
			int		nHeight	// Source Image Height;			:Height=[8,16,24..]
			)
{
	int idx=0;
	char *src=(char*)pSrcBlockSeq;
	char *dst=(char*)pDstImg;
	char *Block;
	for(int row=0;row<nHeight;row+=8)
		for(int col=0;col<nWidth;col+=8)
		{
			Block=dst+row*nWidth+col;
			for(int r=0;r<8;r++)
			{
				for(int c=0;c<8;c++)
					Block[c]=src[idx++];
				Block+=nWidth;
			}
		}

}
};
