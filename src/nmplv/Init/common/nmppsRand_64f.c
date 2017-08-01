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


static unsigned long long				Randomize=-1;
////////////////////////////////////////////////////////////////////////////
//  Random initialization of 64-bit Buffer
void nmppsRandUniform_64f(
		nm64f*			pDstVec,		// array									:int Global [SizeInt]
		int				nSize,		// nSize of Source array in 64-bit elements	:nSize=    [0,1,2,3,4...]
		double low,
		double hi
		)
{
	int i;
	double temp;
	long long* pointer_64int;
	double* pointer_double;
	const double range = 1.0/(double)(0xffffffffffffffff);
	double k = (hi-low)*range;
	double b = 0.5*(hi+low);
	long long r;
	long long mask;
	if((low == 0)&(hi == 0)){return;}
	for(i=0;i<nSize;i++)
	{
		unsigned long long R=Randomize<<63;
		Randomize>>=1;
		Randomize|=R;
		Randomize=1664525LL*Randomize+1013904223LL;
		r=Randomize;
		temp = k*r+b;
		pointer_64int = (long long*)&temp;
		r = *pointer_64int;
		r = r>>14;
		r = r<<14;
		pointer_double = (double*)&r;
		pDstVec[i] = *pointer_double;// + b;
		//pDstVec[i] = temp;
	}
	return;
	//Randomize=Rand;
}

//#ifndef __NM__
		//r = r + 0x1;
		//r = r >> 11;
		//r = r << 11;
		//#endif 
		//r|=(r+1);
		//mask &= (r+1);
		//mask &= (r+2);
		//mask &= (r-1);
		//mask &= (r-2);
		//r = r&mask;

