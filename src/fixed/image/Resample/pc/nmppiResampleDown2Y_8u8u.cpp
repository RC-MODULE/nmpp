//------------------------------------------------------------------------
//
//  $Workfile:: iResizeDown2_pc.cpp  $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   ResizeDown2Y_CS15.cpp
//! \author ������ ��������
//! \brief  ������� ��������� �������� �����������.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpli.h"

extern "C"{

void nmppiResampleDown2Y_16u16u(
                      nm16u15b*			pSrcImg,	// input buffer		:long Local	[len/4]
                      nm16u15b*			pDst,	// output buffer	:long Global[len/4/2]
                      int				w,		// size of input buffer in 16 bit elements. nSize=[0,4,...]
                      int				h		// size of input buffer in 16 bit elements. nSize=[0,4,...]
                      )
{
    for (int i=0;i<(h/2);i++)
        for(int j=0;j<w;j++)
            ((nm16u*)pDst)[i*w+j] = ((unsigned short)(((nm16u*)pSrcImg)[2*i*w+j]+((nm16u*)pSrcImg)[2*i*w+j+w]))>>1;
}


void nmppiResampleDown2Y_8u8u(
                      nm8u7b*			pSrcImg,	// input buffer		:long Local	[len/4]
                      nm8u7b*			pDst,	// output buffer	:long Global[len/4/2]
                      int				w,		// size of input buffer in 16 bit elements. nSize=[0,4,...]
                      int				h		// size of input buffer in 16 bit elements. nSize=[0,4,...]
                      )
{
    for (int i=0;i<(h/2);i++)
        for(int j=0;j<w;j++)
            ((nm8u*)pDst)[i*w+j] =
            (unsigned char)(((nm8u*)pSrcImg)[2*i*w+j]+((nm8u*)pSrcImg)[2*i*w+j+w])>>1;
}

};