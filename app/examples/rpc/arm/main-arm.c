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

	
	int src0[512];
	int src1[16];
	int dst[512];
	int i=0;
	for(i=0; i<16; i++){
		src0[i]=i;
		src1[i]=i-15;
	}

	signed char src0_8s[32];
	signed char src1_8s[32];
	signed char dst_8s[32];
	for(i=0; i<32; i++){
		src0_8s[i]=i-7;
		dst_8s[i]=0xCC;
	}

//	nmppsAdd_8s ((nm8s* )src0,(nm8s* )src1,(nm8s* )dst,16);	
//	nmppsAdd_16s((nm16s*)src0,(nm16s*)src1,(nm16s*)dst,16);
//	nmppsAdd_32s((nm32s*)src0,(nm32s*)src1,(nm32s*)dst,16);
//	nmppsAdd_64s((nm64s*)src0,(nm64s*)src1,(nm64s*)dst,16);
//	
//	nmppsSub_8s ((nm8s* )src0,(nm8s* )src1,(nm8s* )dst,16);
//	nmppsSub_16s((nm16s*)src0,(nm16s*)src1,(nm16s*)dst,16);
//	nmppsSub_32s((nm32s*)src0,(nm32s*)src1,(nm32s*)dst,16);
//	nmppsSub_64s((nm64s*)src0,(nm64s*)src1,(nm64s*)dst,16);
	
	nmppsAbs_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,8);
	
	nmppsAbs1_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,8);
	nmppsAbs1_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,16);
	nmppsAbs1_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,32);
	
	//nmppsAbs_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,16);
	//nmppsAbs_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,24);
	//nmppsAbs_8s ((nm8s* )src0_8s,(nm8s* )dst_8s,32);
	
	for(i=0; i<32; i++){
		printf("[ARM] abs8: %d %d\r\n",src0_8s[i],dst_8s[i]);
	}

	
//	nmppsAbs_16s((nm16s*)dst,(nm16s*)dst,16);
//	nmppsAbs_32s((nm32s*)dst,(nm32s*)dst,16);
//	nmppsAbs_64s((nm64s*)dst,(nm64s*)dst,16);
//	
//	nmppsAddC_8s ((nm8s* )src0,1,(nm8s* )dst,16);	
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
	/*
	NmppsFFTSpec spec;
	fseq64 route;
	nmppsFFT256FwdOptimize((nm32sc*)src0,(nm32sc*)dst, &route);
	
	nmppsMallocSetRouteMode(route);
	nmppsFFT256FwdInitAlloc(nmppsMalloc32, nmppsFree, &spec);
	nmppsFFT256Fwd((nm32sc*)src0,(nm32sc*)dst,&spec);
	nmppsFFTFree(&spec);
	*/
	//====================
	
	printf("===========\n");
	aura_close(n);
	
	slog (0, SLOG_INFO, "Finished");

	return 0;
}


