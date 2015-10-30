#include "nmplv.h"
int nmppsSadV16_8s(nm8s* pVec1,nm8s* pVec2)
{
	int nSad=0;
	for(int i=0;i<16;i++)
		nSad+=char(ABS(char(pVec1[i]-pVec2[i])));
	return nSad;
}


int nmppsSadV16_16s(nm16s* pVec1,nm16s* pVec2)
{
	int nSad=0;
	for(int i=0;i<16;i++)
		nSad+=short(ABS(short(pVec1[i]-pVec2[i])));
	return nSad;
}
