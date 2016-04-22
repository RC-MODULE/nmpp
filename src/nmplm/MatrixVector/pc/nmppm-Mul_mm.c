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

#include "nmtype.h"

void nmppmMul_mm_8s8s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm8s* pSrcMtr2, nm8s* pDstMtr, int nWidth2)
{
	
	int i;
	int j;
	int k;
	int p;
	nm8s* col2;
	nm8s* row1  =pSrcMtr1;
	nm8s* rowDst=pDstMtr;
	
	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}
void nmppmMul_mm_8s16s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	int i;
	int j;
	int k;
	int p;
	nm16s* col2;
	nm8s* row1  =pSrcMtr1;
	nm16s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}
void nmppmMul_mm_8s32s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	int i;
	int j;
	int k;
	int p;
	nm32s* col2;
	nm8s* row1  =pSrcMtr1;
	nm32s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}

void nmppmMul_mm_8s64s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	int i;
	int j;
	int k;
	long long p;
	nm64s* col2;
	nm8s* row1  =pSrcMtr1;
	nm64s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}

void nmppmMul_mm_16s16s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	int i,j,k,p;
	nm16s* col2;
	nm16s* row1  =pSrcMtr1;
	nm16s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}

void nmppmMul_mm_16s32s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	int i,j,k,p;
	nm32s* col2;
	nm16s* row1  =pSrcMtr1;
	nm32s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}

}

void nmppmMul_mm_16s64s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	int i,j,k;
	long long p;
	nm64s* col2;
	nm16s* row1  =pSrcMtr1;
	nm64s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}

void nmppmMul_mm_32s32s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	int i,j,k,p;
	nm32s* col2;
	nm32s* row1  =pSrcMtr1;
	nm32s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
}

void nmppmMul_mm_32s64s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	int i,j,k;
	long long p;
	nm64s* col2;
	nm32s* row1  =pSrcMtr1;
	nm64s* rowDst=pDstMtr;

	for(i=0; i<nHeight1; i++, row1+=nWidth1, rowDst+=nWidth2){
		for(j=0; j<nWidth2; j++){
			col2=pSrcMtr2+j;
			p=0;
			for(k=0; k<nWidth2; k++){
				p+=row1[k]*col2[k*nWidth2];
			}
			rowDst[j]=p;
		}
	}
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
