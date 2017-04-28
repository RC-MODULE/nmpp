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

 nm1* nmppsMalloc_1u(int size){
	 return (nm1*) nmppsMalloc_8u(size/8);
 }
 
  nm4u* nmppsMalloc_4u(int size){
	 return (nm4u*) nmppsMalloc_8u(size/2);
 }

 void nmppsRandUniform_1u (nm1* src,int size){
	 nmppsRandUniform_8u((nm8u*)src,size/8);
	 return;
 }
 
int main()
{
//	return 500;
		 int local_arr[100];
		 local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=20992;
	nm1 *src;
	nm4u *dst;
	
	src=nmppsMalloc_1u(size);		// Allocates vec on Local bus
	dst=nmppsMalloc_4u(size);	// Allocates vec on Global bus
	nmppsRandUniform_1u(src,size);
	if (src==0 || dst==0)
		return -1;
	
	t0=clock();
	
	nmppsConvert_1u4u((nm1*)src,(nm4u*)dst,size);	

	t1=clock();

	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory
	return t1-t0; 
//	return 0x600D;
}
