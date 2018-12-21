#include <nmtype.h>
#include <malloc32.h>
#include "nmpp.h"
#include <stdio.h>

#define 				SIZE					256

int main()
{
	nm32f* src_32f = (nm32f*) nmppsMalloc_32f(SIZE);
	nm32s* dst_32s = (nm32s*) nmppsMalloc_32s(SIZE + 11);

	for(int i = 0; i < SIZE; i++) {
		src_32f[i] = float(i) / 11.0f;
	}

	for(int i = 0; i < SIZE + 11; i++) {
		dst_32s[i] = i;
	}

	unsigned crc = 0;

	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		nmppsConvert_32f32s(src_32f, dst_32s, iSize);
		nmppsCrcAcc_32s(dst_32s, SIZE + 11, &crc);
		// for(int i = 0; i < SIZE; i++) {
		// 	printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
		// }
	}
	nmppsConvert_32f32s(src_32f, dst_32s, SIZE);
	for(int i = 0; i < SIZE + 11; i++) {
		printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
	}
	nmppsFree(src_32f);
	nmppsFree(dst_32s);

	return crc >> 2;
}

// crc = 342391388
