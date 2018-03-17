#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define 		CONST			   7
#define 		SIZE			 128

int main()
{
	nm32fcr* src = (nm32fcr*) nmppsMalloc_32fcr(SIZE);
	nm32fcr* dst  = (nm32fcr*) nmppsMalloc_32fcr(SIZE);

	unsigned crc = 0;

	for(int i = 0; i < SIZE; i++) {
		src[i].re = i;
		src[i].im = 0;
		dst[i].re = 0;
		dst[i].im = 0;
	}

	for(int i = 2; i < SIZE; ++i) {
		nmppsAddC_32fcr(src, dst, CONST, i);
		nmppsCrcAcc_32f((float*)dst, 0, 2 * i, &crc);
	}

	free(src);
	free(dst);

	return crc >> 2;
}