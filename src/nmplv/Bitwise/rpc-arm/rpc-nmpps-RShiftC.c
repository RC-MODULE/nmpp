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
#include "rpc-host.h"
#include "nmtype.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic right shift under 64-bit signed elements of input array
void nmppsRShiftC_64s(
	nm64s*			src,	// input buffer		:long Local [Size/2]
	int				Shift,		// specifies on how many positions the input values should be right-shifted :[0,1,2,3..31]
	nm64s*			dst,	// output buffer	:long Global[Size/2]
	int				size		// size of input buffer in 32 bit elements. Size=[2,4,6...]
		)
{
	RPC_HOST_PIPI("nmppsRShiftC_64s",src,Shift,dst,size,8);
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
	RPC_HOST_PIPI("nmppsRShiftC_32s",src,Shift,dst,size,4);
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
	RPC_HOST_PIPI("nmppsRShiftC_16s",src,Shift,dst,size,2);
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
	RPC_HOST_PIPI("nmppsRShiftC_8s",src,Shift,dst,size,1);
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
	RPC_HOST_PIPI("nmppsRShiftC_8u",src,Shift,dst,size,1);
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
	RPC_HOST_PIPI("nmppsRShiftC_16u",src,Shift,dst,size,2);
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
	RPC_HOST_PIPI("nmppsRShiftC_32u",src,Shift,dst,size,4);
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
	RPC_HOST_PIPI("nmppsRShiftC_64u",src,Shift,dst,size,8);
}

