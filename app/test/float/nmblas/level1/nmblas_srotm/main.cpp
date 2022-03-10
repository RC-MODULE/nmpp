#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 1024
#define EXT 20

float buffer_a[SIZE+EXT];
float buffer_b[SIZE+EXT];

int main(){
	int i,j;
	unsigned crc=0;
	int* pointer;
	float param[5];
	///nmppsRand_32f(param,5,-10,10);
	param[1] = 0.707;//h11
	param[2] = -0.707;//h21
	param[3] = 0.707;//h12
	param[4] = 0.707;//h22
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-5,5);
//////////////////////////////////////////////////////////////////////////////////case 1
	param[0] = -2; 
	printf("TEST 1 HAS BEEN STARTED FLAG IS -2\n");
	printf("\n");
	
	for(i=0;i<SIZE;i++){
		nmblas_srotm(i,buffer_a,1,buffer_b,1,param);
	}
	crc = nmppsCrcAcc_32f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,0,SIZE+EXT,&crc);
	
	printf("TEST PATTERN NOMBER 1 HAS FINISHED\n");
	printf("RESULT OF 1st CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
//////////////////////////////////////////////////////////////////////////////////case 2
	param[0] = -1; 
	printf("TEST 2 HAS BEEN STARTED FLAG IS -1\n");
	printf("\n");
	for(i=0;i<SIZE;i++){
		nmblas_srotm(i,buffer_a,1,buffer_b,1,param);
	}
	crc = nmppsCrcAcc_32f(buffer_b,16,SIZE,&crc);
	crc = nmppsCrcAcc_32f(buffer_a,16,SIZE,&crc);
	printf("TEST PATTERN NOMBER 2 HAS FINISHED\n");
	printf("RESULT OF 2nd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");

//////////////////////////////////////////////////////////////////////////////////case 3
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-5,5);
	param[0] = 0; 
	param[1] = 10000000;//h11
	param[2] = 1000000;//h21
	param[3] = 0.00707;//h12
	param[4] = -0.00707;//h22
	printf("TEST 3 HAS BEEN STARTED FLAG IS 0\n");
	printf("\n");
	for(i=0;i<SIZE;i++){
		nmblas_srotm(i,buffer_a,1,buffer_b,1,param);
	}
	crc = nmppsCrcAcc_32f(buffer_a,7,SIZE,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,7,SIZE,&crc);
	printf("TEST PATTERN NOMBER 3 HAS FINISHED\n");
	printf("RESULT OF 3rd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
	return crc;
//////////////////////////////////////////////////////////////////////////////////case 4
	nmppsRand_32f(buffer_a,SIZE+EXT,-10,10);
	nmppsRand_32f(buffer_b,SIZE+EXT,-5,5);
	param[1] = 0.001;//h11
	param[2] = 1000;//h21
	param[3] = 200;//h12
	param[4] = 0.001;//h22

	param[0] = 1; 
	printf("TEST 3 HAS BEEN STARTED FLAG IS 1\n");
	printf("\n");
	for(i=0;i<SIZE;i++){
		nmblas_srotm(i,buffer_a,1,buffer_b,1,param);
	}
//	for(i=0;i<SIZE+EXT;i++){
//		printf("arr_a[%d] is %f\n",i,buffer_a[i]);
//		printf("arr_b[%d] is %f\n",i,buffer_b[i]);
//	}
	printf("TEST PATTERN NOMBER 4 HAS FINISHED\n");
	crc = nmppsCrcAcc_32f(buffer_a,10,SIZE,&crc);
	crc = nmppsCrcAcc_32f(buffer_b,10,SIZE,&crc);
	printf("RESULT OF 4rd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
	printf("TEST HAS BEEN FINISHED\n");

	return crc>>2;
}

