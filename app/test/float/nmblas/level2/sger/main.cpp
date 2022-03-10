#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"
#include <math.h>

#define ROWS 100
#define COLLUMS 140
#define OFFSET 10

//#pragma data_section ".data_imu1"
float matrix[ROWS+OFFSET][COLLUMS+OFFSET];
//#pragma data_section ".data_imu3"
float x[COLLUMS+OFFSET];
//#pragma data_section ".data_imu4"
float y[ROWS+OFFSET];

int main(){
  int i,j;
  unsigned crc=0;
  float temp;
  nmppsRand_32f((float*)matrix,((COLLUMS+OFFSET)*(ROWS+OFFSET)),-10,10);
  nmppsRand_32f(x,COLLUMS+OFFSET,-10,10);
  nmppsRand_32f(y,ROWS+OFFSET,-10,10);

  printf("INIT MATRIX\n");
  int* matrix_pntr = (int*)matrix;
  for(i=0;i<ROWS+OFFSET;i++){
    for(j=0;j<COLLUMS+OFFSET;j++){
      matrix[i][j] = ceil(matrix[i][j]);
    }
  
  }
  printf("INIT VEXTORS\n");
  for(i=0;i<ROWS+OFFSET;i++){
     temp = ceil(y[i]);
     y[i] = temp;
  }
  for(i=0;i<COLLUMS+OFFSET;i++){
     temp = ceil(x[i]);
     x[i] = temp;
  }

  for(i=2;i<ROWS;i += 2){
      for(j=2;j<COLLUMS;j += 2){
         nmblas_sger(i,j,2,x,1,y,1,(float*)matrix,COLLUMS+OFFSET);
         crc = nmppsCrcAcc_32f(y,0,(ROWS+OFFSET),&crc);
         //printf("N_matrix[%d][%d] crc = %x\n",i,j,crc);
      }
   }   
  
  printf("FINAL crc = %x\n",crc);
  return crc;
}
