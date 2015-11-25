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
	dst=nmppsMalloc_8s(size);	// Allocates vec on Global bus

	if (src==0 || dst==0)
		return -1;
	
	
	t0=clock();
		
	nmppsAbs_8s((nm8s*)src,(nm8s*)dst,size);	// Calcuation of module
	
	t1=clock();

	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory

	return 0x600D;
}
