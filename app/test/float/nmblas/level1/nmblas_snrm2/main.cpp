#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"

#define SIZE 1024

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
float buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
float buffer_a[SIZE];
#endif 

int main(){

	int i=0;
	int r;
	unsigned crc=0;
	float result =0;
	nmppsRand_32f(buffer_a,SIZE,-10,10);
/*	for(i=0;i<SIZE;i++){
		buffer_a[i] = i;	
	}
*/	
	printf("TEST HAS BEEN STARTED\n");
///////////////////////////////////////////////////////////////////////////case 1	
	for(i=0;i<SIZE;i++){
		result = nmblas_snrm2(i,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,13,1,&crc);
	}
	printf("TEST PATTER NUMBER 0 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
///////////////////////////////////////////////////////////////////////////case 2	
	for(i=SIZE;i>=0;i--){
		result = nmblas_snrm2(i,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,13,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
///////////////////////////////////////////////////////////////////////////case 3	
	for(i=0;i<6;i++){
		result = nmblas_snrm2(20,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,13,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
///////////////////////////////////////////////////////////////////////////case 4	
	for(i=0;i<6;i++){
		result = nmblas_snrm2(40,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,13,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

