#include "rpc-host.h"
#include "nmtype.h"

#ifndef RPC


void nmppmMul_mv_8s16s_8xH(
		v8nm8s*		pSrcMtr,
		v8nm16s*		pSrcVec,
			nm16s*		pDstVec,
			int			nHeight
		)

{
	nmmtr8s SrcMtr((nm8s*)pSrcMtr,nHeight,8);
	nmvec16s SrcVec((nm16s*)pSrcVec,8);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}

void nmppmMul_mv_16s16_8xH(
		v8nm16s*		pSrcMtr,
		v8nm16s*		pSrcVec,
			nm16s*		pDstVec,
			int			nHeight
		)

{
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,8);
	nmvec16s SrcVec((nm16s*)pSrcVec,8);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}


void nmppmMul_mv_64sc64sc( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int Height, int Width, void*tmp)
{
	int i,j;
	for(i=0;i<Height;i++)
	{
		pDstVec[i].re = 0;
		pDstVec[i].im = 0;
		for(j=0;j<Width;j++)
		{
//			if(IsMultOverflow(&pSrcMtr[i*Width+j].re, &pSrcVec[j].re))
//				printf("nmppmMul_mv_ overflow(r1, r2)\n");
			pDstVec[i].re += (pSrcMtr[i*Width+j].re * pSrcVec[j].re - pSrcMtr[i*Width+j].im * pSrcVec[j].im);
			pDstVec[i].im += (pSrcMtr[i*Width+j].re * pSrcVec[j].im + pSrcMtr[i*Width+j].im * pSrcVec[j].re);
		}
	}
}

void nmppmMul_mv__Zero( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int nStart, int nQuantity, int Height, int Width, void*tmp)
{
	int i,j;
	for(i=0;i<Height;i++)
	{
		pDstVec[i].re = 0;
		pDstVec[i].im = 0;
		for(j=0;j<nQuantity;j++)
		{
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].re, &pSrcVec[j].re))
//				printf("nmppmMul_mv__Zero overflow(r1, r2)\n");
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].im, &pSrcVec[j].im))
//				printf("nmppmMul_mv__Zero overflow(c1, c2)\n");
			pDstVec[i].re += (pSrcMtr[i*Width+j+nStart].re * pSrcVec[j].re - pSrcMtr[i*Width+j+nStart].im * pSrcVec[j].im);
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].re, &pSrcVec[j].im))
//				printf("nmppmMul_mv__Zero overflow(r1, c2)\n");
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].im, &pSrcVec[j].re))
//				printf("nmppmMul_mv__Zero overflow(c1, r2)\n");
			pDstVec[i].im += (pSrcMtr[i*Width+j+nStart].re * pSrcVec[j].im + pSrcMtr[i*Width+j+nStart].im * pSrcVec[j].re);
		}
	}
}

#endif