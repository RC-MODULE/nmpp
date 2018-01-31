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
	//long long* pnt2result;
	unsigned crc=0;
	nmppsRandUniform_64f(buffer_a,SIZE+EXT,-20,20);
	nmppsRandUniform_64f(buffer_b,SIZE+EXT,-10,10);
	printf("TEST HAS BEEN STARTED\n");
	printf("\n");

	/*for(i=0;i<SIZE+EXT;i++){
		printf("the x[%d] is  %f\n",i,buffer_a[i]);
		printf("the y[%d] is  %f\n",i,buffer_b[i]);
	}*/


////////////////////////////////////////////////////////////////////////////////////case 60 degree 
	printf("CASE 1 rotation 60 degree\n");
	for(i=0;i<SIZE;i++){
		nmblas_drot(i,buffer_a,1,buffer_b,1,0.5,0.866);
	}
	crc = nmppsCrcAcc_64f(buffer_a,0,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,0,SIZE+EXT,&crc);
	crc = crc>>2;
	printf("RETURN CRC FROM CASE 1 IS  %d\n",crc);
	printf("\n");

	/*for(i=0;i<SIZE+EXT;i++){
		printf("the x[%d] is  %f\n",i,buffer_a[i]);
		printf("the y[%d] is  %f\n",i,buffer_b[i]);
	}*/

//////////////////////////////////////////////////////////////////////////////////////case 2  45 degree 
	printf("CASE 2 rotation 45 degree\n");
	for(i=0;i<SIZE;i++){
		nmblas_drot(i,buffer_a,1,buffer_b,1,0.707,0.707);
	}

	/*for(i=0;i<SIZE+EXT;i++){
		printf("the x[%d] is  %f\n",i,buffer_a[i]);
		printf("the y[%d] is  %f\n",i,buffer_b[i]);
	}*/
	
	crc = nmppsCrcAcc_64f(buffer_a,25,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,25,SIZE+EXT,&crc);
	crc = crc>>2;
	printf("RETURN CRC FROM CASE 2 IS  %d\n",crc);
	printf("\n");
	

///////////////////////////////////////////////////////////////////////////////////////case 3  45 degree and deferent offsets
	printf("CASE 3 rotation 45 degree deferent offsets\n");
	for(i=1;i<9;i++){
		nmblas_drot(50,buffer_a,9-i,buffer_b,i,0.707,0.707);
	}
	
	crc = nmppsCrcAcc_64f(buffer_a,25,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,25,SIZE+EXT,&crc);

	printf("RETURN CRC FROM CASE 3 IS  %d\n",crc);
	printf("\n");
	printf("CASE 4 rotation 45 degree deferent offsets\n");
	for(i=1;i<9;i++){
		nmblas_drot(50,buffer_a,i,buffer_b,9-i,0.707,0.707);
	}
	crc = nmppsCrcAcc_64f(buffer_a,21,SIZE+EXT,&crc);
	crc = nmppsCrcAcc_64f(buffer_b,21,SIZE+EXT,&crc);

	printf("RETURN CRC FROM CASE 4 IS  %d\n",crc);
	printf("\n");
	return(crc);
}

