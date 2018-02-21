#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 1024
#define EXT 30
double buffer_a[SIZE+EXT];
double buffer_b[SIZE+EXT];
double param[10];

int main(){
	int i;
	unsigned crc=0;
	//nmppsRandUniform_64f(param,10,0,0.5);
	param[1] = 0.707;//h11
	param[2] = -0.707;//h21
	param[3] = 0.707;//h12
	param[4] = 0.707;//h22
	nmppsRandUniform_64f(buffer_a,SIZE+EXT,-20,20);
	nmppsRandUniform_64f(buffer_b,SIZE+EXT,-20,20);
///////////////////////////////////////////////////////////////////////////////	case 1 
	param[0] = -2; 
	printf("PARAM is -2\n");
	printf("TEST 1 HAS BEEN STARTED FLAG IS -2\n");
	
	for(i=0;i<SIZE;i++){
		nmblas_drotm(i,buffer_a,1,buffer_b,1,param);
	}
	
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,0,SIZE+EXT,&crc);
	
	printf("RESULT OF 1st CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
////////////////////////////////////////////////////////////////////////////// case 2
	param[0] = -1; 
	printf("PARAM is -1\n");
	printf("TEST 2 HAS BEEN STARTED FLAG IS -1\n");

	for(i=0;i<SIZE;i++){
		nmblas_drotm(i,buffer_a,1,buffer_b,1,param);
	}
	
	crc = nmppsCrcAcc_64f(buffer_b,21,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_a,21,SIZE+EXT,&crc);

	printf("RESULT OF 2nd CRC TEST PATTERN IS %d \n",crc);
	printf("\n"); 
///////////////////////////////////////////////////////////////////////////////// case 3
	param[0] = 0; 
	printf("PARAM is 0\n");
	printf("TEST 3 HAS BEEN STARTED FLAG IS 0\n");
	
	for(i=0;i<SIZE;i++){
		nmblas_drotm(i,buffer_a,1,buffer_b,1,param);
	}
	
	crc = nmppsCrcAcc_64f(buffer_a,22,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,22,SIZE+EXT,&crc);
	
	printf("RESULT OF 3rd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
//////////////////////////////////////////////////////////////////////////////// case 4 
	param[0] = 1; 
	printf("PARAM is 1\n");
	printf("TEST 4 HAS BEEN STARTED FLAG IS 1\n");
	
	for(i=0;i<SIZE;i++){
		nmblas_drotm(i,buffer_a,1,buffer_b,1,param);
	}
	
	crc = nmppsCrcAcc_64f(buffer_a,19,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,19,SIZE+EXT,&crc);
	
	printf("RESULT OF 4rd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
///////////////////////////////////////////////////////////////////////////////// case 5
	nmppsRandUniform_64f(buffer_a,SIZE+EXT,-10,10);
	nmppsRandUniform_64f(buffer_b,SIZE+EXT,-10,10);
	printf("PARAM is -1 defferent offset are being tested\n");
	param[0] = -1;

	for(i=1;i<9;i++){
		nmblas_drotm(50,buffer_a,i,buffer_b,9-i,param);
	}

	crc = nmppsCrcAcc_64f(buffer_a,20,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,20,SIZE+EXT,&crc);
	
	for(i=1;i<9;i++){
		nmblas_drotm(50,buffer_a,9-i,buffer_b,i,param);
	}
	crc = nmppsCrcAcc_64f(buffer_a,15,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,15,SIZE+EXT,&crc);
	
	printf("RESULT OF 4rd CRC TEST PATTERN IS %d \n",crc);
	printf("\n");
	return crc >> 2;
}
	