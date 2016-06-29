#include "fft2.h"
#include "rpc-host.h"	



	void nmppsFFT256Fwd(const nm32sc* src, nm32sc* dst,const  NmppsFFTSpec* spec)
	{
		clock_t t0,t1,t2,t3;
		t0=clock();
		int ret;	
		int size=256;
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
			BUG(n, "Call nmppsFFT256Fwd failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*k);
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src); 
		aura_buffer_release( retbuf); 
		t3=clock();
		//slog(0, SLOG_INFO, "ARM: Call nmppsFFT256Fwd -ok"); 

	}

	int nmppsFFT256FwdInitAlloc( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings)
	{
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 256*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 256*8);	
		struct aura_buffer *retbuf; 
		int ret =  aura_call(n, "nmppsFFT256FwdInitAlloc", &retbuf,  iobuf_src, iobuf_dst, settings); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT256FwdInitAlloc failed!"); 
		}
		*spec = (NmppsFFTSpec*) aura_buffer_get_u32(retbuf);
		ret   = aura_buffer_get_u32(retbuf);
		aura_buffer_release( iobuf_src); 
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256FwdInitAlloc -ok"); 
		return ret;
	}

