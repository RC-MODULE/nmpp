#include "nmtl.h"
#include "nmtype.h"
#include "nmpp.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
void IMG_SplitInto2x2Blocks8x8xor(
							nm8u*	pSrcImg,	
							nm8u*	pDstBlockSeq,
							nm8u*	pXorMask,
							int		nWidth,	
							int		nHeight	
							)
{
	unsigned char *src=(unsigned char*)pSrcImg;
	unsigned char *dst=(unsigned char*)pDstBlockSeq;
	
	for(int row=0;row<nHeight;row+=16){
		for(int col=0;col<nWidth;col+=16){
			mtr<unsigned char> m0(src+row*nWidth+col,8,8,nWidth);
			mtr<unsigned char> m1(src+row*nWidth+col+8,8,8,nWidth);
			mtr<unsigned char> m2(src+(row+8)*nWidth+col,8,8,nWidth);
			mtr<unsigned char> m3(src+(row+8)*nWidth+col+8,8,8,nWidth);
			
			mtr<unsigned char> n0(dst,8,8); dst+=64;
			mtr<unsigned char> n1(dst,8,8); dst+=64;
			mtr<unsigned char> n2(dst,8,8); dst+=64;
			mtr<unsigned char> n3(dst,8,8); dst+=64;
			
			n0=m0;
			n1=m1;
			n2=m2;
			n3=m3;
		}
	}
	nmppsXorC_64u((nm64u*)pDstBlockSeq,(nm64u*)pXorMask,(nm64u*)pDstBlockSeq,nWidth*nHeight/8);
}
