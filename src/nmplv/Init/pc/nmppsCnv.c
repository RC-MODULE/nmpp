//------------------------------------------------------------------------
//
//  $Workfile:: pcCnv.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcCnv.cpp
//! \author Сергей Мушкаев
//! \brief  Функции для преобразования запакованных данных.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
#include "nmplv.h"
#include "nmtl.h"
//*****************************************************************************
//  Converts each byte of the pSrcVec buffer to the 2 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsCnv_8s(nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm16s*			Dst16bit,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
				)
{
#ifdef USE_IPP
	ippsConvert_8s16s((signed char*)pSrcVec,Dst16bit,nSize);
#else
	for(int i=0;i<nSize;i++)
		Dst16bit[i] = (nm16s)pSrcVec[i];
#endif
}


//  Converts each byte of the pSrcVec buffer to the 2 bytes by adding
//  leading zero byte and stores the result in the Dst16bit buffer.
void nmppsCnv_8u(nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm16u*	Dst16bit,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
#ifdef USE_IPP
	IppiSize roiSize={nSize,1};
	ippiConvert_8u16u_C1R(pSrcVec,nSize,Dst16bit,nSize<<1,roiSize);
#else
	for(int i=0;i<nSize;i++)
		Dst16bit[i] = (nm16u)pSrcVec[i];
#endif
	
}

//******************************************************************************
//  Converts each byte of the pSrcVec buffer to the 4 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsCnv_8s(nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm32s*			pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
#ifdef USE_IPP
	IppiSize roiSize={nSize,1};
	ippiConvert_8s32s_C1R((signed char*)pSrcVec,nSize,pDstVec,nSize<<2,roiSize);
#else
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm32s)pSrcVec[i];
#endif
}
//******************************************************************************
//  Converts each byte of the pSrcVec buffer to the 8 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsCnv_8s(nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[64,128,...]
			)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
}

//    Converts each byte of the pSrcVec buffer to the 4 bytes by adding
//    3 leading zero bytes and stores the result in the pDstVec buffer.
void nmppsCnv_8u(nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm32u*	pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
#ifdef USE_IPP
	IppiSize roiSize={nSize,1};
	ippiConvert_8u32s_C1R(pSrcVec,nSize,(nm32s*)pDstVec,nSize<<2,roiSize);
#else
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm32u)pSrcVec[i];
#endif
}

//    Converts each byte of the pSrcVec buffer to the 8 bytes by adding
//    3 leading zero bytes and stores the result in the pDstVec buffer.
void nmppsCnv_8u(nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[64,128,...]
			)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
}


//*******************************************************************************
//	Converts each 16 bit word of the pSrcVec to the 4 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_16s(nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm32s*			pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[128,256,...]
			)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (int)pSrcVec[i];
	// No IPPS analog
}

//*******************************************************************************
//	Converts each 16 bit word of the pSrcVec to the 8 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_16s(nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
	// No IPPS analog
}



//*******************************************************************************
//	Converts each 32 bit word of the pSrcVec to the 8 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_32s(nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
	// No IPPS analog
}



//	Converts each 16 bit word of the pSrcVec to the 4 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_16u(nm16u*	pSrcVec,	// input buffer		:long Local [Size/2]
			nm32u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (unsigned int)pSrcVec[i];
	// No IPPS analog
}

//	Converts each 16 bit word of the pSrcVec to the 8 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_16u(nm16u*	pSrcVec,	// input buffer		:long Local [Size/4]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
	// No IPPS analog
}


//	Converts each 32 bit word of the pSrcVec to the 8 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsCnv_32u(nm32u*	pSrcVec,	// input buffer		:long Local [Size/4]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[128,256,...]
			)
{
	
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
	// No IPPS analog
}

//******************************************************************************
//	Converts each 4 bytes of the pSrcVec buffer to the 2 byte by removing
//	2 leading bytes and stores the result in the Dst16bit buffer
void nmppsCnv_32s(nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm16s*			pDstVec,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 32 bit elements. nSize=[128,256,..,]
			)
{
	if (CHECK_OVERFLOW())
	{
		nmvec32s SrcVec((nm32s*)pSrcVec,nSize);
		nmvec16s DstVec(pDstVec,nSize);
		for(int i=0;i<nSize;i++)
			DstVec[i] = (nm16s)SrcVec.m_data[i];
	}
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm16s)pSrcVec[i];
	// No IPP analog

}

//******************************************************************************
//    Converts each 4 bytes of the pSrcVec buffer to the 1 byte by removing
//    3 leading bytes and stores the result in the pDstVec buffer.
void nmppsCnv_32s(nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm8s*			pDstVec,	// output buffer	:long Global[Size/8]
			int				nSize		// size of input buffer in 32 bit elements. nSize=[256,512,..]
			)
{
#ifndef USE_IPP 
	if (CHECK_OVERFLOW())
	{
		nmvec32s SrcVec((nm32s*)pSrcVec,nSize);
		nmvec8s DstVec(pDstVec,nSize);
		for(int i=0;i<nSize;i++)
			DstVec[i] = (nm8s)SrcVec.m_data[i];
	}
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm8s) pSrcVec[i];
#else
	IppiSize roiSize={nSize,1};
	ippiConvert_32s8u_C1R(pSrcVec,nSize<<2,(nm8u*)pDstVec,nSize,roiSize);
#endif
}


//******************************************************************************
//    Converts each 2 bytes of the pSrcVec buffer  to the 1 byte by removing
//    leading byte and stores the result in the pDstVec buffer 
void nmppsCnv_16s(nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm8s*			pDstVec,	// output buffer	:long Global[Size/8]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[256,512,..]
			)
{
#ifdef USE_IPP
	IppiSize roiSize={nSize,1};
	ippiConvert_16s8u_C1R(pSrcVec,nSize<<1,(nm8u*)pDstVec,nSize,roiSize);
#else
	if (CHECK_OVERFLOW())
	{
		nmvec16s SrcVec((nm16s*)pSrcVec,nSize);
		nmvec8s DstVec(pDstVec,nSize);
		for(int i=0;i<nSize;i++)
			DstVec[i] = (nm8s)SrcVec.m_data[i];
	}
	for(int i=0;i<nSize;i++)
		pDstVec[i]=(nm8s)pSrcVec[i];
#endif
}

//*****************************************************************************
//  Converts each bit of the pSrcVec buffer to the 2 bits by sign propagation
//  and stores the result in the pDstVec buffer
//	Example: 0b -> 00b, 1b -> 11b.
void nmppsCnv_1(nm1*			pSrcVec,	// input buffer		:long Local [Size/64]
			nm2s*			pDstVec,	// output buffer	:long Global[Size/32]
			int				nSize	// size of input buffer in bits. 
			)
{
	int i, j;
	nm64s* pi64Dst = (nm64s*)pDstVec;
	nm32s* pSrc=(nm32s*)pSrcVec;
	int iSrc, iSize = nSize >> 5;
	
	for(i=0; i<iSize; i++)
	{
		iSrc = pSrc[i];
		for(j=0; j<32; j++)
		{
			pi64Dst[i] <<= 2;
			pi64Dst[i] |= ((iSrc >> 31) & 0x3);
			iSrc <<= 1;
		}
	}		
}
//******************************************************************************
//  Converts each bit of the pSrcVec buffer to the 2 bits by adding
//  leading zero bit and stores the result in the pDstVec buffer.
//	Example: 0b -> 00b, 1b -> 01b.
void nmppsCnv_1(nm1*			pSrcVec,	// input buffer		:long Local [Size/64]
			nm2u*			pDstVec,	// output buffer	:long Global[Size/32]
			int				nSize	// size of input buffer in bits. 
			)
{
	int i, j;
	nm64s* pi64Dst = (nm64s*)pDstVec;
	nm32u* pSrc=(nm32u*)pSrcVec;

	int iSize = nSize >> 5;
	unsigned int uiSrc;

	for(i=0; i<iSize; i++)
	{
		uiSrc = pSrc[i];
		for(j=0; j<32; j++)
		{
			pi64Dst[i] <<= 2;
			pi64Dst[i] |= (uiSrc >> 31);
			uiSrc <<= 1;
		}
	}
}

//******************************************************************************
//  Converts each bit pair of the pSrcVec buffer to the 4 bits by sign propagation
//  and stores the result in the pDstVec buffer
//	Example: 00b -> 0000b, 01b -> 0001b, 10b -> 1110b, 11b -> 1111b.
void nmppsCnv_2s(nm2s* pSrcVec, nm4s* pDstVec, int nSize)
{
	int i, j;
	nm64s*pi64Dst = (nm64s*)pDstVec;
	int iSize = nSize >> 5;
	int iSrc, *piSrc = (nm32s*)pSrcVec;

	for(i=0; i<iSize; i++)
	{
		pi64Dst[i] = 0;
		iSrc = piSrc[i];
		for(j=0; j<16; j++)
		{
			pi64Dst[i] <<= 4;
			pi64Dst[i] |= ((iSrc >> 30) & 0xf);
			iSrc <<= 2;
		}
	}
}
//******************************************************************************
//	Converts each bit pair of the pSrcVec buffer to the 4 bits by adding
//	3 leading zero bits and stores the result in the pDstVec buffer.
//	Example: 00b -> 0000b, 01b -> 0001b, 10b -> 0010b, 11b -> 0011b.
void nmppsCnv_2u(nm2u* pSrcVec, nm4u* pDstVec, int nSize)
{
	int i, j;
	nm64s*pi64Dst = (nm64s*)pDstVec;

	int iSize = nSize >> 5;
	unsigned int uiSrc, *puiSrc = (nm32u*)pSrcVec;

	for(i=0; i<iSize; i++)
	{
		uiSrc = puiSrc[i];
		for(j=0; j<32; j++)
		{
			pi64Dst[i] <<= 4;
			pi64Dst[i] |= (uiSrc >> 30);
			uiSrc <<= 2;
		}
	}
}
//******************************************************************************
void nmppsCnv_32s(nm32s *pSrc, nm4s *pDst, int nSize)
{
    for(int i=0; i<nSize; i++)
    {
        nmppsSetInt_4s(pDst,i,pSrc[i]);
    }
}

void nmppsCnv_16s(nm16s *pSrc, nm4s *pDst, int nSize)
{
    for(int i=0; i<nSize; i++)
    {
        nmppsSetInt_4s(pDst,i,pSrc[i]);
    }
}

void nmppsCnv_8s(nm8s *pSrc, nm4s *pDst, int nSize)
{
    for(int i=0; i<nSize; i++)
    {
        nmppsSetInt_4s(pDst,i,pSrc[i]);
    }
}

void nmppsCnv_64s(nm64s* pSrcVec, nm32s* pDstVec, int nSize)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = (nm32s)pSrcVec[i];
}
void nmppsCnv_64s(nm64s* pSrcVec, nm16s* pDstVec, int nSize)
{
	for(int i=0;i<nSize;i++)
		pDstVec[i] = pSrcVec[i];
}
