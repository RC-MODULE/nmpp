#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include "nmpp.h"

#define SIZE 1024
#define EXT 20
#ifdef __GNUC__ //  NMC-GCC C++ compilier 
float buffer_a[SIZE+EXT] __attribute__ ((section (".data_imu1")));
float buffer_b[SIZE+EXT] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
float buffer_a[SIZE+EXT];
#pragma data_section ".data_imu2"
float buffer_b[SIZE+EXT];
#endif 

int main(){
	int i;
	unsigned int crc=0;
	int *pointer;	
	//initialisation
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
/////////////////////////////////////////////////////////////////////	
	printf("TEST HAS BEEN STARTED\n");
	//case 1
	for(i=0;i<SIZE;i++){
		nmblas_sscal(i,i,buffer_a,1);
	}

	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER ONE HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	//case 2 
	for(i=SIZE;i=0;i--){
		nmblas_sscal(i,-i,buffer_a,1);
	}
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER TWO HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	for(i=1;i<6;i++){
		nmblas_sscal(SIZE/5,4,buffer_a,1);
	}
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER 3 HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	for(i=1;i<6;i++){
		nmblas_sscal(SIZE/5,4,buffer_a,1);
	}
	printf("TEST PATTERN NOMBER 4 HAS FINISHED\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

