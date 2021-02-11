#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "time.h"


#define SIZE 1600

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
	for(int i=0;i<SIZE;i++){
		x[i] = i;
		y[i] = 0;
		printf("x[%d]=%f\ty[%d]=%f\n",i,x[i],i,y[i]);
	}
	clock_t t0,t1;
	t0=clock();
	nmblas_dcopy(SIZE,x,2,y,1);
	t1=clock();
	for(int i=0;i<SIZE;i++){
		printf("y[%d]=%f\n",i,y[i]);
	}
	//return t1-t0;
	return 0;
}

