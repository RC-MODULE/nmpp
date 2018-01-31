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
	unsigned int result =0;
	unsigned crc=0;
	
	//nmppsRand_32f(buffer_a,SIZE,-100,100);
	nmppsRand_32f(buffer_a,SIZE/4,0,100);
	nmppsRand_32f(buffer_a+SIZE/4,SIZE/4,-200,200);
	nmppsRand_32f(buffer_a+SIZE/2,SIZE/4,100,1000);
	nmppsRand_32f(buffer_a+3*SIZE/4,SIZE/4,-1000,2000);
	//
//	int* pointer;
/*	for(i=0;i<SIZE;i++){
		pointer = (int*)&buffer_a[i];
		printf("the ARR_X[%d] is %0x fpu is %f \n",i,*pointer,buffer_a[i]);
		//printf("the ARR_X[%d] is %f\n",i,buffer_a[i]);
	}
//	return(10);
*/	
	printf("TEST HAS BEEN STARTED\n");
//////////////////////////////////////////////////////////////////////////////////////case 1 
	for(i=0;i<SIZE;i++){
		result = nmblas_isamax(i,buffer_a,1);
		//printf("the result[%d] is %d\n",i,result);
		crc = nmppsCrcAcc_32u(&result,1,&crc);
	}

	printf("TEST PATTER NUMBER 1 HAS FINISHED\n");
	printf("CURRENT CRC IS %d\n",crc);
//////////////////////////////////////////////////////////////////////////////////////case 2	

	for(i=0;i<6;i++){
		result = nmblas_isamax(20,buffer_a,1);
		crc = nmppsCrcAcc_32u(&result,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	
	for(i=0;i<6;i++){
		result = nmblas_isamax(40,buffer_a,1);
		crc = nmppsCrcAcc_32u(&result,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	
	return crc>>2;
}

