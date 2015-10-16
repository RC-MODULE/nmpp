#include "nmplv.h"
int VEC_SadV16(nm8s* pVec1,nm8s* pVec2)
{
	int nSad=0;
	for(int i=0;i<16;i++)
		nSad+=char(ABS(char(pVec1[i]-pVec2[i])));
	return nSad;
}


int VEC_SadV16(nm16s* pVec1,nm16s* pVec2)
{
	int nSad=0;
	for(int i=0;i<16;i++)
		nSad+=short(ABS(short(pVec1[i]-pVec2[i])));
	return nSad;
}
