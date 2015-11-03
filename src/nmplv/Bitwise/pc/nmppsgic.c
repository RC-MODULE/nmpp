//------------------------------------------------------------------------
//
//  $Workfile:: VecLogic.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   VecLogic.cpp
//! \author Сергей Мушкаев
//! \brief  Логические и бинарные функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmplv.h"
///////////////////////////////////////////////////////////
// pDstVec[i] = !pSrcVec[i]; 
void nmppsNot_64u(nm64u*	pSrcVec,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = ~pSrcVec[i];
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsAndV_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & Src2[i];
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsAndNotV_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,	// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & (~Src2[i]);
}

///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] & Mask 
void nmppsAndC_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & Mask[0];
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] | Src2[i];
void nmppsOrV_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] | Mask 
void nmppsOrC_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Mask[0];
}
///////////////////////////////////////////////////////////////////////////////
//	Bitwise XOR operation 
//	pDstVec[i] = pSrcVec1[i] ^ pSrcVec2[i];
void nmppsXorV_64u(nm64u*		pSrcVec1,	// Input Buffer					:long Local[nSize]
			nm64u*		pSrcVec2,	// Input Buffer					:long Local[nSize]
			nm64u*		pDstVec,		// Output Buffer				:long Global[nSize]
			int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n]
			)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] ^ pSrcVec2[i];
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] ^ Mask 
void nmppsXorC_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	for(int i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] ^ Mask[0];
}

///////////////////////////////////////////////////////////////////////////////
//	Mask logic operation 
//  pDstVec[i]=(pSrcVec1[i] AND SrcVec3[i]) OR (pSrcVec2[i] AND NOT SrcVec3[i])
void nmppsMaskV_64u(nm64u*		pSrcVec1,	// Input Buffer								: long Global[nSize]
		nm64u*		pSrcVec2,	// Input Buffer								: long Global[nSize]
 		nm64u*		pSrcVec3,	// Input Buffer	(Mask)						: long Local [nSize]
		nm64u*		pDstVec,		// Output Buffe								: long Global[nSize]
		int			nSize		// nSize of input buffers in 64 bit elements : nSize=[0,1,2,3...]
		)

{
	nm32u *pV1=(nm32u*) pSrcVec1;
	nm32u *pV2=(nm32u*) pSrcVec2;
	nm32u *pV3=(nm32u*) pSrcVec3;
	nm32u *pDst=(nm32u*)pDstVec;
	for(int i=0;i<nSize*2;i++)
		pDst[i]=(pV1[i]&pV3[i])|(pV2[i]&(~pV3[i]));
}
