 #include "nmplv.h"





//!
//! \perfinclude _IMG_ReleaseObject__FPl.html
//!

void IMG_ReleaseObject(nm64s* kernel)
{
	nmppsFree(kernel);
}
