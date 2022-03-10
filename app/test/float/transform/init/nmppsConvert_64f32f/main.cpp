#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>
#include <stdio.h>

#define 				SIZE					256

int main()
{
	nm64f* src_64f = (nm64f*) nmppsMalloc_64f(SIZE);
	nm32f* dst_32f = (nm32f*) nmppsMalloc_32f(SIZE + 11);

	for(int i = 0; i < SIZE; i++) {
		src_64f[i] = i;
	}

	for(int i = 0; i < SIZE + 11; i++) {
		dst_32f[i] = 777;
	}

	unsigned crc = 0;

	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		nmppsConvert_64f32f(src_64f, dst_32f, iSize);
		nmppsCrcAcc_32f(dst_32f, 0, SIZE + 11, &crc);
	}

	// for(int i = 0; i < SIZE + 11; i++) {
	// 	printf("%f\n", dst_32f[i]);
	// }

	nmppsFree(src_64f);
	nmppsFree(dst_32f);

	return crc >> 2;
}

// crc = 438322565
