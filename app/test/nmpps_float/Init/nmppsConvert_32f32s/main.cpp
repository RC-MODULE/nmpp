#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define 				SIZE					256

int main()
{
	nm32f* src_32f = (nm32f*) nmppsMalloc_32f(SIZE);
	nm32s* dst_32s = (nm32s*) nmppsMalloc_32s(SIZE);

	for(int i = 0; i < SIZE; i++) {
		src_32f[i] = i;
	}

	for(int i = 0; i < SIZE; i++) {
		dst_32s[i] = i;
	}

	unsigned crc = 0;

	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		nmppsConvert_32f32s(src_32f, dst_32s, iSize);
		nmppsCrcAcc_32s(dst_32s, SIZE, &crc);
	}

	nmppsFree(src_32f);
	nmppsFree(dst_32s);

	return crc >> 2;
}

// crc = 342391388
