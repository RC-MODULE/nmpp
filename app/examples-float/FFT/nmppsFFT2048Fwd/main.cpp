
/* The using example of forward FFT2048 for floating point */ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "nmtype.h"           // The type nm32fcr was declared here (здесь объявлен тип nm32fcr)
#include "fft_32fcr.h"


#define SIZE 2048

#ifdef __GNUC__ // NMC-GCC C++ compilier 
nm32fcr src[SIZE] __attribute__ ((section (".data_imu1")));
nm32fcr dst[SIZE] __attribute__ ((section (".data_imu2")));
#else 			// NMSDK C++ compiler
#pragma data_section ".data_imu1"
nm32fcr src[SIZE];
#pragma data_section ".data_imu2"
nm32fcr dst[SIZE];
#endif 


int main()
{
  // a generating a sin func
  // генерация функции синуса
  for(int i = 0; i < SIZE; i++) {
  	src[i].re = sinf(i);
	src[i].im = 0;
  }
  
  // a printing of first 10 src elements
  // печать первых 10 элементов src
  for(int i = 0; i < 10; i++) {
  	printf("src[%d].re = %f, src[%d].im = %f, \n", i, src[i].re, i, src[i].im);
  }
  
  printf("\n\n");
  
  // a special fft var which has to will is initialized by nmppsFFT2048InitAlloc_32fcr
  // специальная переменная БПФ, которая должна быть инициализирована с помощью nmppsFFT2048InitAlloc_32fcr
  NmppsFFTSpec_32fcr* spec;
  
  // an initializing of a special fft var
  // инициализация специальной переменной БПФ
  int ret_val = nmppsFFT2048FwdInitAlloc_32fcr(&spec);
  if(ret_val) {
	printf("Error %d!\n", ret_val);
	return 1;
  }
  
  // computing forward fft2048 from a generated sin func
  // вычисление прямого БПФ2048 от сгенерированной функции синуса
  nmppsFFT2048Fwd_32fcr(src, dst, spec);
  
  // a printing of first 10 dst elements
  // печать первых 10 элементов dst
  for(int i = 0; i < 10; i++) {
  	printf("dst[%d].re = %f, dst[%d].im = %f, \n", i, dst[i].re, i, dst[i].im);
  }
  
  return 0;
}

