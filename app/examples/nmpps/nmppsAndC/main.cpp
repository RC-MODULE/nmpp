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
int main()
{
	int local_arr[100];
	local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=1000*8;
	nm8s *src, *dst;

	nmc_malloc_set_heap(1);
	src=(nm8s*)malloc32(size/4);		// Allocates vec on Local bus
	nmc_malloc_set_heap(2);
	dst=(nm8s*)malloc32(size/4);	// Allocates vec on Global bus

	printf("%x %x\n",src,dst);
	if (src==0 || dst==0)
		return -1;
		
	
	t0=clock();
		
			
	nmppsAndC_8u((nm8u*)src,1,(nm8u*)dst,size);	// Calcuation of module
	
	t1=clock();

	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory

	return t1-t0;
	return 0x600D;
}
