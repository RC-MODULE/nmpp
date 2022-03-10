//------------------------------------------------------------------------
//
//  $Workfile:: mtrResolve.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrResolve.cpp
//! \author Сергей Мушкаев
//! \brief  Функции линейной алгебры.
//!
//! \endif
//!
//------------------------------------------------------------------------


//!
//! \n
//!



#include "nmpp.h"

void MTR_fpResolve_Gauss(
	 double*	pSrcMtrA,
	 double*	pSrcVecB,
	 double*	pDstVecX,
	 int		nSize
  )
{
	///////////////////////////
	// Forward trace
	//int MtrSize=nSize*nSize;
	double *A=pSrcMtrA;
	double *B=pSrcVecB;
	double Major;
	double CurDivMaj;
	double *CurString;
	double *MajorString;

	int row;
	for(row=0;row<nSize-1;row++)
	{
		MajorString=A+row*nSize;
		Major=MajorString[row];
		for(int r=row+1;r<nSize;r++)
		{
			CurString =A+r*nSize;
			CurDivMaj =CurString[row]/Major;
			CurString[row]=0;
			for(int col=row+1;col<nSize;col++)
				CurString[col]-=MajorString[col]*CurDivMaj;
			B[r]-=B[row]*CurDivMaj;
		}
			
	}
	///////////////////////////
	// Backward trace
	for(row=0;row<nSize;row++)
		pDstVecX[row]=0;
	
	CurString=A+(nSize-1)*nSize;
	pDstVecX[nSize-1]=B[nSize-1]/CurString[nSize-1];

	double Summ;
	for(row=nSize-2;row>=0;row--)
	{
		CurString=A+row*nSize;
		Summ=0;
		for(int col=row+1;col<nSize;col++)
			Summ+=CurString[col]*pDstVecX[col];
		pDstVecX[row]=(B[row]-Summ)/CurString[row];
	}
	
}

int  SearchPivot(double *A,int col,int Rank)
{
	double Max=0,Tmp;
	int MaxRow=0;
	double *Column=A+col+col*Rank;
	for(int row=col;row<Rank-1;row++)
	{
		Tmp=*Column;
		Column+=Rank;
		if (Max<ABS(Tmp))
		{
			MaxRow=row;
			Max=ABS(Tmp);
		}
		
	}
	return MaxRow;
}

//!
//! \n
//!

void MTR_fpResolve_PivotGauss(
	 double*	pSrcMtrAB,
	 double*	pDstVecX,
	 int		nSize
					  )
{
	///////////////////////////
	// Forward trace
	double Major;
	double CurDivMaj;
	double *CurString;
	double *MajorString;

	int Length=nSize+1;
	int row;
	int Piv;
	for(row=0;row<nSize-1;row++)
	{
		MajorString=pSrcMtrAB+row*Length;
		Piv=SearchPivot(pSrcMtrAB,row,Length);
		if (Piv!=row)
			nmppsSwap_64s((nm64s*)(pSrcMtrAB+Piv*Length),(nm64s*)MajorString,Length);
		Major=MajorString[row];
		for(int r=row+1;r<nSize;r++)
		{
			CurString = pSrcMtrAB+r*Length;
			CurDivMaj = CurString[row]/Major;
			CurString[row]=0;
			for(int col=row+1;col<Length;col++)
				CurString[col]-=MajorString[col]*CurDivMaj;
		}
			
	}
	///////////////////////////
	// Backward trace
	for(row=0;row<nSize;row++)
		pDstVecX[row]=0;
	
	CurString=pSrcMtrAB+(nSize-1)*Length;
	pDstVecX[nSize-1]=CurString[Length-1]/CurString[nSize-1];

	double Summ;
	for(row=nSize-2;row>=0;row--)
	{
		CurString=pSrcMtrAB+row*Length;
		Summ=0;
		for(int col=row+1;col<nSize;col++)
			Summ+=CurString[col]*pDstVecX[col];
		pDstVecX[row]=(CurString[Length-1]-Summ)/CurString[row];
	}
	
}

