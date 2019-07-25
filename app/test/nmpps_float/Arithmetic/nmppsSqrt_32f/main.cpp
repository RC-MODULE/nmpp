#include <nmtype.h>
#include <nmpp.h>

#define    SIZE                         11


#ifdef __GNUC__
__attribute__((section(".data_imu1"))) 	nm32f src[SIZE];
__attribute__((section(".data_imu2"))) 	nm32f dst[SIZE + 10];
__attribute__((section(".data_imu3"))) 	nm32f tmp[SIZE];
#else
nm32f src[SIZE];
nm32f dst[SIZE + 10];
nm32f tmp[SIZE];
#endif

int main()
{
	unsigned crc = 0;
	
	for(int i = 0; i < SIZE; i++) {
		src[i] = i * i;
	}

	for(int i = 0; i < SIZE + 10; i++) {
		dst[i] = 777;
	}


	for(int size = 2; size < SIZE; size += 2){
		nmppsSqrt_32f(src, dst, tmp, size);
		nmppsCrcAcc_32f(dst, 0, size + 10, &crc);
	}

	return crc >> 2;
}