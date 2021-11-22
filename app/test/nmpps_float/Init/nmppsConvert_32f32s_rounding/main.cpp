#include <nmtype.h>
#include <malloc32.h>
#include "nmpp.h"
#include <stdio.h>
#include <math.h>

#define 				SIZE					1024

int main()
{
	nm32f* src_32f = (nm32f*) nmppsMalloc_32f(SIZE);
	nm32s* dst_32s = (nm32s*) nmppsMalloc_32s(SIZE + 11);
	nmppsRand_32f(src_32f, SIZE, 5, -15);
	// for(int i = 0; i < SIZE; i++) {
	// 	src_32f[i] = float(i) / 0.09090909;
	// 	//src_32f[i] = 12.0f;
	// }

	for(int i = 0; i < SIZE + 11; i++) {
		dst_32s[i] = 777;
	}


	src_32f[0]  = 0.00000000;
	src_32f[1]  =-0.00000000;
	src_32f[2]  = 1.40129846432e-45;
	src_32f[3]  = 2.80259692865e-45;
	src_32f[4]  = 0.49999995;
	src_32f[5]  = 0.49999996;
	src_32f[6]  = 0.49999997;
	src_32f[7]  = 0.49999998;
	src_32f[8]  = 0.49999999;
	src_32f[9]  = 0.50000000;
	src_32f[10] = 0.50000001;
	src_32f[11] = 0.50000002;
	src_32f[12] = 0.50000003;
	src_32f[13] = 0.50000004;
	src_32f[14] = 0.99999995;
	src_32f[15] = 0.99999996;
	src_32f[16] = 0.99999997;
	src_32f[17] = 0.99999998;
	src_32f[18] = 0.99999999;
	src_32f[19] =  1.0000000;
	src_32f[20] =  1.00000011921;
	src_32f[21] =  1.00000023842;
	src_32f[22] =  1.00000035763;
	src_32f[23] =  1.0000004;
	src_32f[24] =  1.4999995;
	src_32f[25] =  1.4999996;
	src_32f[26] =  1.4999997;
	src_32f[27] =  1.4999998;
	src_32f[28] =  1.4999999;
	src_32f[29] =  1.5000000;
	src_32f[30] =  1.5000001;
	src_32f[31] =  1.5000002;
	src_32f[32] =  1.5000003;
	src_32f[33] =  1.5000004;
	src_32f[34] =  1.9999995;
	src_32f[35] =  1.9999996;
	src_32f[36] =  1.9999997;
	src_32f[37] =  1.9999998;
	src_32f[38] =  1.9999999;
	src_32f[39] =  2.0000000;

	for (int i = 0; i < 40; i++) {
		src_32f[40 + i] = -src_32f[i];
	}
	unsigned crc = 0;

	nmppsConvert_32f32s_rounding(src_32f, dst_32s, 0, 80);
	nmppsCrcAcc_32s(dst_32s,80, &crc);

	for (int i = 0; i < 80; i++) {
		printf("%d round(%.8f)=%d %f\n", i, src_32f[i], dst_32s[i], floor(src_32f[i]+0.5));
	}
	
	// nmppsConvert_32f32s_rounding(src_32f, dst_32s, -3, SIZE);
	// for(int i = 0; i < SIZE + 11-11; i++) {
	// 	printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
	// }

	//
	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		for(int scale = -10; scale < 11; scale++) {
			nmppsConvert_32f32s_rounding(src_32f, dst_32s, scale, iSize);
			nmppsCrcAcc_32s(dst_32s, SIZE + 11, &crc);
		}
		// for(int i = 0; i < SIZE; i++) {
		// 	printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
		// }
	}
	// nmppsConvert_32f32s_rounding(src_32f, dst_32s, SIZE);
	// for(int i = 0; i < SIZE + 11; i++) {
	// 	printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
	// }
	nmppsFree(src_32f);
	nmppsFree(dst_32s);

	return crc >> 2;
}

// crc = 342391388
