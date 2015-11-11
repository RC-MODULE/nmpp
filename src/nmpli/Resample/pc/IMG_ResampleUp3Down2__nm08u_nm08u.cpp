#include "nmpli.h"
#include "nmpls.h"
#include "nmtl.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
static double PolyphaseFilter3div2[3*4*2+1] = {     
		 0,
   -0.0057,
   -0.0062,
         0,
    0.0323,
    0.0367,
		 0,
   -0.1120,
   -0.1394,
		 0,
    0.3983,
    0.7956,
    1.0000,
    0.7956,
    0.3983,
		 0,
   -0.1394,
   -0.1120,
		 0,
    0.0367,
    0.0323,
         0,
   -0.0062,
   -0.0057,
		 0
};

static double PolyphaseFilter5div4[5*4*2+1] = {     
         0,
   -0.0038,
   -0.0063,
   -0.0066,
   -0.0044,
         0,
    0.0212,
    0.0362,
    0.0391,
    0.0266,
		 0,
   -0.0713,
   -0.1276,
   -0.1455,
   -0.1061,
		 0,
    0.2279,
    0.4844,
    0.7260,
    0.9096,
    1.0000,
    0.9096,
    0.7260,
    0.4844,
    0.2279,
		 0,
   -0.1061,
   -0.1455,
   -0.1276,
   -0.0713,
		 0,
    0.0266,
    0.0391,
    0.0362,
    0.0212,
         0,
   -0.0044,
   -0.0066,
   -0.0063,
   -0.0038,
         0
};

void MakeResample3div2TblFiles()
{
	
//	mtr<double>	tblDCT_left (ptblDCT_left,8,8);	
//	mtr<double>	tblDCT_right(ptblDCT_right,8,8);	
//	mtr<double>	tblIDCT_left(ptblIDCT_left,8,8);	
//	mtr<double>	tblIDCT_right(ptblIDCT_right,8,8);
//
//	nmmtr64s	packed_tblDCT_left_8   ((nm64s*)ptblDCT_left_8,8,1);
//	nmmtr64s	packed_tblDCT_right_32 ((nm64s*)ptblDCT_right_32,8,4);
//	nmmtr64s	packed_tblIDCT_left_8  ((nm64s*)ptblIDCT_left_8,8,1);
//	nmmtr64s	packed_tblIDCT_right_32((nm64s*)ptblIDCT_right_32,8,4);
//
//	nmmtr64s	repacked_tblDCT_right_32(4,8);
//	nmmtr64s	repacked_tblIDCT_right_32(4,8);
//
//
//	repacked_tblDCT_right_32=packed_tblDCT_right_32.transpose();
//	repacked_tblIDCT_right_32=packed_tblIDCT_right_32.transpose();
//
//	ofstream fout_asm("DctTable.asm");
//	fout_asm << "global DCT_Right: ";
//	AsmArray(fout_asm,repacked_tblDCT_right_32);
//
//	fout_asm << "global DCT_Left: ";
//	AsmArray(fout_asm,packed_tblDCT_left_8);
//
//	fout_asm << "global IDCT_Right: ";
//	AsmArray(fout_asm,repacked_tblIDCT_right_32);
//
//	fout_asm << "global IDCT_Left: ";
//	AsmArray(fout_asm,packed_tblIDCT_left_8);
//
//
//	ofstream fout_cpp("fDctTable.cpp");
//
//	fout_cpp << "double tblDCT_left[8][8]=" << tblDCT_left;
//	fout_cpp << "double tblDCT_right[8][8]=" << tblDCT_left;
}


void IMG_VResample3div2_RShift0(nm16s* pSrcImg, int nWidth, int nHeight, nm16s* pDstImg)
{
	int nSize=nHeight*nWidth;
	nmvec16s vKernel(25);						// Filter kernel
	nmmtr16s mSrc(pSrcImg,nHeight,nWidth);		// Source image
	nmmtr16s mDst(pDstImg,nHeight*3/2,nWidth);	// Result image
	nmmtr16s mSrcUpsample(nHeight*3,nWidth,30);	// Resampled vSrc by 5 times
	nmmtr16s mDstUpsample(nHeight*3,nWidth);	// Filtered vSrcUpsample
	int i,j,y,x;

		// Filxed point coefficient initialization
	for(i=0;i<25;i++)
	{
		vKernel[i]=floor(PolyphaseFilter3div2[i]*64+0.5);
	}
//	for(i=0;i<10;i++)
//	{
//		vKernel[i]=0;
//		vKernel[24-i]=0;
//	}
//	vKernel[10]=21;
//	vKernel[11]=43;
//	vKernel[13]=43;
//	vKernel[14]=21;
//	vKernel[10]=0;
//	vKernel[11]=64;
//	vKernel[13]=64;
//	vKernel[14]=0;



		// Resampling by 5 times
	mSrcUpsample.reset();
	for(y=0;y<nHeight;y++)
	{
		nmvec16s vSrcUpsample(mSrcUpsample.addr(y*3,0),mSrcUpsample.m_width);
		nmvec16s vSrc(mSrc.addr(y,0),mSrc.m_width);
		vSrcUpsample=vSrc;
		//mSrcUpsample.GetVec(y*3)=mSrc.GetVec(y);
	}

		// Filtration
	for(y=0;y<nHeight*3;y++)
		for(x=0;x<nWidth;x++)
		{
			nmint16s nDotMul(0);
			for(i=0;i<25;i++)
				nDotMul+=mSrcUpsample[y-25/2+i][x]*vKernel[i];
			mDstUpsample[y][x]=nDotMul;
		}

		// Decimation by 2
	for(y=0,i=0;y<nHeight*3;y+=2,i++)
	{
		nmvec16s vDstUpsample(mDstUpsample.addr(y,0),mDstUpsample.m_width);
		nmvec16s vDst(mDst.addr(i,0),mDst.m_width);
		vDst=vDstUpsample;
		//mDst.GetVec(i)=mDstUpsample.GetVec(y);
	}
}

void IMG_ResampleUp3Down2(nm8u* pSrcImg,int nSrcWidth, int nSrcHeight, nm8u* pDstImg, nm64s* pKernel, void* pTmp)
{
	int nSrcSize=nSrcWidth*nSrcHeight;
	nm8s*  pSrc8s;
	nm16s* pHResample16s;
	nm16s* pVResample16s;
	nmppsMalloc_8s(&pSrc8s,nSrcSize+100,0);
	nmppsMalloc_16s(&pHResample16s,nSrcSize*3/2+nSrcWidth*100,0);
	nmppsMalloc_16s(&pVResample16s,nSrcSize*3*3/2/2+nSrcWidth*100,0);

	nmppsSubC_8s((nm8s*)pSrcImg,char(128),(nm8s*)pSrc8s,nSrcSize);
	SIG_ResampleUp3Down2((nm8s*)pSrc8s,pHResample16s+nSrcWidth*50,nSrcSize,pKernel);
	nmppsRShiftC_16s(pHResample16s+nSrcWidth*50,6,pHResample16s+nSrcWidth*50,nSrcSize*3/2);
	IMG_VResample3div2_RShift0(pHResample16s+nSrcWidth*50,nSrcWidth*3/2,nSrcHeight,pVResample16s+nSrcWidth*50);
	nmppsClipRShiftConvert_AddC_16s(pVResample16s+nSrcWidth*50, 6+7,6,128,(nm8s*)pDstImg, nSrcSize*3*3/2/2);
	
	nmppsFree(pKernel);
	nmppsFree(pVResample16s);
	nmppsFree(pHResample16s);
	nmppsFree(pSrc8s);
	
}

//void IMG_VResample5div4_RShift0(nm16s* pSrcImg, int nWidth, int nHeight, nm16s* pDstImg)
//{
//	int nSize=nHeight*nWidth;
//	nmvec16s vKernel(41);						// Filter kernel
//	nmmtr16s mSrc(pSrcImg,nHeight,nWidth);		// Source image
//	nmmtr16s mDst(pDstImg,nHeight*5/4,nWidth);	// Result image
//	nmmtr16s mSrcUpsample(nHeight*5,nWidth,30);	// Resampled vSrc by 5 times
//	nmmtr16s mDstUpsample(nHeight*5,nWidth);	// Filtered vSrcUpsample
//	int i,j,y,x;
//
//		// Filxed point coefficient initialization
//	for(i=0;i<41;i++)
//	{
//		vKernel[i]=floor(PolyphaseFilter5div4[i]*64+0.5);
//	}
//
//		// Resampling by 5 times
//	mSrcUpsample.reset();
//	for(y=0;y<nHeight;y++)
//	{
//		mSrcUpsample.GetVec(y*5)=mSrc.GetVec(y);
//	}
//
//		// Filtration
//	for(y=0;y<nHeight*5;y++)
//		for(x=0;x<nWidth;x++)
//		{
//			nmint16s nDotMul(0);
//			for(i=0;i<41;i++)
//				nDotMul+=mSrcUpsample[y-41/2+i][x]*vKernel[i];
//			mDstUpsample[y][x]=nDotMul;
//		}
//
//		// Decimation by 4
//	for(y=0,i=0;y<nHeight*5;y+=4,i++)
//	{
//		mDst.GetVec(i)=mDstUpsample.GetVec(y);
//	}
//}
//

//
//
//IMG_Resample5div4(nm8u* pSrcImg,int nSrcWidth, int nSrcHeight, nm8u* pDstImg, void* pTmp)
//{
//	int nSrcSize=nSrcWidth*nSrcHeight;
//	nm8s*  pSrc8s;
//	nm16s* pHResample16s;
//	nm16s* pVResample16s;
//	nmppsMalloc_64s(&pSrc8s,nSrcSize+100);
//	nmppsMalloc_64s(&pHResample16s,nSrcSize*5/4+nSrcWidth*100);
//	nmppsMalloc_64s(&pVResample16s,nSrcSize*5*5/4/4+nSrcWidth*100);
//
//	nmppsSubC_8s((nm8s*)pSrcImg,char(128),(nm8s*)pSrc8s,nSrcSize);
//	SIG_Resample5div4_RShift0((nm8s*)pSrc8s,nSrcSize,pHResample16s+nSrcWidth*50);
//	nmppsRShiftC_(pHResample16s+nSrcWidth*50,6,pHResample16s+nSrcWidth*50,nSrcSize*5/4);
//	IMG_VResample5div4_RShift0(pHResample16s+nSrcWidth*50,nSrcWidth*5/4,nSrcHeight,pVResample16s+nSrcWidth*50);
//	nmppsClipPowCRShiftConvert_AddC_(pVResample16s+nSrcWidth*50, 6+7,6,128,(nm8s*)pDstImg, nSrcSize*5*5/4/4);
//	
//	nmppsFree(pVResample16s);
//	nmppsFree(pHResample16s);
//	nmppsFree(pSrc8s);
//	
//}
