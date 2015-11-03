//------------------------------------------------------------------------
//
//  $Workfile:: Shift.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Shift.cpp
//! \author Сергей Мушкаев
//! \brief  Функции сдвига для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
//#include "vShift.h"
#include "nmplv.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 64-bit signed elements of input array
void nmppsArshC_64s(nm64s*			pSrcVec,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm64s*			pDstVec,	// output buffer	:long Global[Size/2]
	int				Size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<Size; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
	// No IPP analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 32-bit signed elements of input array
void nmppsArshC_32s(nm32s*			pSrcVec,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm32s*			pDstVec,	// output buffer	:long Global[Size/2]
	int				nSize		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
#ifndef USE_IPP
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
#else
	if (pSrcVec!=pDstVec)
		ippsRShiftC_32s(pSrcVec,Shift,pDstVec,nSize);
	else
		ippsRShiftC_32s_I(Shift, pSrcVec,nSize);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 16-bit signed elements of input array
void nmppsArshC_16s(nm16s*			pSrcVec,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm16s*			pDstVec,	// output buffer	:long Global[Size/2]
	int				nSize		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
#ifndef USE_IPP
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
#else
	if (pSrcVec!=pDstVec)
		ippsRShiftC_16s(pSrcVec,Shift,pDstVec,nSize);
	else
		ippsRShiftC_16s_I(Shift, pSrcVec,nSize);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 8-bit signed elements of input array
void nmppsArshC_8s(nm8s*			pSrcVec,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm8s*			pDstVec,	// output buffer	:long Global[Size/2]
	int				Size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<Size; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
	// No IPPS analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Right shift under 8-bit unsigned elements of input array
void nmppsRshC_8u(nm8u*	pSrcVec,	//Input buffer		:long Local [Size/8].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 7].
	nm8u*	pDstVec,	//Output buffer		:long Global[Size/8].
	int		nSize		//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
	)
{
#ifndef USE_IPP
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
#else
	if (pSrcVec!=pDstVec)
		ippsRShiftC_8u(pSrcVec,Shift,pDstVec,nSize);
	else
		ippsRShiftC_8u_I(Shift, pSrcVec,nSize);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 16-bit unsigned elements of input array
void nmppsRshC_16u(nm16u*	pSrcVec,		//Input buffer		:long Local [Size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm16u*	pDstVec,		//Output buffer		:long Global[Size/4].
	int		nSize		//Size of input buffer in 8 bit elements. Size=[0,4,8,12...].
	)
{
#ifndef USE_IPP
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] >> Shift;
#else
	if (pSrcVec!=pDstVec)
		ippsRShiftC_16u(pSrcVec,Shift,pDstVec,nSize);
	else
		ippsRShiftC_16u_I(Shift, pSrcVec,nSize);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 32-bit unsigned elements of input array
void nmppsRshC_32u(nm32u*	SrcVec,		//Input buffer		:long Local [Size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm32u*	DstVec,		//Output buffer		:long Global[Size/4].
	int		Size		//Size of input buffer in 8 bit elements. Size=[0,4,8,12...].
	)
{
	int i;
	for (i=0; i<Size; i++)
		DstVec[i] = SrcVec[i] >> Shift;
	// No IPPS nalaog
}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 64-bit unsigned elements of input array
void nmppsRshC_64u(nm64u*	SrcVec,		//Input buffer		:long Local [Size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm64u*	DstVec,		//Output buffer		:long Global[Size/4].
	int		Size		//Size of input buffer in 8 bit elements. Size=[0,4,8,12...].
	)
{
	int i;
	for (i=0; i<Size; i++)
		DstVec[i] = SrcVec[i] >> Shift;
	// No IPPS analog
}


//////////////////////////////////////////////////////////////////////////////////////
// Pushes nBits highest bits of  64-bit word-pBits into the begining of buffer-Src. 
// Buffer Src is considered as a bitstream being contained in 64-bit array 
// and bits are moving by continuous shift.
// In 64-bit word-pBits the lower bits are moved to the higher positions. 
// And within Src buffer hightest bits are moved to lowest positions of the next 64-bit word
// Example : 
// pushing of 8 bits: pBits=[AB00000000000000]
// into                 Src=[0807060504030201][FF0F0E0D0C0B0A09]....... will give
//						Dst=[07060504030201AB][0F0E0D0C0B0A0908]....... (last 8 bits of Src will be lost)
// If you point pBits to the last 64-bit word of Src buffer you will get the cyclical bit shift

void nmppsDisplaceBits_(
	const   nm64u*	pSrcVec,		//Input buffer					:long Local [Size/8].
			nm64u*	pDstVec,		//Output buffer					:long Global[Size/8].
			nm64u*	pnBits,		//Being pushed bits				:long Variable
			int		nBits,		//Number of being pushed bits	:nBits=[2,4,6....62].
			int		nSize		//Size of input buffer in 64-bit long elements. Size=[1,2,3....].
	)
{
	nm64u* src=(nm64u*)pSrcVec;
	nm64u* dst=(nm64u*)pDstVec;
	nm64u* pbits=(nm64u*)pnBits;
	
	unsigned __int64 tmp;
	int i;
	dst[0]=(src[0]<<nBits)|(*pbits)>>(64-nBits);

	for (i=1;i<nSize;i++)
	{
		tmp=src[i-1]>>(64-nBits);
		dst[i]=src[i]<<nBits;
		dst[i]|=tmp;
	}
}


//////////////////////////////////////////////////////////////////////////////////////
void nmppsRshC_AddC_8u(nm8u *pSrcVec,   int nShift,uint8b nAddVal, nm8u *pDstVec, int nSize)
{
	int i;
	nm8u nMask=0xFF;
	nMask>>=nShift;
	for (i=0; i<nSize; i++)
		pDstVec[i] = ((pSrcVec[i] >> nShift) + nAddVal)&nMask;
}

void nmppsRshC_AddC_16u(nm16u *pSrcVec,  int nShift, uint16b nAddVal, nm16u *pDstVec, int nSize)
{
	int i;
	nm16u nMask=0xFFFF;
	nMask>>=nShift;
	for (i=0; i<nSize; i++)
		pDstVec[i] = ((pSrcVec[i] >> nShift) + nAddVal)&nMask;
}

void nmppsRshC_AddC_32u(nm32u *pSrcVec,   int nShift, uint32b nAddVal,nm32u *pDstVec, int nSize)
{
	int i;
	nm32u nMask=0xFFFFFFFF;
	nMask>>=nShift;
	for (i=0; i<nSize; i++)
		pDstVec[i] = ((pSrcVec[i] >> nShift) + nAddVal)&nMask;
}
