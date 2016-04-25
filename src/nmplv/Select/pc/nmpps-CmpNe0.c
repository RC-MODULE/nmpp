//------------------------------------------------------------------------
//
//  $Workfile:: pcCompare.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcCompare.cpp
//! \author ������ �������
//! \brief  ������� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"



///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe0_64s(
	nm64s*	pSrcVec,		// Input Buffer
	nm64s*	pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe0_32s(
	nm32s*		pSrcVec,		// Input Buffer
	nm32s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 32 bit elements. nSize={2,4,..,n*2}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe0_16s(
	nm16s*		pSrcVec,		// Input Buffer
	nm16s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 16 bit elements. nSize={4,8,..,n*4}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe0_8s(
	nm8s*		pSrcVec,		// Input Buffer
	nm8s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 8 bit elements. nSize={8,16,..,n*8}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;
}

