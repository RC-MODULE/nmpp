#include "nmpp.h"
#include "nmpp-cpp.h"
#include "nmblas.h"
#include "time.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

__attribute__((section(".mem_bank0"))) long long im0[2048];
__attribute__((section(".mem_bank1"))) long long im1[2048];
__attribute__((section(".mem_bank2"))) long long im2[2048];
__attribute__((section(".mem_bank3"))) long long im3[2048];
__attribute__((section(".mem_bank4"))) long long im4[2048];
__attribute__((section(".mem_bank5"))) long long im5[2048];
//__attribute__((section(".mem_bank6"))) long long im6[2048];
//__attribute__((section(".mem_bank7"))) long long im7[2048];

__attribute__((section(".data_ddr"))) long long emi[4096];


int main()
{
  return 0;
}