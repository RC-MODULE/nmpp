//------------------------------------------------------------------------
//
//  $Workfile:: pcConvert.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcConvert.cpp
//! \author Сергей Мушкаев
//! \brief  Функции для преобразования запакованных данных.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
#include "nmpp.h"
//*****************************************************************************
//  Converts each byte of the pSrcVec buffer to the 2 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsConvert_8s16s(
			nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm16s*			Dst16bit,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
				)
{
	int i;
	for (i=0;i<nSize;i++)
		Dst16bit[i] = (nm16s)pSrcVec[i];
}


//  Converts each byte of the pSrcVec buffer to the 2 bytes by adding
//  leading zero byte and stores the result in the Dst16bit buffer.
void nmppsConvert_8u16u(
			nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm16u*	Dst16bit,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		Dst16bit[i] = (nm16u)pSrcVec[i];

}

//******************************************************************************
//  Converts each byte of the pSrcVec buffer to the 4 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsConvert_8s32s(
			nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm32s*			pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm32s)pSrcVec[i];
}
//******************************************************************************
//  Converts each byte of the pSrcVec buffer to the 8 bytes by sign propagation
//  and stores the result in the pDstVec buffer
void nmppsConvert_8s64s(
			nm8s*			pSrcVec,	// input buffer		:long Local [Size/8]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[64,128,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
}

//    Converts each byte of the pSrcVec buffer to the 4 bytes by adding
//    3 leading zero bytes and stores the result in the pDstVec buffer.
void nmppsConvert_8u32u(
			nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm32u*	pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[256,512,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm32u)pSrcVec[i];
}

//    Converts each byte of the pSrcVec buffer to the 8 bytes by adding
//    3 leading zero bytes and stores the result in the pDstVec buffer.
void nmppsConvert_8u64u(
			nm8u*	pSrcVec,	// input buffer		:long Local [Size/8]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 8 bit elements. nSize=[64,128,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
}


//*******************************************************************************
//	Converts each 16 bit word of the pSrcVec to the 4 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_16s32s(nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm32s*			pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[128,256,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (int)pSrcVec[i];
}

//*******************************************************************************
//	Converts each 16 bit word of the pSrcVec to the 8 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_16s64s(
			nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
}



//*******************************************************************************
//	Converts each 32 bit word of the pSrcVec to the 8 bytes by sign propagation
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_32s64s(nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm64s*			pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64s)pSrcVec[i];
}



//	Converts each 16 bit word of the pSrcVec to the 4 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_16u32u(
			nm16u*	pSrcVec,	// input buffer		:long Local [Size/2]
			nm32u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (unsigned int)pSrcVec[i];
}

//	Converts each 16 bit word of the pSrcVec to the 8 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_16u64u(
			nm16u*	pSrcVec,	// input buffer		:long Local [Size/4]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/1]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[64,128,...]
			)
{
	
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
}


//	Converts each 32 bit word of the pSrcVec to the 8 bytes by adding
//	leading zero byte and stores the result in the pDstVec buffer.
void nmppsConvert_32u64u(nm32u*	pSrcVec,	// input buffer		:long Local [Size/4]
			nm64u*	pDstVec,	// output buffer	:long Global[Size/2]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[128,256,...]
			)
{
	
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm64u)pSrcVec[i];
}

//******************************************************************************
//	Converts each 4 bytes of the pSrcVec buffer to the 2 byte by removing
//	2 leading bytes and stores the result in the Dst16bit buffer
void nmppsConvert_32s16s(
			nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm16s*			pDstVec,	// output buffer	:long Global[Size/4]
			int				nSize		// size of input buffer in 32 bit elements. nSize=[128,256,..,]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm16s)pSrcVec[i];
}

//******************************************************************************
//    Converts each 4 bytes of the pSrcVec buffer to the 1 byte by removing
//    3 leading bytes and stores the result in the pDstVec buffer.
void nmppsConvert_32s8s(
			nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
			nm8s*			pDstVec,	// output buffer	:long Global[Size/8]
			int				nSize		// size of input buffer in 32 bit elements. nSize=[256,512,..]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm8s) pSrcVec[i];
}


//******************************************************************************
//    Converts each 2 bytes of the pSrcVec buffer  to the 1 byte by removing
//    leading byte and stores the result in the pDstVec buffer 
void nmppsConvert_16s8s(
			nm16s*			pSrcVec,	// input buffer		:long Local [Size/4]
			nm8s*			pDstVec,	// output buffer	:long Global[Size/8]
			int				nSize		// size of input buffer in 16 bit elements. nSize=[256,512,..]
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=(nm8s)pSrcVec[i];
}

//*****************************************************************************
//  Converts each bit of the pSrcVec buffer to the 2 bits by sign propagation
//  and stores the result in the pDstVec buffer
//	Example: 0b -> 00b, 1b -> 11b.
void nmppsConvert_1s2s(
			nm1*			pSrcVec,	// input buffer		:long Local [Size/64]
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
void nmppsConvert_1u2u(
			nm1*			pSrcVec,	// input buffer		:long Local [Size/64]
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
void nmppsConvert_2s4s(nm2s* pSrcVec, nm4s* pDstVec, int nSize)
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
void nmppsConvert_2u4u(nm2u* pSrcVec, nm4u* pDstVec, int nSize)
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
void nmppsConvert_32s4s(nm32s *pSrc, nm4s *pDst, int nSize)
{
    int i;
    for (i=0; i<nSize; i++)
    {
        nmppsPut_4s(pDst,i,pSrc[i]);
    }
}

void nmppsConvert_16s4s(nm16s *pSrc, nm4s *pDst, int nSize)
{
    int i;
    for (i=0; i<nSize; i++)
    {
        nmppsPut_4s(pDst,i,pSrc[i]);
    }
}

void nmppsConvert_8s4s(nm8s *pSrc, nm4s *pDst, int nSize)
{
    int i;
    for (i=0; i<nSize; i++)
    {
        nmppsPut_4s(pDst,i,pSrc[i]);
    }
}

void nmppsConvert_64s32s(nm64s* pSrcVec, nm32s* pDstVec, int nSize)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = (nm32s)pSrcVec[i];
}
void nmppsConvert_64s16s(nm64s* pSrcVec, nm16s* pDstVec, int nSize)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i] = pSrcVec[i];
}
