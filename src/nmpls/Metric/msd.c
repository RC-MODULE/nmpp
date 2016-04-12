#include "nmtype.h"

float nmppsMSD_32sc(nm32sc* x0,nm32sc* x1, int size)
{
	int i;
	float msdF;
	long long msd64=0;
	for(i=0; i<size; i++){
		msd64+=(x0[i].re-x1[i].re)*(x0[i].re-x1[i].re);
		msd64+=(x0[i].im-x1[i].im)*(x0[i].im-x1[i].im);
	}
	msdF=msd64;
	msdF/=size;
	return msdF;
}

