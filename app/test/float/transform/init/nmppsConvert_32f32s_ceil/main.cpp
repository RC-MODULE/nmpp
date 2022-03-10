#include <nmtype.h>
#include <malloc32.h>
#include <stdio.h>
#include <nmpp.h>
#include <math.h>

#define 				SIZE			1024

#pragma data_section ".data_imu5"
	nm32f src_32f[SIZE];
#pragma data_section ".data_imu5"
	nm32s dst_32s[SIZE + 12];

	int Round(nm32f value)
	{	
		float v = 0.5 + value;
		return floor(v);
	}


void nmppsConvert_32f32s_ceiling2(const nm32f* pSrcVec, nm32s* pDstVec, int scale, int nSize)
	{
		int i;
		for (i = 0; i < nSize; i++) {
			float v = (pSrcVec[i]);
			v *= powf(2.0, scale);
			v = Round(-0.5-v);
			//v += 0.499999970198;
			//v = Round(v);
			v = -v;
			pDstVec[i] = v;
		}
	}

int main()
{
	unsigned crc = 0;
	for(int i = 0; i < SIZE + 11; i++) {
		dst_32s[i] = 777;
	}

	/*
	src_32f[0]  = 0.00000000;
	src_32f[1]  =-0.00000000;
	src_32f[2]  = 1.17549435082e-38;
	src_32f[3]  = 1.17549435082e-38;
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

	src_32f[40] = 0.1;
	src_32f[41] = 0.01;
	src_32f[42] = 0.001;
	src_32f[43] = 0.0001;
	src_32f[44] = 0.00001;
	src_32f[45] = 0.000001;
	src_32f[46] = 1e-7;
	src_32f[47] = 1e-8;
	src_32f[48] = 1e-9;
	src_32f[49] = 1e-10;


	for (int i = 0; i < 50; i++) {
		src_32f[50 + i] = -src_32f[i];
	}

	nmppsConvert_32f32s_ceiling(src_32f, dst_32s, 0, 100);
	nmppsCrcAcc_32s(dst_32s,100, &crc);

	for (int i = 0; i < 100; i++) {
		printf("%d nm_ceil(%.8e)=%d \t c_ceil=%f\n", i, src_32f[i], dst_32s[i], ceil(src_32f[i]));
	}
*/


	//nm32f* src_32f = (nm32f*) nmppsMalloc_32f(SIZE);
	//nm32s* dst_32s = (nm32s*) nmppsMalloc_32s(SIZE + 11);
	//nm32f* dst_32s = (nm32f*) nmppsMalloc_32f(SIZE + 11);
	//nmppsRand_32f(src_32f, SIZE, -5, 15);
	


	// float value = -5.01f;
	// for(int i = 0; i < SIZE; i++) {
	// 	src_32f[i] =  i / 7;
	// }

	// nmppsConvert_32f32s_ceiling(src_32f, dst_32s, 0, SIZE);
	// for(int i = 0; i < SIZE + 11-11; i++) {
	// 	printf("dst_32s[%d] = %d\n", i, dst_32s[i]);
	// }

//	int gr7 = 7;
//SIZE
	//return 5;
	for(int iSize = 2; iSize < SIZE; iSize += 2) {
		//int iSize=106;
		//printf ("%d---\n", iSize);
		int scale = 0;
		for(int scale = -10; scale < 10; scale++) {
			nmppsConvert_32f32s_ceiling(src_32f, dst_32s, scale, iSize);
			nmppsCrcAcc_32s(dst_32s, SIZE + 11, &crc);
			
		}
		
		
	}
	//return 3;



	// for(int i = 0; i < SIZE + 11; i++) {
	// 	printf("[%d] = %d\n", i, dst_32s[i]);
	// }
	// printf("\n");
	//
	
	return crc >> 2;
}
