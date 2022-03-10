 #include "nmpp.h"



#ifdef __cplusplus
		extern "C" {
#endif



//!
//! \perfinclude _nmppiReleaseObject__FPl.html
//!

void nmppiReleaseObject(nm64s* kernel)
{
	nmppsFree(kernel);
}



#ifdef __cplusplus
		};
#endif