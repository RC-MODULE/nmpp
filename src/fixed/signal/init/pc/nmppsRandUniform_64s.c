//------------------------------------------------------------------------
//
//  $Workfile:: InitRand.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   InitRand.cpp
//! \author ������ �������
//! \brief  ������� ������������� � ����������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

 
//! 
//! \perfinclude _nmppsRandUniform__FPUiiUi_.html
//! 


static unsigned long long				Randomize=-1;
////////////////////////////////////////////////////////////////////////////
//  Random initialization of 64-bit Buffer
void nmppsRandUniform_64s(
		nm64s*			pDstVec,		// array									:int Global [SizeInt]
		int				nSize 		// nSize of Source array in 64-bit elements	:nSize=    [0,1,2,3,4...]
		)
{
	//__int64 Rand=Randomize&0xFFFFFFFFL;
	int i;
	for(i=0;i<nSize;i++)
	{
		//Rand=1664525L*Rand+1013904223L;
		unsigned long long R=Randomize<<63;
		Randomize>>=1;
		Randomize|=R;
		Randomize=1664525LL*Randomize+1013904223LL;
		pDstVec[i]=Randomize;
	}
	//Randomize=Rand;
}


