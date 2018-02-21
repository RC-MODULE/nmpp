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
 	unsigned int crc=0;
 	int *pointer;
 	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-10,10);
	//for(i=0;i<SIZE+EXT;i++){
	//	pointer = (int*)&buffer_a[i];
	//	printf("arr_a[%d] %0x\n",i,*pointer);
	//	pointer = (int*)&buffer_b[i];
	//	printf("arr_a[%d] %0x\n",i,*pointer);
	//}
//////////////////////////////////////////////////////// case 1	
	printf("TEST HAS BEEN STARTED\n");
	printf("case 1 \n");
	for(i=0;i<SIZE;i++){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
	//	printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);	
//////////////////////////////////////////////////////////////
	printf("case 2 \n");
	for(i=SIZE;i!=0;i--){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
	//	printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);	
///////////////////////////////////////////////////////////////////
	printf("case 3 \n");
	for(i=SIZE;i!=0;i--){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
	//	printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 3 HAS FINISHED\n");
	printf("current crc is %d\n",crc);	
	return crc;	
}




/*int main(){
	int i;
	unsigned crc=0;
	int* pointer;
	//initialisation
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-10,10);
	for(i=0;i<SIZE+EXT;i++){
		pointer = (int*)&buffer_a[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
		pointer = (int*)&buffer_b[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
	}
///////////////////////////////////////////////////////////case 0
	nmblas_sswap(SIZE,buffer_a,1,buffer_b,1);
	nmblas_sswap(SIZE,buffer_b,1,buffer_a,1);
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	for(i=0;i<SIZE+EXT;i++){
		pointer = (int*)&buffer_a[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
		pointer = (int*)&buffer_b[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
	}
////////////////////////////////////////////////////////////case 1	
	printf("TEST HAS BEEN STARTED\n");
	printf("case 1 \n");
	for(i=0;i<SIZE;i++){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
	//	nmblas_sswap(i,buffer_a,1,buffer_b,1);
		printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 1 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
////////////////////////////////////////////////////////////case 2	
	printf("case 2 \n");
	for(i=SIZE;i>=0;i--){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
		printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 2 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
//////////////////////////////////////////////////////////////case 3
	printf("case 3\n");
	for(i=0;i<200;i++){
		nmblas_sswap(i,buffer_a,1,buffer_b,1);
		printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 3 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
////////////////////////////////////////////////////////////case 4	
	printf("case 4\n");
	for(i=SIZE;i>=0;i--){
		nmblas_sswap(i,buffer_b,1,buffer_a,1);
		printf("%d\n",i);
	}
	printf("\n");
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	printf("TEST PATTERN 4 HAS FINISHED\n");
	printf("current crc is %d\n",crc);
	return crc>>2;

	printf("TEST HAS BEEN FINISHED\n");
	return crc>>2;
}*/

