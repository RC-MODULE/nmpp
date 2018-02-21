#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nmblas.h"
#include "nmpp.h"

#define SIZE 1024

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
double buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double buffer_a[SIZE];
#endif 

int main(){

	int i=0;
	int r;
	double result =0;
	nmppsRandUniform_64f(buffer_a,SIZE,-100,100);
	/*for(i=0;i<SIZE;i++){
		buffer_a[i] = i;	
	}*/
	printf("TEST HAS BEEN STARTED\n");
	unsigned crc=0;
	for(i=0;i<SIZE;i++){
		result = nmblas_dnrm2(i,buffer_a,1);
		//printf("the resalt[%d] is %f\n",i,result);
		crc = nmppsCrcAcc_64f(&result,16,1,&crc);
	}
	//return crc>>2;
	printf("TEST PATTER NUMBER 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_dnrm2(20,buffer_a,i);
		crc = nmppsCrcAcc_64f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_dnrm2(40,buffer_a,i);
		crc = nmppsCrcAcc_64f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

