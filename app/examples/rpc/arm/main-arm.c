#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"
#include "fft2.h"

struct aura_node *n;
int main() {

	slog_init(NULL, 0);

	int ret; 
	n = aura_open("nmc", "./rpc-demo.abs");
	if (!n) {
		slog (0, SLOG_ERROR, "Failed to open node");
		exit(1);
	}
	aura_wait_status(n, AURA_STATUS_ONLINE);

	
	int src0_32s[512];
	int src1_32s[16];
	int dst_32s[512];
	int i=0;
	for(i=0; i<16; i++){
		src0_32s[i]=i-7;
		src1_32s[i]=i-15;
	}

	signed char src0_8s[32];
	signed short src0_16s[32];
	signed char src1_8s[32];
	signed char dst_8s[32];
	signed short dst_16s[32];
	for(i=0; i<32; i++){
		src0_8s[i]=i-7;
		src0_16s[i]=i-7;
		src0_32s[i]=i-7;
	}

	
//	nmppsAbs_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,8);
//	nmppsAbs_16s((nm16s*)dst,(nm16s*)dst,16);
//	nmppsAbs_32s((nm32s*)dst,(nm32s*)dst,16);
//	nmppsAbs_64s((nm64s*)dst,(nm64s*)dst,16);
//	
//	nmppsAddC_8s ((nm8s* )src0_8s,10,(nm8s* )dst_8s,16);	
//	for(i=0; i<16; i++){
//		printf("[ARM] addC_8s: %d %d\r\n",src0_8s[i],dst_8s[i]);
//	}
//	
//	nmppsAddC_16s((nm16s*)src0_16s,100,(nm16s*)dst_16s,16);
//	
//	for(i=0; i<16; i++){
//		printf("[ARM] addC_16s: %d %d\r\n",src0_16s[i],dst_16s[i]);
//	}

	int min;
//	nmppsMin_8s ((nm16s*)src0_8s,32, &min);printf("min=%d\r\n",min);
//	nmppsMin_16s((nm16s*)src0_16s,32,&min);printf("min=%d\r\n",min);
//	nmppsMin_32s((nm16s*)src0_32s,32,&min);printf("min=%d\r\n",min);
//	//nmppsMin_64s((nm16s*)src0_16s,16,&min);
//
//	nmppsMax_8s ((nm16s*)src0_8s,32, &min);printf("max=%d\r\n",min);
//	nmppsMax_16s((nm16s*)src0_16s,32,&min);printf("max=%d\r\n",min);
//	nmppsMax_32s((nm16s*)src0_32s,32,&min);printf("max=%d\r\n",min);
	//nmppsMin_64s((nm16s*)src0_16s,16,&min);

	
//	nmppsAddC_16s((nm16s*)src0,1,(nm16s*)dst,16);
//	nmppsAddC_32s((nm32s*)src0,1,(nm32s*)dst,16);
//	//nmppsAddC_64s((nm64s*)src0,1,(nm64s*)dst,16);
//	
//	nmppsSubC_8s ((nm8s* )src0,1,(nm8s* )dst,16);
//	nmppsSubC_16s((nm16s*)src0,1,(nm16s*)dst,16);
//    nmppsSubC_32s((nm32s*)src0,1,(nm32s*)dst,16);
//	//nmppsSubC_64s((nm64s*)src0,1,(nm64s*)dst,16);
//	
//	nmppsRShiftC_8s ((nm8s* )src0,1,(nm8s* )dst,16);
//	nmppsRShiftC_16s((nm16s*)src0,1,(nm16s*)dst,16);
//    nmppsRShiftC_32s((nm32s*)src0,1,(nm32s*)dst,16);
//	nmppsRShiftC_64s((nm64s*)src0,1,(nm64s*)dst,16);
//	
//	for(i=0; i<16; i++){
//		printf("%d\r\n",dst[i]);
//	}
//	
	//=====================
	int handleFwd256;
	nmppsFFT256FwdInitAllocH(src0_32s, dst_32s, &handleFwd256);
	nmppsFFT256FwdH((nm32sc*)src0_32s,(nm32sc*)dst_32s,handleFwd256);
	nmppsFFTFreeH(handleFwd256);
	//====================
	
	printf("===========\n");
	aura_close(n);
	
	slog (0, SLOG_INFO, "Finished");

	return 0;
}


