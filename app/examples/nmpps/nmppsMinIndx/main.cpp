//------------------------------------------------------------------------
//
//  $Workfile:: main.cpp             $
//
//  NMPLV
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.0 $      Date: 2005/06/04 
//
//! \if file_doc
//!
//! \file   main.cpp
//! \author S. Mushkaev
//! \brief  Example of vec library using (Saturation function)
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpp.h"
//#include "stdio.h"
//#include "time.h"
int main()
{
	//clock_t t0,t1;
	//t0=clock();
	
	//return 123;
	int nSize=128;
	nm16s *pSrcVec;
	nm16s *pDstVec;
	nm16s *pTmpL;
	nm16s *pTmpG;


	//unsigned long long route=0xF1010;
	//nmppsMallocSetRoute(&route,4);
	pSrcVec=nmppsMalloc_16s(nSize);	
	pDstVec=nmppsMalloc_16s(nSize);	
	pTmpL  =nmppsMalloc_16s(nSize);	
	pTmpG  =nmppsMalloc_16s(nSize);	

	//nmppsRandUniform_32u((nm32u*) pSrcVec, nSize/2, 1);			// Random initialization of the input array
	for(int i=0; i<nSize; i++){
		nmppsPut_16s(pSrcVec,i,-i);
	
	}
	nmppsPut_16s(pSrcVec,13,-1000);
	nmppsSet_16s( pTmpL, 0xCCCC, nSize);		// Constant initialization of the output array
	int nIndex;
	int16b nMaxValue;
	nmppsMinIndx_16s(pSrcVec, nSize, &nIndex , &nMaxValue, pTmpL, pTmpG,1 ); 
	
//	printf("Maximum value : %x at %d position\n", nMaxValue, nIndex);
	

	//t1=clock();

	nmppsFree(pSrcVec);							// Free memory
	nmppsFree(pDstVec);							// Free memory
	nmppsFree(pTmpL);
	nmppsFree(pTmpG);

	return nIndex;
	//return t1-t0;
}
