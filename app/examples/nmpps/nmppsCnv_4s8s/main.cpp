//------------------------------------------------------------------------
//
//  $Workfile:: main.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/03/04 14:35:42 $
//
//! \if file_doc
//!
//! \file   main.cpp
//! \author S. Mushkaev
//! \brief  Example of vec library using
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"
#include "time.h"
#include "stdio.h"
 int ststic_arr[100];
 int init_arr[2]={1,2};
 
nm4s* nmppsMalloc_4s(int size){
	 return (nm4s*) nmppsMalloc_8s(size>>1);
 }
 
void nmppsRandUniform_4s (nm4s* pDstVec,  int nSize) {
	nmppsRandUniform_8s ((nm8s*)pDstVec,  nSize>>1);
	return;
}

int main()
{
//	return 500;
		 int local_arr[100];
		 local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=10240;
	nm4s *src;
	nm8s *dst;
	nmppsMallocSetRoute16(0xf23);
	src=nmppsMalloc_4s(size);		// Allocates vec on Local bus
	dst=nmppsMalloc_8s(size);	// Allocates vec on Global bus
	printf("%x %x\n", (int)src,(int)dst);
	nmppsRandUniform_4s (src,  size);
	if (src==0 || dst==0)
		return -1;
	
	t0=clock();
	nmppsConvert_4s8s((nm4s*)src,(nm8s*)dst,size);	

	t1=clock();
	
	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory
	return t1-t0;
//	return 0x600D;
}
