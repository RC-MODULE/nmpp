#include <aura/aura.h>
#include <ion/ion.h>

#include "nmpp.h"

/*


void aura_arm_nmppsFwdFFT256(struct aura_node *n )
{
	int src[512];
	int tst[512];
	int i;
	src[0]=1;
	tst[0]=1;
	for(i=1; i<512; i++){
	    src[i]=i;
	}
	
	int ret;
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "FFT256Fwd", &retbuf, src);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	int* dst=aura_buffer_get_bin(retbuf,256*2*4);

	//for(i=0; i<256; i++){
	//   if (dst[i]!=tst[i])
	//      slog(0, SLOG_ERROR, "ARM: test  aura_arm_nmppsAbs_s32_256 is NOT ok: [%d] %d vs %d",i, dst[i], tst[i]); 
	//}
	aura_buffer_release(n, retbuf);
	slog(0, SLOG_INFO, "ARM: TEST aura_arm_nmppsFFT256Fwd is ok");
}

void aura_arm_nmppsSum_s32_256(struct aura_node *n )
{
	int vec[256];
	int i;
	int check_value=0;
	for(i=0; i<256; i++){
	    vec[i]=i;
	    check_value+=i;
	}
	
	int ret;
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "Sum_s32_256", &retbuf, vec);
	if (ret != 0) 
		BUG(n, "Call failed!");

	uint32_t v = aura_buffer_get_u32(retbuf);
	if (v != check_value)
	{
		slog(0, SLOG_ERROR, "test  aura_nmppsSum_s32_256 is NOT ok: %dx vs %dx", v, check_value); 
	}
	aura_buffer_release(n, retbuf);
	slog(0, SLOG_INFO, "ARM: TEST nmppsSum_s32_256 is ok");
}


void aura_arm_nmppsAbs_s32_256(struct aura_node *n )
{
	int src[256];
	int tst[256];
	int i;
	src[0]=1;
	tst[0]=1;
	for(i=1; i<256; i++){
	    if (src[i-1]>0)
	      src[i]=-src[i-1]-1;
	    else 
	      src[i]=-src[i-1]+1;
	    
	    if (src[i]>0)
		tst[i]=src[i];
	    else 
		tst[i]=-src[i];
	    //slog(0, SLOG_INFO, "ARM: test  aura_arm_nmppsAbs_s32_256 : [%d] %d vs %d",i, src[i], tst[i]); 
	}
	
	int ret;
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "Abs_s32_256", &retbuf, src);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	int* dst=aura_buffer_get_bin(retbuf,256*4);

	for(i=0; i<256; i++){
	    if (dst[i]!=tst[i])
	      slog(0, SLOG_ERROR, "ARM: test  aura_arm_nmppsAbs_s32_256 is NOT ok: [%d] %d vs %d",i, dst[i], tst[i]); 
	}
	aura_buffer_release(n, retbuf);
	slog(0, SLOG_INFO, "ARM: TEST aura_arm_nmppsAbs_s32_256 is ok");
}

void aura_arm_nmppsAbs_s32(struct aura_node *n , int size )
{
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*4);
	int* src=iobuf_src->data;
	int* dst=iobuf_dst->data;
	int* tst=malloc(size*4);
	int i;
	src[0]=1;
	tst[0]=1;
	for(i=1; i<size; i++){
	    if (src[i-1]>0)
	      src[i]=-src[i-1]-1;
	    else 
	      src[i]=-src[i-1]+1;
	    
	    if (src[i]>0)
		tst[i]=src[i];
	    else 
		tst[i]=-src[i];
	    //slog(0, SLOG_INFO, "ARM: test  aura_arm_nmppsAbs_s32_256 : [%d] %d vs %d",i, src[i], tst[i]); 
	}
	
	int ret;
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "Abs_s32", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	//int* dst=aura_buffer_get_in(retbuf,256*4);

	for(i=0; i<size; i++){
	    if (dst[i]!=tst[i])
	      slog(0, SLOG_ERROR, "ARM: test  aura_arm_nmppsAbs_s32 is NOT ok: [%d] %d vs %d",i, dst[i], tst[i]); 
	}
	aura_buffer_release(n, retbuf);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, iobuf_dst);
	free(tst);
	slog(0, SLOG_INFO, "ARM: TEST aura_arm_nmppsAbs_s32 is ok");
}


void aura_arm_nmppsAdd_s32W(struct aura_node *n )
{
	uint32_t src0[256];
	uint32_t src1[256];
	uint32_t tst[256];
	
	int i;
	 
	src0[0]=1;
	tst[0]=1;
	for(i=0; i<256; i++){
	    src0[i]=i;
	    src1[i]=1000+i;
	    tst [i]=src0[i]+src1[i];
	    //slog(0, SLOG_INFO, "ARM: test  aura_arm_nmppsAdd_s32_256 : [%d] %d  %d",i, src0[i], src1[i]); 
	}
	
	int ret;
	struct aura_buffer *retbuf; 
	//slog(0, SLOG_DEBUG, "a 0x%x b 0x%x", (uint32_t) src0, (uint32_t) src1);
	ret = aura_call(n, "Add_s32_256", &retbuf, (uint32_t) src0, (uint32_t) src1);
	if (ret != 0) 
	    BUG(n, "Call failed!");
	//aura_hexdump("retbuf", retbuf->data, retbuf->size);
	int* dst=aura_buffer_get_bin(retbuf,256*4);

	for(i=0; i<256; i++){
	    if (dst[i]!=tst[i])
	      slog(0, SLOG_ERROR, "ARM: test  aura_arm_nmppsAdd_s32_256 is NOT ok: [%d] %d vs %d",i, dst[i], tst[i]); 
	}
	aura_buffer_release(n, retbuf);
	slog(0, SLOG_INFO, "ARM: TEST aura_arm_nmppsAdd_s32_256 is ok");
}

*/

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

	//aura_arm_nmppsAbs_s32(n,256);
	//aura_arm_nmppsFwdFFT256(n);
	//aura_arm_nmppsAbs_s32_256(n);
	//aura_arm_nmppsAdd_s32_256(n);
	//aura_arm_nmppsSum_s32_256(n);
	
	int src0[16];
	int src1[16];
	int dst[16];
	int i=0;
	for(i=0; i<16; i++){
		src0[i]=i;
		src1[i]=i-15;
	}
	nmppsAdd_32s(src0,src1,dst,16);
	for(i=0; i<16; i++){
		printf("%d\r\n",dst[i]);
	}
	
	nmppsAbs_32s(dst,dst,16);
	nm32sc in[256];
	nm32sc out[256];
	//nmppsFFT256Fwd(in,out);
	
	for(i=0; i<16; i++){
		printf("%d\r\n",dst[i]);
	}
	printf("===========\n");
	aura_close(n);
	
	slog (0, SLOG_INFO, "Finished");

	return 0;
}


