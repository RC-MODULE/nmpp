#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 1024
#define EXT 20
#ifdef __GNUC__ //  NMC-GCC C++ compilier 
double buffer_a[SIZE+EXT] __attribute__ ((section (".data_imu1")));
double buffer_b[SIZE+EXT] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double buffer_a[SIZE+EXT];
#pragma data_section ".data_imu2"
double buffer_b[SIZE+EXT];
#endif 

int main(){
	int i;
	unsigned crc=0;
	//nmppsRandUniform_64f(buffer_a,SIZE);
	//nmppsRandUniform_64f(buffer_b,SIZE);
	//initialisation
	for(i=0;i<SIZE+EXT;i++){
		buffer_a[i] = i;	
		buffer_b[i] = 100-i;
	}

	printf("TEST HAS BEEN STARTED\n");
	//case 1
	for(i=0;i<SIZE;i++){
		nmblas_dswap(i,buffer_a,1,buffer_b,1);
	}
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER ONE HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	//case 2 
	for(i=SIZE;i=0;i--){
		nmblas_dswap(i,buffer_a,1,buffer_b,1);
	}
	crc = nmppsCrcAcc_64f(buffer_b,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER TWO HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	for(i=1;i<6;i++){
		nmblas_dswap(SIZE/5,buffer_a,i,buffer_b,i);
	}
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b+EXT,0,SIZE,&crc);
	printf("TEST PATTERN NOMBER 3 HAS FINISHED\n");
	printf("RESULT OF FIRST CRC TEST PATTERN IS %d \n",crc);
	for(i=1;i<6;i++){
		nmblas_dswap(SIZE/5,buffer_a,i,buffer_b,6-i);
	}
	printf("TEST PATTERN NOMBER 4 HAS FINISHED\n");
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}

