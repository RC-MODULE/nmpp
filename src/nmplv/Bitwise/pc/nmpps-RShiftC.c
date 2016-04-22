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
#include "nmpp.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 64-bit signed elements of input array
void nmppsRShiftC_64s(
	nm64s*			src,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm64s*			dst,	// output buffer	:long Global[Size/2]
	int				size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 32-bit signed elements of input array
void nmppsRShiftC_32s(
	nm32s*			src,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm32s*			dst,	// output buffer	:long Global[Size/2]
	int				size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 16-bit signed elements of input array
void nmppsRShiftC_16s(
	nm16s*			src,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm16s*			dst,	// output buffer	:long Global[Size/2]
	int				size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;

}

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 8-bit signed elements of input array
void nmppsRShiftC_8s(
	nm8s*			src,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm8s*			dst,	// output buffer	:long Global[Size/2]
	int				size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;

}

/////////////////////////////////////////////////////////////////////////////////////////
// Right shift under 8-bit unsigned elements of input array
void nmppsRShiftC_8u(
	nm8u*	src,	//Input buffer		:long Local [Size/8].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 7].
	nm8u*	dst,	//Output buffer		:long Global[Size/8].
	int		size		//Size of input buffer in 8 bit elements. Size=[256, 512, .., n*256].
	)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;

}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 16-bit unsigned elements of input array
void nmppsRShiftC_16u(
	nm16u*	src,		//Input buffer		:long Local [Size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm16u*	dst,		//Output buffer		:long Global[Size/4].
	int		size		//Size of input buffer in 8 bit elements. Size=[0,4,8,12...].
	)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;
}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 32-bit unsigned elements of input array
void nmppsRShiftC_32u(
	nm32u*	src,		//Input buffer		:long Local [Size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm32u*	dst,		//Output buffer		:long Global[Size/4].
	int		size		//Size of input buffer in 8 bit elements. Size=[0,4,8,12...].
	)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;
}

//////////////////////////////////////////////////////////////////////////////////////
// Performs shift to right on 64-bit unsigned elements of input array
void nmppsRShiftC_64u(
	nm64u*	src,		//Input buffer		:long Local [size/4].
	int		Shift,		//Specifies on how many positions the input values should be right-shifted :[0, 1, 2, .., 15].
	nm64u*	dst,		//Output buffer		:long Global[size/4].
	int		size		//size of input buffer in 8 bit elements. size=[0,4,8,12...].
	)
{
	int i;
	for (i=0; i<size; i++)
		dst[i] = src[i] >> Shift;
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

void nmppsFwdShiftBitstream(
	const   nm64u*	src,		//Input buffer					:long Local [size/8].
			nm64u*	dst,		//Output buffer					:long Global[size/8].
			nm64u*	pnBits,		//Being pushed bits				:long Variable
			int		nBits,		//Number of being pushed bits	:nBits=[2,4,6....62].
			int		size		//size of input buffer in 64-bit long elements. size=[1,2,3....].
	)
{
	//nm64u* src=(nm64u*)src;
	//nm64u* dst=(nm64u*)dst;
	nm64u* pbits=(nm64u*)pnBits;
	
	unsigned __int64 tmp;
	int i;
	dst[0]=(src[0]<<nBits)|(*pbits)>>(64-nBits);

	for (i=1;i<size;i++)
	{
		tmp=src[i-1]>>(64-nBits);
		dst[i]=src[i]<<nBits;
		dst[i]|=tmp;
	}

}


//////////////////////////////////////////////////////////////////////////////////////
void nmppsRShiftC_AddC_8u(nm8u *src,   int nShift,uint8b nAddVal, nm8u *dst, int size)
{
	int i;
	nm8u nMask=0xFF;
	nMask>>=nShift;
	for (i=0; i<size; i++)
		dst[i] = ((src[i] >> nShift) + nAddVal)&nMask;

}

void nmppsRShiftC_AddC_16u(nm16u *src,  int nShift, uint16b nAddVal, nm16u *dst, int size)
{
	int i;
	nm16u nMask=0xFFFF;
	nMask>>=nShift;
	for (i=0; i<size; i++)
		dst[i] = ((src[i] >> nShift) + nAddVal)&nMask;

}

void nmppsRShiftC_AddC_32u(nm32u *src,   int nShift, uint32b nAddVal,nm32u *dst, int size)
{
	int i;
	nm32u nMask=0xFFFFFFFF;
	nMask>>=nShift;
	for (i=0; i<size; i++)
		dst[i] = ((src[i] >> nShift) + nAddVal)&nMask;

}
