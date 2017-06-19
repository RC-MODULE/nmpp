//#include "fft.h"
#include "time.h"
#include "malloc32.h"
#include "math.h"
#include "nmpp.h"

#include "fft.h"

#ifndef PI
#define PI 3.14159265359
#endif



//#include "rpc-host.h"	


	
	void nmppsFFT32Free(NmppsFFTSpec* spec )
	{
	//#ifdef RPC
		//RPC_HOST_I("nmppsFFTFree",(int)spec);	
	//#else
		if (spec){
			nmppsFree(spec->buffer[0]);
			nmppsFree(spec->buffer[1]);
			//spec->free(spec->buffer[2]);
			//spec->free(spec->buffer[3]);
			nmppsFree(spec->fftTable[0]);
		}
	//#endif
		
	}	

/*
	void nmppsFFT32Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
	{
	#ifdef RPC
		clock_t t0,t1,t2,t3;
		t0=clock();
		int ret;	
		int size=32;
		int k=8;
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	
		memcpy(iobuf_src->data,src,size*k);	
		struct aura_buffer *retbuf; 
		t1=clock();
		ret = aura_call_raw(n, 2, &retbuf,  iobuf_src, iobuf_dst, spec); 
		t2=clock();
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT32Fwd failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*k);
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src); 
		aura_buffer_release( retbuf); 
		t3=clock();
		printf("[ARM: NMC] wrap=%d call=%d\r\n",t1-t0+t3-t2,t2-t1);
		slog(3, SLOG_INFO, "ARM: Call nmppsFFT32Fwd -ok"); 
	#else 
		FFT_Fwd32(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);

	#endif

	
	}
*/

	nm32sc fixW32(int arg, int max){
		nm32sc res;
		double argIm= -2.0*PI/32.0*arg;
		double expRe= cos(argIm)*max+0.5;
		double expIm= sin(argIm)*max+0.5;
		res.re= floor(expRe);
		res.im= floor(expIm);
		res.re= res.re > (max-1) ? (max-1):res.re;
		res.im= res.im > (max-1) ? (max-1):res.im;
		return res;
	}

	int nmppsFFT32FwdInitAlloc(  NmppsFFTSpec* spec, int settings)
	{
		int i,k,p;
		int round [4];
		spec->buffer[0]  =nmppsMalloc_32sc(32);
		spec->buffer[1]  =nmppsMalloc_32sc(32);
		spec->fftTable[0]=nmppsMalloc_8s(16*16*2*2);
		spec->shift [0]=7;
	
		round[0]=1<< (spec->shift[0]-1);
		spec->free=free;
		
		if (spec->fftTable[0]==0) 	return -1;
		if (spec->buffer[0]==0) 	return -1;
		if (spec->buffer[1]==0) 	return -1;
		i=0;
		if (settings==-1)
			return 0;
		for(k=0; k<32; k+=2){
			for(p=0; p<8; p++,i++){
				nm32sc w=fixW32(p*k,128);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i,w.re);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256,w.im);
			}
		}
		for(k=0; k<32; k+=2){
			for(p=8; p<16; p++,i++){
				nm32sc w=fixW32(p*k,128);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i,w.re);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256,w.im);
			}
		}

		for(k=1; k<32; k+=2){
			for(p=0; p<8; p++,i++){
				nm32sc w=fixW32(p*k,128);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256,w.re);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256+256,w.im);
			}
		}
		
		for(k=1; k<32; k+=2){
			for(p=8; p<16; p++,i++){
				nm32sc w=fixW32(p*k,128);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256,w.re);
				nmppsPut_8s((nm8s*)spec->fftTable[0],i+256+256,w.im);
			}
		}
	
		return 0;
	}

/*
	int nmppsFFT32FwdInitAlloc( NmppsFFTSpec* spec,  int settings)
	{
#ifdef RPC
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 32*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 32*8);	
		struct aura_buffer *retbuf; 
		int ret =  aura_call(n, "nmppsFFT32FwdInitAlloc", &retbuf,  iobuf_src, iobuf_dst, settings); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT32FwdInitAlloc failed!"); 
		}
		*spec = (NmppsFFTSpec*) aura_buffer_get_u32(retbuf);
		ret   = aura_buffer_get_u32(retbuf);
		aura_buffer_release( iobuf_src); 
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( retbuf); 
		slog(3, SLOG_INFO, "ARM: Call nmppsFFT32FwdInitAlloc -ok"); 
		return ret;
#else
		int ret;
		if (settings&NMPP_OPTIMIZE_DISABLE){}
		else {
			//!fseq64 allocRoute;
			//!ret=nmppsFFT32FwdOptimize(src, dst, &allocRoute);
			//!nmppsMallocSetRouteMode(allocRoute); 
		}
		ret = nmppsFFT32FwdInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
		return ret;
#endif
	}
	*/
/*
	int nmppsFFT32FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
	{
		unsigned heapIndx0;
		unsigned heapIndx1;
		fseq64   route;
		*allocOrder=0xFFFFFF00;
		clock_t t0,t1,bestTime=0x1000000;

		for(heapIndx0=0; heapIndx0<4; heapIndx0++){
			for(heapIndx1=0; heapIndx1<4; heapIndx1++){


				route =0xF0|(heapIndx1<<4)|(heapIndx0); 
				//!nmppsMallocSetRouteMode(route);
				NmppsFFTSpec* spec;
				if (nmppsFFT32FwdInitAllocCustom(&spec, nmppsMalloc32, nmppsFree, NMPP_OPTIMIZE_DISABLE )==NMPP_OK){
					t0=clock();
					nmppsFFT32Fwd((nm32sc*)src, (nm32sc*)dst, spec);
					t1=clock();

					if (bestTime>t1-t0){
						bestTime=t1-t0;
						//!nmppsMallocGetHistory(allocOrder,2);
					}
				}
				nmppsMallocSpec.status=0;
				nmppsFFTFree(spec);
			}
		}
		if (bestTime<0x1000000)	return NMPP_OK;
		else					return NMPP_ERROR;
	}
*/	




