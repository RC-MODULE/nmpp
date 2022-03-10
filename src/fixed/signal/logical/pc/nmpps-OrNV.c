//------------------------------------------------------------------------
//
//  $Workfile:: VecLogic.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2013/01/24 13:50:15 $
//
//! \if file_doc
//!
//! \file   VecOrNV.cpp
//! \author ������ �������
//! \brief  ���������� � �������� ������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpp.h"
//void nmppsOrNV_64u(nm64u** pSrcVecs, int numVecs, nm64u* pDstVec, int nSize);
///////////////////////////////////////////////////////////
// pDstVec[i] = !pSrcVec[i]; 
void nmppsOrNV_64u(nm64u**	pSrcVecs,		// Input Buffer
	int numVecs,        //Number of  input buffers, numVecs > 2
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// Size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i,k;
	nm64u * pVec0=pSrcVecs[0];
	nm64u * pVec1=pSrcVecs[1];
	for (i=0; i<nSize; i++){
		pDstVec[i] = pVec0[i] | pVec1[i];
	}
		
	for (i=0; i<nSize; i++){
		for(k=2; k<numVecs; k++){
			nm64u * pVec=pSrcVecs[k];
			pDstVec[i]|= pVec[i];
		}
	}

}
///////////////////////////////////////////////////////////////////////////////
