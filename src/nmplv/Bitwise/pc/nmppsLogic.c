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

#include "nmpp.h"
///////////////////////////////////////////////////////////
// pDstVec[i] = !pSrcVec[i]; 
void nmppsNot_64u(nm64u*	pSrcVec,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsNot_64u",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = ~pSrcVec[i];

	#endif
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsAnd_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsAnd_64u",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & Src2[i];

	#endif
}


///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsAndNotV_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,	// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsAndNotV_64u",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & (~Src2[i]);

	#endif
}



///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] | Src2[i];
void nmppsOr_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsRShiftC_s",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];

	#endif
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] | Mask 
void nmppsOrC_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsRShiftC_s",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Mask[0];

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Bitwise XOR operation 
//	pDstVec[i] = pSrcVec1[i] ^ pSrcVec2[i];
void nmppsXor_64u(nm64u*		pSrcVec1,	// Input Buffer					:long Local[nSize]
			nm64u*		pSrcVec2,	// Input Buffer					:long Local[nSize]
			nm64u*		pDstVec,		// Output Buffer				:long Global[nSize]
			int			nSize		// Vector size in 64-bit words	:nSize=[0,1,2,..,n]
			)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsRShiftC_s",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] ^ pSrcVec2[i];

	#endif
}
///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] ^ Mask 
void nmppsXorC_64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsRShiftC_s",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] ^ Mask[0];

	#endif
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
	#ifdef RPC
	//RPC_HOST_PPI("nmppsRShiftC_s",pSrcVec,pDstVec,nSize,8);
	#else


	nm32u *pV1=(nm32u*) pSrcVec1;
	nm32u *pV2=(nm32u*) pSrcVec2;
	nm32u *pV3=(nm32u*) pSrcVec3;
	nm32u *pDst=(nm32u*)pDstVec;
int i;
	for (i=0;i<nSize*2;i++)
		pDst[i]=(pV1[i]&pV3[i])|(pV2[i]&(~pV3[i]));

	#endif
}
