//------------------------------------------------------------------------
//
//  $Workfile:: InitRand.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   InitRand.cpp
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов.
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

/*
void nmppsRandUniform_32u(nm32u*	pDstVec,		// array									:int Global [SizeInt]
		int				nSize,		// nSize of Source array in 32-bit elements	:nSize=    [0,1,2,3,4...]
		unsigned nRandomize
		)
{

	for(int i=0;i<nSize;i++)
	{
		nRandomize=1664525L*nRandomize+1013904223L;
		pDstVec[i]=nRandomize;
	}
}

*/