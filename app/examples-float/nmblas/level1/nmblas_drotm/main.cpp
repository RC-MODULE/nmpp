#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nmblas.h"


#define SIZE 10
#define PI 3.1415

#ifdef __GNUC__ // NMC-GCC C++ compilier 
double x[SIZE] __attribute__ ((section (".data_imu1")));
double y[SIZE] __attribute__ ((section (".data_imu2")));
#else 			// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double x[SIZE];
#pragma data_section ".data_imu2"
double y[SIZE];
#endif 

double param[5];
int main(){
	int i;

	param[1] = 0.707;//h11
	param[2] = -0.707;//h21
	param[3] = 0.707;//h12
	param[4] = 0.707;//h22


	for(int i=0;i<SIZE;i++){
		x[i] = 10*sin(PI/6*i);
		y[i] = 10*cos(PI/6*i);
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	printf("\n");
///////////////////////////////////////////////////////////////////////////////	case 1 
	param[0] = -2; 
	printf("PARAM is -2\n");
	nmblas_drotm(SIZE,x,1,y,1,param);

	for(int i=0;i<SIZE;i++){
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	printf("\n");
////////////////////////////////////////////////////////////////////////////// case 2
	param[0] = -1; 
	printf("PARAM is -1\n");

	nmblas_drotm(SIZE,x,1,y,1,param);

	for(int i=0;i<SIZE;i++){
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	printf("\n");

///////////////////////////////////////////////////////////////////////////////// case 3
	param[0] = 0; 
	printf("PARAM is 0\n");
	nmblas_drotm(SIZE,x,1,y,1,param);
	
	for(int i=0;i<SIZE;i++){
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	printf("\n");
//////////////////////////////////////////////////////////////////////////////// case 4 
	param[0] = 1; 
	printf("PARAM is 1\n");
	nmblas_drotm(SIZE,x,1,y,1,param);
	
	
	for(int i=0;i<SIZE;i++){
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	printf("\n");
	return 1;
}
	