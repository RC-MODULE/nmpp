#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"


#define SIZE 10

#ifdef __GNUC__ // NMC-GCC C++ compilier 
double x[SIZE] __attribute__ ((section (".mem_bank1")));
double y[SIZE] __attribute__ ((section (".mem_bank2")));
#else 			// NMSDK C++ compiler
#pragma data_section ".mem_bank1"
double x[SIZE];
#pragma data_section ".mem_bank2"
double y[SIZE];
#endif 


int main(){
	for(int i=0;i<SIZE;i++){
		x[i] = i;
		y[i] = i;
		printf("x[%d]=%f y[%d]=%f\n",i,x[i],i,y[i]);
	}
	
	double result = nmblas_ddot(SIZE,x,1,y,1);
	printf("result=%f\n",result);

	return result;
}

