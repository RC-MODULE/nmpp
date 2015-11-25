#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <easynmc/easynmc.h>
#include <easynmc/aura.h>
//#include "nmpp.h"
#include "fft.h"
// #include "malloc32.h"
unsigned int *pinmux  = (unsigned int *) 0x0800CC21;
unsigned int *port    = (unsigned int *) 0x0800A403;
unsigned int *ddr     = (unsigned int *) 0x0800A407;

void aura_panic() { 
	for (;;) { 
		*port ^= (1<<6);	
		*port ^= (1<<7);	
	} ;
}

void aura_hexdump (char *desc, unsigned int *addr, int len) {
	int i; 
	for (i=0; i<len; i++) { 
		printf("0x%x: 0x%x\n", ((unsigned int)addr << 2), *addr);
		addr++;
	}
}

//#define RPC_NMC_PPI(callid,func,src,dst,size)
/*
void rpc_nmppsAbs_s32(void *in, void *out)
{
	int i=0;
	int sum=0;
	
	aura_buffer buf_src = aura_get_buf();
	nm32s *ptr  =aura_buffer_to_ptr(buf_src);
	aura_buffer buf_dst = aura_get_buf();
	nm32s *dst =aura_buffer_to_ptr(buf_dst);	
	unsigned size = aura_get_u32();
	
	nmppsAbs_s32(src,dst,size);
	printf("NMC: hello from aura_nmc_nmppsAbs_s32_256\n");
	
}

void rpc_nmppsAdd_s32(void *in, void *out)
{
	aura_buffer buf_src0 = aura_get_buf();
	aura_buffer buf_src1 = aura_get_buf();
	nm32s *src0  =aura_buffer_to_ptr(buf_src0);
	nm32s *src1  =aura_buffer_to_ptr(buf_src1);
	aura_buffer buf_dst = aura_get_buf();
	nm32s *dst =aura_buffer_to_ptr(buf_dst);	
	unsigned size = aura_get_u32();
	
	nmppsAdd_s32(src0,src1,dst,size);
	printf("NMC: hello from aura_nmc_nmppsAdd_s32\n");
	
}


void rpc_nmppsFFT256Fwd(void *in, void *out)
{
	int i=0;
	int sum=0;
	nm32sc *dst ;	
	nm32sc *src = aura_get_bin(256*2*4);
	
	clock_t t0,t1,t;
	
	
	dst= nmppsMalloc32(256*2*4);	

	NmppsFFTSpec spec;
	fseq64 route;
	nmppsFFT256FwdOptimize(src,dst, &route);
	
	nmppsMallocSetRouteMode(route);
	nmppsFFT256FwdInitAlloc(nmppsMalloc32, nmppsFree, &spec);
	t0=clock();
	nmppsFFT256Fwd(src,dst,&spec);
	t1=clock();
	t=t1-t0;
	nmppsFFTFree(&spec);
	printf("NMC: route is: 0x%X \n", route);
	printf("NMC: Time is: %d\n", t);

	printf("NMC: hello from aura_nmc_nmppsFFT256Fwd\n");
	aura_put_bin(dst, 256*4);
	nmppsFree(dst);
}*/

int main(int argc, char **argv)
{
	printf("NMC: Aura RPC demo \n");
	aura_init();
	aura_loop_forever();

}

