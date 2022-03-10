#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define 				SIZE					256

int main()
{
	nm32s* src_32s = (nm32s*) nmppsMalloc_32s(SIZE);
	nm32f* dst_32f = (nm32f*) nmppsMalloc_32f(SIZE);

	for(int i = 0; i < SIZE; i++) {
		src_32s[i] = i;
	}

	for(int i = 0; i < SIZE; i++) {
		dst_32f[i] = i;
	}

	unsigned crc = 0;

	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		nmppsConvert_32s32f(src_32s, dst_32f, iSize);
		nmppsCrcAcc_32f(dst_32f, 0, SIZE, &crc);
	}

	nmppsFree(src_32s);
	nmppsFree(dst_32f);

	return crc >> 2;
}

// crc = 223351351
