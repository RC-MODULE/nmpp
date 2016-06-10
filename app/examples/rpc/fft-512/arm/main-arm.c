#define __STDC_FORMAT_MACROS
#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"
#include "fft2.h"

struct aura_node *n;
int main() {

	printf("START-%s\n", aura_get_version());
	slog_init(NULL, 0);
       sleep(1);
	int ret; 
		n = aura_open("nmc", "./rpc-demo.abs");
	if (!n) {
		printf("ERROR:Failed to open node\n");
		slog (0, SLOG_ERROR, "Failed to open node");
		exit(1);
	}

	aura_wait_status(n, AURA_STATUS_ONLINE);
	
	static int   src0_32s[2*512] ;
	signed int 	 dst_32s[2*512];
	int i=0;
	unsigned crc=-1;
	//=====================
	
	for(i=0; i<512*2; i++){
		src0_32s[i]=i/2;
		dst_32s[i]=0;
	}

	//src0_32s[0]=1000;
	//src0_32s[1]=1000;
	//src0_32s[2]=1000;
	//src0_32s[3]=1000;
	//src0_32s[4]=1000;
	//src0_32s[5]=1000;
	//src0_32s[6]=1000;
	//src0_32s[7]=1000;
	
	//--------- forward FFT ------------
	NmppsFFTSpec* specFwd512;
	ret=nmppsFFT512FwdInitAlloc(&specFwd512, src0_32s, dst_32s, 0);
	if (ret){
		printf("ERROR: NMC Memory allocation error in nmppsFFT512FwdInitAlloc!\n");
		aura_close(n);
		return -1;
	}
	uint64_t t0,t1;
	nmppsFFT512Fwd((nm32sc*)src0_32s,(nm32sc*)dst_32s,specFwd512);
	nmppsFFTFree(specFwd512);
	//--------- inverse FFT ------------
	NmppsFFTSpec *specFFTInv512;
	ret=nmppsFFT512InvInitAlloc(&specFFTInv512, src0_32s, dst_32s, NMPP_OPTIMIZE_DISABLE);
	if (ret){
		printf("ERROR: NMC Memory allocation error in nmppsFFT512InvInitAlloc!\n");
		aura_close(n);
		return -1;
	}
	nmppsFFT512Inv((nm32sc*)dst_32s,(nm32sc*)src0_32s,specFFTInv512);
	nmppsFFTFree(specFFTInv512);
	
	for(i=0; i<64; i++){
		printf("[inv:%d] %d %d\r\n",i,src0_32s[i*2] ,src0_32s[i*2+1]);
	}
	
	aura_close(n);
	slog (0, SLOG_INFO, "Finished");
	printf("CRC=%x\n",crc);
	return crc-0xc354a8e4;
}


