//------------------------------------------------------------------------
//
//  $Workfile:: mProdM.cpp  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mProdM.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения матрицы на матрицу.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
//#include "tnmvector.h"
//#include "tnmmatrix.h"
#include "rpc-host.h"
#include "nmplm.h"

#ifndef RPC
//#include "nmtl.h"

#endif
#include "nmtl/tmatrix.h"
#include "nmtl/tnmmtr.h"
//extern "C" {

//#ifdef USE_IPP
//#include "ipp.h"
//#endif

//#include "stdlib.h"




void nmppmMul_mm_8s8s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm8s* pSrcMtr2, nm8s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_8s8s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,1);
	#else
	nmmtr8s SrcMtrA((nm8s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr8s SrcMtrB((nm8s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr8s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	
}
void nmppmMul_mm_8s16s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_8s16s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,2);
	#else
	nmmtr8s SrcMtrA((nm8s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr16s SrcMtrB((nm16s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr16s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	
	
	
}
void nmppmMul_mm_8s32s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_8s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,4);
	#else
	nmmtr8s SrcMtrA((nm8s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr32s SrcMtrB((nm32s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr32s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	

}

void nmppmMul_mm_8s64s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_8s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,8);
	#else
	nmmtr8s SrcMtrA((nm8s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr64s SrcMtrB((nm64s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr64s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	
}

void nmppmMul_mm_16s16s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_16s16s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,2);
	#else
	nmmtr16s SrcMtrA((nm16s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr16s SrcMtrB((nm16s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr16s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	


}

void nmppmMul_mm_16s32s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_16s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,4);
	#else
	nmmtr16s SrcMtrA((nm16s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr32s SrcMtrB((nm32s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr32s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	

	
	
}

void nmppmMul_mm_16s64s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_16s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,8);
	#else
	nmmtr16s SrcMtrA((nm16s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr64s SrcMtrB((nm64s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr64s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	

}

void nmppmMul_mm_32s32s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_32s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,4,4);
	#else
	nmmtr32s SrcMtrA((nm32s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr32s SrcMtrB((nm32s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr32s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	
}

void nmppmMul_mm_32s64s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	#ifdef RPC
	RPC_HOST_PIIPPI("nmppmMul_mm_32s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,4,8);
	#else
	nmmtr32s SrcMtrA((nm32s*)pSrcMtr1,nHeight1,nWidth1);
	nmmtr64s SrcMtrB((nm64s*)pSrcMtr2,nWidth1,nWidth2);
	nmmtr64s DstMtr(pDstMtr,nHeight1,nWidth2);
	DstMtr=SrcMtrA*SrcMtrB;
	#endif	
}



/*
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit mtr  by vec of 8 shorts
void nmppmMul_mv_(
		nm8s*		SrcMtr,			// input  mtr (nSrcStride=8)	:long Global [8*Height/4]
		nm16s*		SrcVec8,		// input  vec of 8 16-bit words	:long Local  [2]
			nm16s*		pDstVec,			// output vec					:long Global [Height/4]
			int			nHeight			// Matrix height					:=[0,1,2,...]
		)

{
	
	nmmtr8s  Mtr(nHeight,8);
	vec<nmint<16> > Vec(8);
	vec<nmint<16> > Res(nHeight);
	Mtr.SetData(SrcMtr);
	Vec.SetData(SrcVec8);
	Res=Mtr*Vec;
	Res.GetData(pDstVec);

}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-short column mtr  by vec of 8 shorts
void nmppmMul_mv_(
		nm16s*		SrcMtr,			// input  mtr (nSrcStride=8)	:long Global [8*Height/4]
		nm16s*		SrcVec8,		// input  vec of 8 16-bit words	:long Local  [8/4]
			nm16s*		pDstVec,			// output vec					:long Global [Height/4]
			int			nHeight			// Matrix height					:=[0,8,16,24...]
			)
{
	if (CHECK_OVERFLOW())
	{
		nmmtr16s Mtr(nHeight,8);
		vec<nmint<16> > Vec(8);
		vec<nmint<16> > Res(nHeight);
		Mtr.SetData(SrcMtr);
		Vec.SetData(SrcVec8);
		Res=Mtr*Vec;
		Res.GetData(pDstVec);
	}
	else 
		for(int row=0;row<nHeight;row++)
		{
			short S=0;
			for(int col=0;col<8;col++,SrcMtr++)
				S+=(*SrcMtr)*SrcVec8[col];
			pDstVec[row]=S;
		}
}

*/


//};