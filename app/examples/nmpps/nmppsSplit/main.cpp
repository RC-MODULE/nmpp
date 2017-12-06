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
 

int main()
{
	clock_t t0,t1;
	int size=4096;//10240*2;
	nm8s *src, *dst1, *dst2, *tmp;

	nmppsMallocSetRoute16(0xF3221);
	src =nmppsMalloc_8s(size);	
	dst1=nmppsMalloc_8s(size);	
	dst2=nmppsMalloc_8s(size);	
	tmp =nmppsMalloc_8s(size);	

	if (src==0 || dst1==0 || dst2==0 || tmp==0)
		return -1;
	
	
	t0=clock();
	nmppsSplit_8s(src, dst1, dst2, size, tmp );
	// size=10240*2; Return 5389 ; 5389/(10240*2/8) = 2,105078125 на лонг
	// size=4096 ; Return 1286   ; 1286/(4096/8) = 2,51171875 на лонг
	
	
	//nmppsSplitEco_8s(src, dst1, dst2, size);
	// size=10240*2; Return 5488 = 0x1570 ; 5488/(10240*2/8) = 2,14375 на лонг
	// size=4096 ; Return 1328  ; 1328/(4096/8) = 2,59375 на лонг
	
	
	
	t1=clock();

	//nmppsFree(src);							// Free memory
	//nmppsFree(dst);							// Free memory

	return t1-t0;
}
