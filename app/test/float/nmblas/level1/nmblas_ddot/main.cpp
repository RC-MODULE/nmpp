#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 1024

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
double buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
double buffer_b[SIZE] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double buffer_a[SIZE];
#pragma data_section ".data_imu2"
double buffer_b[SIZE];
#pragma data_section ".data_imu3"
#endif 

int main(){

	int i=0;
	int r;
	double result =0;
	unsigned crc=0;
	nmppsRandUniform_64f(buffer_a,SIZE,-100,10);
	nmppsRandUniform_64f(buffer_b,SIZE,-100,10);
	
	///initialisation
//	for(i=0;i<SIZE;i++){
//		buffer_a[i] = i;
//		buffer_b[i] = 100-i;
//	}
	printf("TEST HAS BEEN STARTED\n");
	
	for(i=0;i<SIZE;i++){
		result = nmblas_ddot(i,buffer_a,1,buffer_b,1);
		crc = nmppsCrcAcc_64f(&result,17,1,&crc);
	}
	printf("THE PATTERN NUMBER 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_ddot(20,buffer_a,i,buffer_b,i);
		crc = nmppsCrcAcc_64f(&result,17,1,&crc);
	}
	printf("THE PATTERN NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_ddot(20,buffer_a,i,buffer_b,6-i);
		crc = nmppsCrcAcc_64f(&result,17,1,&crc);
	}
	printf("THE PATTERN NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

