#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

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
	unsigned crc=0;
	int* pointer;
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-10,10);
	
/*	for(i=0;i<SIZE+EXT;i++){
		pointer = (int*)&buffer_a[i];
		printf("buffer_a[%d] is %0x\n",i,*pointer);
		pointer = (int*)&buffer_b[i];
		printf("buffer_b[%d] is %0x\n",i,*pointer);
	}
*/
	//initialisation
/////////////////////////////////////////////////////////////////////////// case 1 
	printf("TEST HAS BEEN STARTED\n");
	for(i=0;i<SIZE;i++){
		nmblas_scopy(i,buffer_a,1,buffer_b,1);
	}
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER ONE HAS FINISHED\n");
	printf("THE RESULT OF THE 1st CRC TEST PATTERN IS %d \n",crc);

/////////////////////////////////////////////////////////////////////////// case 2 
	for(i=SIZE;i=0;i--){
		nmblas_scopy(i,buffer_a,1,buffer_b,1);
	}
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER TWO HAS FINISHED\n");
	printf("THE RESULT OF THE 2nd CRC TEST PATTERN IS %d \n",crc);
///////////////////////////////////////////////////////////////////////////// case 3	
	for(i=0;i<SIZE;i++){
		nmblas_scopy(i,buffer_b,1,buffer_a,1);
	}
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER 3 HAS FINISHED\n");
	printf("THE RESULT OF THE 3rd CRC TEST PATTERN IS %d \n",crc);

/////////////////////////////////////////////////////////////////////////// case 2 
	for(i=SIZE;i=0;i--){
		nmblas_scopy(i,buffer_b,1,buffer_a,1);
	}
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	printf("TEST PATTERN NOMBER 4 HAS FINISHED\n");
	printf("THE RESULT OF THE 4th CRC TEST PATTERN IS %d \n",crc);
	return crc>>2;
}

