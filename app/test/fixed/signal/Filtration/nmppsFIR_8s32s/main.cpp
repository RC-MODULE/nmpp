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
 


int pWeights[MAX_KERNEL_SIZE+1];
int main()
{
	clock_t t0,t1;
	
	nm8s  *srcBuf,*src; 
	nm32s *dstBuf,*dst; 
	NmppsFIRState* state;
	int maxSize=1024;
	unsigned crc=0;
	
	srcBuf=nmppsMalloc_8s(maxSize+256);
	dstBuf=nmppsMalloc_32s(maxSize+256);
	src=nmppsAddr_8s(srcBuf,128);
	dst=nmppsAddr_32s(dstBuf,128);
	
	nmppsRandUniform_8s(srcBuf,maxSize+256);
	nmppsRandUniform_32s(pWeights,MAX_KERNEL_SIZE+1);
	nmppsSet_32s(0xCCCC,dstBuf,maxSize+256);
	
	
	for(int size=0; size<maxSize; size+=8){
		for(int kernelSize=3; kernelSize<207; kernelSize+=2){
			if (nmppsFIRInitAlloc_8s32s(&state,pWeights,kernelSize))
				return -1;
			nmppsFIR_8s32s(src,dst,size,state);
			nmppsCrcAcc_32s(dst,size,&crc);
			nmppsFIRFree(state);
		}
	}
	
	
	nmppsFree(srcBuf);	
	nmppsFree(dstBuf);	

	return crc>>2;
}
