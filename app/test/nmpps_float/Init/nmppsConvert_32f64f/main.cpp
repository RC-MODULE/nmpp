#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>
#include <stdio.h>

#define 				SIZE					256

int main()
{
	nm32f* src_32f = (nm32f*) nmppsMalloc_32f(SIZE);
	nm64f* dst_64f = (nm64f*) nmppsMalloc_64f(SIZE + 11);

	for(int i = 0; i < SIZE; i++) {
		src_32f[i] = i;
	}

	for(int i = 0; i < SIZE + 11; i++) {
		dst_64f[i] = 777;
	}

	unsigned crc = 0;

	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		nmppsConvert_32f64f(src_32f, dst_64f, iSize);
		nmppsCrcAcc_64f(dst_64f, 0, SIZE + 11, &crc);
	}

	// for(int i = 0; i < SIZE + 11; i++) {
	// 	printf("%f\n", dst_64f[i]);
	// }

	nmppsFree(src_32f);
	nmppsFree(dst_64f);

	return crc >> 2;
}

// crc = 438322565
