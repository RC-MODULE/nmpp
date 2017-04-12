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

nm4u* nmppsMalloc_4u(int size){
	 return (nm4u*) nmppsMalloc_8u(size>>1);
 }
 
void nmppsRandUniform_4u (nm4u* pDstVec,  int nSize) {
	nmppsRandUniform_8u ((nm8u*)pDstVec,  nSize>>1);
	return;
}
int main()
{
//	return 500;
		 int local_arr[100];
		 local_arr[1]=ststic_arr[1];
	clock_t t0,t1;
	int size=10240;
	nm4u *src;
	nm8u *dst;
	
	src=nmppsMalloc_4u(size);		// Allocates vec on Local bus
	dst=nmppsMalloc_8u(size);	// Allocates vec on Global bus
	printf("%x %x\n", (int)src,(int)dst);
	nmppsRandUniform_4u (src,size);
	if (src==0 || dst==0)
		return -1;
	
	t0=clock();
	
	nmppsConvert_4u8u((nm4u*)src,(nm8u*)dst,size);	

	t1=clock();

	nmppsFree(src);							// Free memory
	nmppsFree(dst);							// Free memory
	
	return t1-t0;
//	return 0x600D;
}
