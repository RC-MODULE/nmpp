 #include "nmpp.h"





//!
//! \perfinclude _nmppiReleaseObject__FPl.html
//!

void nmppiReleaseObject(nm64s* kernel)
{
	nmppsFree(kernel);
}
