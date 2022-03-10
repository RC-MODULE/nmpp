#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"

#define SIZE 1024

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
float buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
float buffer_b[SIZE] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
float buffer_a[SIZE];
#pragma data_section ".data_imu2"
float buffer_b[SIZE];
#endif 

int main(){

	int i=0;
	float result =0;
	unsigned crc=0;
	nmppsRand_32f(buffer_a,SIZE,-10,10);
	int* pointer;
	/*for(i=0;i<SIZE;i++){
		pointer = (int*)&buffer_a[i]; 
		printf("arr_a[%d] %0x\n",i,*pointer);
	}
	return 100;*/

	printf("TEST HAS BEEN STARTED\n");
	for(i=0;i<SIZE;i++){
		result = nmblas_sasum(i,buffer_a,1);
		//printf("the resalt[%d] is %f\n",i,result);
		crc = nmppsCrcAcc_32f(&result,14,1,&crc);
	}
	printf("TEST PATTER NUMBER 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_sasum(20,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_sasum(40,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

