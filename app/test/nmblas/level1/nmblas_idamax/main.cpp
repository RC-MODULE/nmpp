#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"

#define SIZE 1024
//unsigned int buff[1000];
#ifdef __GNUC__ //  NMC-GCC C++ compilier 
double buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double buffer_a[SIZE];
#endif 

int main(){

	int i=0;
	int r;
	unsigned int result =0;
	unsigned int crc=0;
	float *pointer;
	nmppsRandUniform_64f(buffer_a,SIZE,-30,30);
	buffer_a[947] =  -1000000;
	buffer_a[600]  = -845;
	buffer_a[10]  =  -45;
	buffer_a[30]  =  -68;
	buffer_a[50]  =  -101;
	buffer_a[70]  =   104;
	buffer_a[601]  = -845;
	buffer_a[567] =  -700;

	/*for(i=0;i<SIZE;i++){
		printf("THE ARR_X[%d]  %f\n",i,buffer_a[i]);
		printf("%llu\n",buffer_a[i]);
	}*/

/////////////////////////////////////////////////////////////////////// case 1 
	printf("TEST HAS BEEN STARTED\n");
	for(i=0;i<SIZE;i++){
		result = nmblas_idamax(i,buffer_a,1);
		//printf("ARR[%d] THE INDEX OF MAX IS  %d\n",i,result);
		nmppsCrcAcc_32u(&result,1,&crc);
		//pointer	= (float*)&result;
		//crc = nmppsCrcAcc_32f(pointer,0,1,&crc);	
	}
	printf("CURRENT CRC IS %d\n",crc);
	printf("TEST PATTER NUMBER 1 HAS FINISHED\n");
/////////////////////////////////////////////////////////////////////// case 2 
	
	for(i=0;i<6;i++){
		result = nmblas_idamax(20,buffer_a,i);
		//printf("THE INDEX OF MAX IS  %d\n",result);
		nmppsCrcAcc_32u(&result,1,&crc);
		//crc = nmppsCrcAcc_32f(pointer,0,1,&crc);
	}
	printf("CURRENT CRC IS %d\n",crc);
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
/////////////////////////////////////////////////////////////////////// case 3 
	
	for(i=0;i<6;i++){
		result = nmblas_idamax(SIZE/6,buffer_a,i);
		//printf("THE INDEX OF MAX IS  %d\n",result);
		nmppsCrcAcc_32u(&result,1,&crc);
		//crc = nmppsCrcAcc_32f(pointer,0,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
/////////////////////////////////////////////////////////////////////// case 4 
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;

}

