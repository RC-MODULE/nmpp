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
//extern "C" void nmppsConvert_2s1s(const nm2s* pSrcVec, nm1*  pDstVec, int nSize);

nm2s* nmppsMalloc_2s(int size){
	
	return (nm2s*)nmppsMalloc_8s(size/4);
}

nm1* nmppsMalloc_1s(int size){
	
	return (nm1*)nmppsMalloc_8s(size/8);
}

 void nmppsRandUniform_2s (nm2s* src,int size){
	 nmppsRandUniform_8s((nm8s*)src,size/4);
	 return;
 }

int main()
{
//	return 500;
		 int local_arr[100];
		 local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=102400;
	nm2s *src;
	nm1 *dst;
	
	src=nmppsMalloc_2s(size);		// Allocates vec on Local bus
	dst=nmppsMalloc_1s(size);	// Allocates vec on Global bus
	
	printf("%x %x\n", (int)src,(int)dst);
	if (src==0 || dst==0)
		return -1;
	nmppsRandUniform_2s(src,size);
	
	t0=clock();
	nmppsConvert_2s1s((nm2s*)src,(nm1*)dst, size);	

	t1=clock();
	
	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory
	
	return t1-t0;
//	return 0x600D;
}
