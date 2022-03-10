#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 1024

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
float buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
float buffer_b[SIZE] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
float buffer_a[SIZE];
#pragma data_section ".data_imu2"
float buffer_b[SIZE];
#endif 

int main(){

	int i=0;
	int r;
	float result =0;
	unsigned crc=0;
	///initialisation
	nmppsRand_32f(buffer_a,SIZE,-10,10);
	nmppsRand_32f(buffer_b,SIZE,-10,10);

	printf("TEST HAS BEEN STARTED\n");
//////////////////////////////////////////////////////////////case 1
	for(i=0;i<SIZE;i++){
		result = nmblas_sdsdot(i,i,buffer_a,1,buffer_b,1);
		crc = nmppsCrcAcc_32f(&result,0,1,&crc);
	}
	printf("THE PATTERN NUMBER 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
//////////////////////////////////////////////////////////////case 2 
	for(i=SIZE;i>=0;i--){
		result = nmblas_sdsdot(i,i,buffer_a,1,buffer_b,1);
		crc = nmppsCrcAcc_32f(&result,0,1,&crc);
	}
	printf("THE PATTERN NUMBER 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
////////////////////////////////////////////////////////////// case 3 
	for(i=0;i<6;i++){
		result = nmblas_sdsdot(20,i,buffer_a,1,buffer_b,1);
		crc = nmppsCrcAcc_32f(&result,0,1,&crc);
	}
	printf("THE PATTERN NUMBER 3 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
///////////////////////////////////////////////////////////// case 4	
	for(i=0;i<6;i++){
		result = nmblas_sdsdot(20,-i,buffer_b,1,buffer_a,1);
		crc = nmppsCrcAcc_32f(&result,0,1,&crc);
	}
	printf("THE PATTERN NUMBER 4 HAS FINISHED\n");
	printf("THE FINAL CRC %d\n",crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

