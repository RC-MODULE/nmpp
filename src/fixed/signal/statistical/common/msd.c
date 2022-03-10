#include "nmtype.h"
//#include <math.h>
float nmppsMSD_32sc(const nm32sc* x0, const nm32sc* x1, int size)
{
	int i;
	float msdF;
	nm32sc err;
	long long msd64=0;
	
	for(i=0; i<size; i++){
		err.re= x0[i].re-x1[i].re;
		err.im= x0[i].im-x1[i].im;
		msd64+=err.re*err.re+err.im*err.im;
	}
	msdF=msd64;
	msdF/=size;
	//return sqrt(msdF);
	return (msdF);
}

