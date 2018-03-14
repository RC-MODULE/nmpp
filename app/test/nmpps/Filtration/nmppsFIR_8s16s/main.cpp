//------------------------------------------------------------------------
//
//  $Workfile:: main.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   main.cpp
//! \author S. Mushkaev
//! \brief  Example of signal library using
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"
#include "minrep.h"
#include "nmpls.h"
#include "time.h"
#define MAX_KERNEL_SIZE 129
 


int weights[MAX_KERNEL_SIZE+1];
int main()
{
	clock_t t0,t1;
	
	nm8s *srcBuf,*src; 
	nm16s *dstBuf,*dst; 
	NmppsFIRState* state;
	int maxSize=1024;
	unsigned crc=0;
	
	srcBuf=nmppsMalloc_8s(maxSize+256);
	dstBuf=nmppsMalloc_16s(maxSize+256);
	src=nmppsAddr_8s(srcBuf,128);
	dst=nmppsAddr_16s(dstBuf,128);
	
	nmppsRandUniform_8s(srcBuf,maxSize+256);
	nmppsRandUniform_32s(weights,MAX_KERNEL_SIZE+1);
	nmppsSet_16s(dstBuf,0xCCCC,maxSize+256);
	
	
	for(int size=8; size<maxSize; size+=8){
		for(int kernelSize=3; kernelSize<33; kernelSize+=2){
			nmppsFIRInitAlloc_8s16s(&state,weights,kernelSize);
			nmppsFIR_8s16s(src,dst,size,state);
			nmppsCrcAcc_16s(dst,size,&crc);
			nmppsFIRFree(state);
		}
	}
	
	
	nmppsFree(srcBuf);	
	nmppsFree(dstBuf);	

	return crc>>2;
}
