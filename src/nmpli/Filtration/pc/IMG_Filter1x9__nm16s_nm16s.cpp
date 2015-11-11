//------------------------------------------------------------------------
//
//  $Workfile:: FilterWxH.cp $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   Convert16_WxH.cpp
//! \author Дмитрий Рыжов
//! \brief  Функции векторного ядра.
//! 
//! \endif
//!
//------------------------------------------------------------------------

//#include "internal.h"
#include "nmtype.h"
#include "nmtl.h"


void IMG_Filter5x9( nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									 int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(5-1)/2;
	int ch=(9-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i] += (*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
//					dst[dstep*j+i]=3;
				}
        }

 
}


void IMG_Filter7x5(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(7-1)/2;
	int ch=(5-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
      }
}

void IMG_Filter9x5(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(9-1)/2;
	int ch=(5-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
        }
}


void IMG_Filter7x9(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(7-1)/2;
	int ch=(9-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
        }
//    return 0;
}

void IMG_Filter9x9(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(9-1)/2;
	int ch=(9-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
        }
}

void IMG_Filter11x5(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									 int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(11-1)/2;
	int ch=(5-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
        }
}

void IMG_Filter13x5(  nm16s * src, int nSrcStride, nm32s *dst,  int nDstStride, 
									 int width, int height, nm64s * pKernel )
{
	int *Mask=(int*)pKernel;
	int sstep=nSrcStride<<1;
	int dstep=nDstStride;
	int cw=(13-1)/2;
	int ch=(5-1)/2;
	int i, j, s, t;

	for(j=0; j<height; j++)
        for(i=0; i<width; i++) {
            dst[dstep*j+i] = 0;
			for(t=-ch; t<=ch; t++)
				for(s=-cw; s<=cw; s++)
				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
					dst[dstep*j+i]+=(*(src+sstep*(j+t)+i+s))*Mask[(ch+t)*13+cw+s];
				}
        }
}

void IMG_Filter1x9(  nm16s* pSrcImg, int nSrcStride, nm8s* pKernel, nm16s* pDstImg,  int nDstStride, int nWidth, int nHeight )
{
//	int *Mask=(int*)pKernel;
//	int sstep=nSrcStride<<1;
//	int dstep=nDstStride<<1;
//	int ch=(9-1)/2;
//	int i, j, t;
//
//	for(j=0; j<nHeight; j++)
//        for(i=0; i<nWidth; i++) {
//            pDstImg[dstep*j+i] = 0;
//			for(t=-ch; t<=ch; t++)
//				{
//					dst[dstep*j+i]=(int)src[sstep*(j+t)+i+s]*Mask[(ch+t)*13+cw+s];
//					pDstImg[dstep*j+i]+=(*(pSrcImg+sstep*(j+t)+i))*Mask[ch+t];
//				}
//        }

	nmvec8s  vKernel(pKernel,9);
	nmmtr16s mSrcImg(pSrcImg,nHeight,nWidth,nSrcStride<<1);
	nmmtr16s mDstImg(pDstImg,nHeight,nWidth,nDstStride<<1);
	mSrcImg.m_border=4;
	for(int y=0; y<nHeight; y++)
        for(int x=0; x<nWidth; x++)
		{
			nmint16s nSum(0);
			for(int i=0;i<9;i++)
				nSum+=vKernel[i]*mSrcImg[y-4+i][x];
			mDstImg[y][x]=nSum;
        }
}