#include "malloc32.h"
#include "nmplv/vSupport.h"
#include "nmplv/vInit.h"


int nmppsMallocResetRoute(){
	if (nmppsMallocResetPos())
		return nmppsMallocSpec.status;
	else{
		nmppsSet_64u ((nm64u*)nmppsMallocSpec.route,0,  NMPPS_MALLOC_LIMIT>>4);		
		nmppsSet_64u ((nm64u*)nmppsMallocSpec.bestRoute,0xFFFFFFFFFFFFFFFF,  NMPPS_MALLOC_LIMIT>>4);		
		nmppsSet_64u ((nm64u*)nmppsMallocSpec.allocHistory,0,NMPPS_MALLOC_LIMIT>>4);
		nmppsMallocSpec.timeBest=-1;
		return 0;
	}
	
}