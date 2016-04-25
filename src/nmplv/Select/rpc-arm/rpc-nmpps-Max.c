//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/07/13 14:19:56 $
//
//! \if file_doc
//!
//! \file   GetMax.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "rpc/rpc-host.h"
#include "nmplv.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 8-bit buffer
void nmppsMax_8s(
				nm8s*		pSrcVec,	// input buffer					:long Local [Size/8]
				int			nSize,		// buffer size in 8-bit words	:nSize=[512,768,1024.....]
				int8b*		pMaxValue)	// Maximum
{
	RPC_HOST_PIR("nmppsMax_8s",pSrcVec,nSize,pMaxValue,1);
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 16-bit buffer
void nmppsMax_16s(
				nm16s*		pSrcVec,	// input buffer					:long Local [Size/4]
				int			nSize,		// buffer size in 16-bit words	:nSize=[256,384,512...]
				int16b*		pMaxValue)	// Maximum
{
	RPC_HOST_PIR("nmppsMax_16s",pSrcVec,nSize,pMaxValue,2);
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 32-bit buffer
void nmppsMax_32s(
				nm32s*		pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int*		pMaxValue)	// Maximum
{
	RPC_HOST_PIR("nmppsMax_32s",pSrcVec,nSize,pMaxValue,4);
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 64-bit buffer
void nmppsMax_64s(
				nm64s63b*	pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int64b*		pMaxValue)	// Maximum
{
	RPC_HOST_PIR64("nmppsMax_64s",pSrcVec,nSize,pMaxValue,8);
}

