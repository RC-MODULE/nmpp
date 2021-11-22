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
#include "nmplv/vSupport.h"
extern "C"{
	

void nmppmMul_mm_2s64s( nm2s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i;
	int j;
	int k;
	long long sum;
	nm64s* colB;
	nm2s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=nmppsGet_2s(rowA,k)*colB[k*widthB];
			}
			rowDst[j]=sum;
		}

		rowA=nmppsAddr_2s(rowA,widthA);
	}
}

void nmppmMul_mm_4s64s( nm8s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i;
	int j;
	int k;
	long long sum;
	nm64s* colB;
	nm4s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=nmppsGet_4s(rowA,k)*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
		rowA=nmppsAddr_4s(rowA,widthA);
	}
}

void nmppmMul_mm_8s8s( nm8s* srcMtrA, int heightA, int widthA,  nm8s* srcMtrB, nm8s* dstMtr, int widthB)
{
	
	int i;
	int j;
	int k;
	int sum;
	nm8s* colB;
	nm8s* rowA  =srcMtrA;
	nm8s* rowDst=dstMtr;
	
	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			for(k=0, sum=0; k< widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}
void nmppmMul_mm_8s16s( nm8s* srcMtrA, int heightA, int widthA,  nm16s* srcMtrB, nm16s* dstMtr, int widthB)
{
	int i;
	int j;
	int k;
	int sum;
	nm16s* colB;
	nm8s* rowA  =srcMtrA;
	nm16s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}
void nmppmMul_mm_8s32s( nm8s* srcMtrA, int heightA, int widthA,  nm32s* srcMtrB, nm32s* dstMtr, int widthB)
{
	int i;
	int j;
	int k;
	int sum;
	nm32s* colB;
	nm8s* rowA  =srcMtrA;
	nm32s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_8s64s( nm8s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i;
	int j;
	int k;
	long long sum;
	nm64s* colB;
	nm8s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_16s16s( nm16s* srcMtrA, int heightA, int widthA,  nm16s* srcMtrB, nm16s* dstMtr, int widthB)
{
	int i,j,k,sum;
	nm16s* colB;
	nm16s* rowA  =srcMtrA;
	nm16s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_16s32s( nm16s* srcMtrA, int heightA, int widthA,  nm32s* srcMtrB, nm32s* dstMtr, int widthB)
{
	int i,j,k,sum;
	nm32s* colB;
	nm16s* rowA  =srcMtrA;
	nm32s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}

}

void nmppmMul_mm_16s64s( nm16s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i,j,k;
	long long sum;
	nm64s* colB;
	nm16s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_32s32s( nm32s* srcMtrA, int heightA, int widthA,  nm32s* srcMtrB, nm32s* dstMtr, int widthB)
{
	int i,j,k,sum;
	nm32s* colB;
	nm32s* rowA  =srcMtrA;
	nm32s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			for(k=0, sum=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_32f( float* srcMtr1,  int nHeight1, int nStride1,
                      float* srcMtr2,  int nWidth1,  int nStride2,
                      float* dstMtr,   int nWidth2,  int nStrideDst,  int bPlusDst )
{
	int i,j,k,sum;
	float* col2;
	float* row1  =srcMtr1;
	float* rowDst=dstMtr;

	for(i=0; i<nHeight1; i++, row1+=nStride1, rowDst+=nStrideDst){
		for(j=0; j<nWidth2; j++){
			col2=srcMtr2+j;
            sum = bPlusDst ? rowDst[j] : 0;
			for(k=0; k<nWidth1; k++){
				sum+=row1[k]*col2[k*nStride2];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_32s64s( nm32s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i,j,k;
	long long sum;
	nm64s* colB;
	nm32s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}

void nmppmMul_mm_64s64s( nm64s* srcMtrA, int heightA, int widthA,  nm64s* srcMtrB, nm64s* dstMtr, int widthB)
{
	int i,j,k;
	long long sum;
	nm64s* colB;
	nm64s* rowA  =srcMtrA;
	nm64s* rowDst=dstMtr;

	for(i=0; i<heightA; i++, rowA+=widthA, rowDst+=widthB){
		for(j=0; j<widthB; j++){
			colB=srcMtrB+j;
			sum=0;
			for(k=0; k<widthA; k++){
				sum+=rowA[k]*colB[k*widthB];
			}
			rowDst[j]=sum;
		}
	}
}


};

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
