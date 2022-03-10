#include "malloc32.h"
#include "nmplv/vSupport.h"
#include "nmplv/vInit.h"


int nmppsMallocResetRoute(){
	if (nmppsMallocResetPos())
		return nmppsMallocSpec.status;
	else{
		nmppsSet_64u (0,(nm64u*)nmppsMallocSpec.route,  NMPPS_MALLOC_LIMIT>>4);		
		nmppsSet_64u (0xFFFFFFFFFFFFFFFF,(nm64u*)nmppsMallocSpec.bestRoute,  NMPPS_MALLOC_LIMIT>>4);		
		nmppsSet_64u (0,(nm64u*)nmppsMallocSpec.allocHistory,NMPPS_MALLOC_LIMIT>>4);
		nmppsMallocSpec.timeBest=-1;
		return 0;
	}
	
}