#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"


#define SIZE 10

#ifdef __GNUC__ // NMC-GCC C++ compilier 
double x[SIZE] __attribute__ ((section (".data_imu1")));
double y[SIZE] __attribute__ ((section (".data_imu2")));
#else 			// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double x[SIZE];
#pragma data_section ".data_imu2"
double y[SIZE];
#endif 


int main(){
	printf("Input:\n");
	for(int i=0;i<SIZE;i++){
		x[i] = i;
		y[i] = i;
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	
	double alpha =2;
	//y=alpha * x + y
	nmblas_daxpy(SIZE,alpha,x,1,y,1);
	printf("Result:\n");
	for(int i=0;i<SIZE;i++){
		printf("y[%d]=%f\n",i,y[i]);
	}

	return 0;
}

