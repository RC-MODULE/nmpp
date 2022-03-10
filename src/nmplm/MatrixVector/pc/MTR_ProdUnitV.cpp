//------------------------------------------------------------------------
//
//  $Workfile:: mProdV.cpp        $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mProdV.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
//#include "tnmvector.h"
//#include "tnmmatrix.h"
#include "nmtype.h"

#ifndef RPC
#include "nmtl/tmatrix.h"
#include "nmtl/tnmmtr.h"
#endif

extern "C" {

void MTR_ProdUnitV_4x16s( v4nm16s* pSrcMtr, nm16s* pDstVec, int nHeight)
{
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,4);
	nmvec16s SrcVec(4);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
    for (int i = 0; i < 4; i++)
    	SrcVec[i] = 1;
	DstVec=SrcMtr*SrcVec;
}

/*
void MTR_ProdUnitV( nm16s* pSrcMtr, nm16s* pDstVec, int nHeight)
{
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,16);
	nmvec16s SrcVec(16);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
    for (int i = 0; i < 16; i++)
    	SrcVec[i] = 1;
	DstVec=SrcMtr*SrcVec;
}
*/

void MTR_ProdUnitV_16x8s( v16nm8s* pSrcMtr, nm16s* pDstVec, int nHeight)
{
	nmmtr8s  SrcMtr((nm8s*)pSrcMtr,nHeight,16);
	nmvec16s SrcVec(16);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
    for (int i = 0; i < 16; i++)
    	SrcVec[i] = 1;
	DstVec=SrcMtr*SrcVec;
}

};
