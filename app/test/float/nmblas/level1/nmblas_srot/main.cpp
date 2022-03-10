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
	//long long* pnt2result;
	unsigned crc=0;
	int *pointer;
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-10,10);
	printf("TEST HAS BEEN STARTED\n");
	printf("\n");
////////////////////////////////////////////////////////////////////////////case 1 60 degree	
	//60
	printf("CASE 1 rotation 60 degree\n");
	for(i=0;i<SIZE;i++){
		nmblas_srot(i,buffer_a,1,buffer_b,1,0.5,0.866);
	}
	crc = nmppsCrcAcc_32f(buffer_a,16,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,16,SIZE+EXT,&crc);
	printf("RETURN CRC FROM CASE 1 IS  %d\n",crc);
	
	/*for(i=0;i<SIZE+EXT;i++){
		pointer = (int*)&buffer_a[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
		pointer = (int*)&buffer_b[i];
		printf("arr_a[%d] %0x\n",i,*pointer);
	}*/
///////////////////////////////////////////////////////////////////////////////case 2 45 
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-10,10);
	printf("CASE 1 rotation 45 degree\n");
	for(i=SIZE;i!=0;i--){
		nmblas_srot(i,buffer_a,1,buffer_b,1,0.707,0.707);
	}

	crc = nmppsCrcAcc_32f(buffer_a,18,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,18,SIZE+EXT,&crc);
	printf("RETURN CRC FROM CASE 2 IS  %d\n",crc);
	
	//nmblas_srot(SIZE,buffer_a,1,buffer_b,1,0.707,0.707);

	return crc;
//////////////////////////////////////////////////////////////////////////////case 2 45 degree
	/*printf("CASE 2 rotation 45 degree\n");
	for(i=0;i<SIZE;i++){
		nmblas_srot(i,buffer_a,1,buffer_b,1,0.707,0.707);
	}
	crc = nmppsCrcAcc_32f(buffer_a,10,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,10,SIZE+EXT,&crc);
	crc = crc>>2;
	printf("RETURN CRC FROM CASE 2 IS  %d\n",crc);
	printf("\n");

///////////////////////////////////////////////////////////////////////////////////case 3 45 degree
	printf("CASE 3 rotation 45 degree deferent offsets\n");
	for(i=1;i<9;i++){
		nmblas_srot(50,buffer_a,9-i,buffer_b,i,0.707,0.707);
	}
	crc = nmppsCrcAcc_32f(buffer_a,10,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,10,SIZE+EXT,&crc);
	crc = crc>>2;
	printf("RETURN CRC FROM CASE 3 IS  %d\n",crc);
	printf("\n");
	printf("CASE 4 rotation 45 degree deferent offsets\n");
	for(i=1;i<9;i++){
		nmblas_srot(50,buffer_a,i,buffer_b,9-i,0.707,0.707);
	}
	crc = nmppsCrcAcc_32f(buffer_a,10,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,10,SIZE+EXT,&crc);
	crc = crc>>2;
	printf("RETURN CRC FROM CASE 4 IS  %d\n",crc);
	printf("\n");*/
}

