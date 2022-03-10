#include "nmpp.h"
#include "nmtype.h"
#include "time.h"
#include <stdio.h>

#define     MAX_STEP     6
#define     N            1024
#define		COUNT        MAX_STEP * N

#pragma data_section ".data_imu1"
	v2nm32f in[COUNT];
#pragma data_section ".data_imu2"
	nm32s maskX[(N >> 5) + 5];
	nm32s maskY[(N >> 5) + 5];
#pragma data_section ".data_imu3"
	v2nm32f threshold;

int main()
{
  int tm;
  clock_t t1, t2;
  for(int i = 0; i < COUNT; i++) {
  	in[i].v0 = -16+i;
	in[i].v1 = -16+i;
  }

  for(int i = 0; i < (N >> 5) + 5; i++) {
  	maskX[i] = 0x55555555;
	maskY[i] = 0x55555555;
  }


  threshold.v0 = 1;
  threshold.v1 = 1;

  //printf("%x %f %f\n", &threshold, threshold.v0, threshold.v1);
  unsigned crcX = 0;
  unsigned crcY = 0;

  printf("\n");
  for(int step = 1; step <= MAX_STEP; step++) {
    for(int size = 1; size <= N; size+=1) {
	  threshold.v0 = size;
      threshold.v1 = size + step;

	nmppsCmpGteC_v2nm32f(in, &threshold, (nm1*)maskX, (nm1*)maskY, step, size);

    nmppsCrcAcc_32s(maskX, (N >> 5) + 5, &crcX);
 	nmppsCrcAcc_32s(maskY, (N >> 5) + 5, &crcY);
    }
  }

   printf("CRC_X = %d\n", crcX >> 2);
   printf("CRC_Y = %d\n", crcY >> 2);
   printf("\n");

  // for (int i = 0; i < (N >> 5) + 6; i++) {
	 //printf("maskX = 0x%x\n", maskX[i]);
  // }
  // printf("-----------------------\n");
  // for (int i = 0; i < (N >> 5) + 6; i++) {
	 //  printf("maskY = 0x%x\n", maskY[i]);
  // }

   t1 = clock();
   //nmppsCmpGteC_v2nm32f(in, (nm1*)maskX, (nm1*)maskY, threshold, 1, N);
   t2 = clock();
   printf("time = %d ticks (%d pairs)\n", t2 - t1, N);
   return 0;
}
