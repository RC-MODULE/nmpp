//#include "vec.h"
#include "nmpp.h"
//*****************************************************************************
void nmppsSplitTmp_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc, nm8s* tmpSizeofDst)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_16s(const nm16s* src, nm16s* dst1, nm16s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_32s(const nm32s* src, nm32s* dst1, nm32s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

