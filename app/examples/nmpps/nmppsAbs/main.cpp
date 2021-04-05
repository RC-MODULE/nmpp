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

//#include "sys/times.h"
// extern int errno;
//extern "C" {
//clock_t _times(struct tms* tms) {
//     errno = -1;
//    return (clock_t)-1;
//}
//};

 int ststic_arr[100];
 int init_arr[2]={1,2};
int main()
{
	int local_arr[100];
	local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=10240;
	nm8s *src, *dst;

	
	src=nmppsMalloc_8s(size);		// Allocates vec on Local bus
	//dst=nmppsMalloc_8s(size);		// Allocates vec on Global bus
	nmc_malloc_set_heap(0);
	src=(nm8s*)malloc32(size/4);	// Allocates vec on Local bus
	nmc_malloc_set_heap(1);
	dst=(nm8s*)malloc32(size/4);	// Allocates vec on Global bus

	printf("%x, %x\n",src,dst);
	if (src==0 || dst==0)
		return -1;
	
	t0=clock();
		
	nmppsAbs_8s((nm8s*)src,(nm8s*)dst,size);	// Calcuation of module
	t1=clock();
	
	free(src);							// Free memory
	free(dst);							// Free memory

	return t1-t0;
	//return 0x600D;
	return 0;
}
