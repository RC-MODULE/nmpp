#include <stdio.h>
#include <stdlib.h>
#include "nmblas.h"
#include "nmpp.h"
#include <math.h>
#define ROWS 50
#define COLLUMS 50
#define OFFSET 5

#pragma data_section ".my_data_2"
double matrix[ROWS+OFFSET][COLLUMS+OFFSET];
#pragma data_section ".my_data_3"
double x[COLLUMS+OFFSET];
#pragma data_section ".my_data_3"
double y[ROWS+OFFSET];

//void nmblas_sgemv(
//   const enum nm_trans           TRANS,
//   const int                  M,rows in case notrans
//   const int                  N,
//   const double               ALPHA,
//   const double               * A,
//   const int                  LDA,
//   const double               * X,
//   const int                  INCX,
//   const double               BETA,
//   double                     * Y,
//   const int                  INCY
//);


int main(){
   //initialisation
   int i,j,z;
   int *pointer;
   unsigned crc=0;
   double temp;
   nmppsRandUniform_64f((double*)matrix,((ROWS+OFFSET)*(COLLUMS+OFFSET)),-10,10);
   nmppsRandUniform_64f(x,COLLUMS+OFFSET,-5,5);
   nmppsRandUniform_64f(y,ROWS+OFFSET,-10,10);
   printf("crc of matrix,x and y to prevent mismach betwine rounding at deffernt architectures\n");
   crc = nmppsCrcAcc_64f((double*)matrix,0,((ROWS+OFFSET)*(COLLUMS+OFFSET)),&crc);
   printf("matrix crc is      %d \n",crc);
   crc = nmppsCrcAcc_64f(y,0,(ROWS+OFFSET),&crc);
   printf("y crc is           %d \n",crc);
   crc = nmppsCrcAcc_64f(x,0,(COLLUMS+OFFSET),&crc);
   printf("x crc is           %d \n",crc);
  
   for(i=0;i<ROWS;i++){
      for(j=0;j<COLLUMS;j++){
         temp = ceil(matrix[i][j]);
         matrix[i][j] = temp;
      }
   }
   
   for(i=0;i<ROWS;i++){
     temp = ceil(y[i]);
     y[i] = temp;
   }

   for(i=0;i<COLLUMS;i++){
     temp = ceil(x[i]);
     x[i] = temp;
   }
    
   for(i=0;i<ROWS;i++){
      for(j=0;j<COLLUMS;j++){
         nmblas_dgemv(nm_n,i,j,2,(double*)matrix,COLLUMS+OFFSET,x,1,-1,y,1);
         crc = nmppsCrcAcc_64f(y,0,(ROWS+OFFSET),&crc);
      }
   }

    for(i=0;i<ROWS;i++){
      for(j=0;j<COLLUMS;j++){
         nmblas_dgemv(nm_t,i,j,2,(double*)matrix,COLLUMS+OFFSET,x,1,-1,y,1);
         crc = nmppsCrcAcc_64f(y,0,(ROWS+OFFSET),&crc);
      }
   }

   return crc;
   
}
