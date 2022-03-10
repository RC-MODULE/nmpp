#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"
#include <math.h>
#define SIZE 1024

double buffer_a[SIZE];

int main(){

	int i=0;
	double result =0;
	nmppsRandUniform_64f(buffer_a,SIZE,-10,10);
	unsigned long long* pointer;
/*	for(i=0;i<SIZE;i++){
		//buffer_a[i] = ceil(buffer_a[i]);
		//printf("%f\n",buffer_a[i]);
		pointer = (unsigned long long*)&buffer_a[i];
		printf("[%d] %llx\nmpp",i,*pointer);
	}
*/	
	printf("TEST HAS BEEN STARTED\n");
	unsigned crc=0;
	for(i=0;i<SIZE;i++){
		result = nmblas_dasum(i,buffer_a,1);
		//printf("the resalt[%d] is %f\n",i,result);
		crc = nmppsCrcAcc_64f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_dasum(20,buffer_a,1);
		crc = nmppsCrcAcc_64f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	for(i=0;i<6;i++){
		result = nmblas_dasum(40,buffer_a,1);
		crc = nmppsCrcAcc_64f(&result,10,1,&crc);
	}
	printf("TEST PATTER NUMBER 3 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

