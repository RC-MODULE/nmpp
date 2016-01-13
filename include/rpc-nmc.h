typedef void (func_p_t)(void*);
typedef void*(func_i_p_t)(int);
typedef void (func_ppi_t)(void*,void*,int);
typedef int (func_ppi_i_t)(void*,void*,int);
typedef int (func_ppr_i_t)(void*,void*,int*);
typedef void (func_pppi_t)(void*,void*,void*,int);
typedef void (func_pipi_t)(void*,int,void*,int);
typedef void (func_plpi_t)(void*,long,void*,int);
typedef void (func_pip_t)(void*,int,void*);
typedef void (func_ppp_t)(void*,void*,void*);
typedef int  (func_ppp_i_t)(void*,void*,void*);

#include <time.h>

#define NMC_RPC_I_P(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	unsigned i = aura_get_u32(); \
	func_i_t *unifunc=(func_i_t*)func; \
	void* p=unifunc(i); \
	aura_put_u32((int)p); \
}

#define NMC_RPC_I(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	unsigned i = aura_get_u32(); \
	func_i_p_t *unifunc=(func_i_p_t*)func; \
	unifunc(i); \
}


#define NMC_RPC_PPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	clock_t t0,t1,t2; \
	t0=clock(); \
	aura_buffer buf_src = aura_get_buf(); \
	aura_buffer buf_dst = aura_get_buf(); \
	int *src = aura_buffer_to_ptr(buf_src); \
	int *dst = aura_buffer_to_ptr(buf_dst);	 \
	unsigned size = aura_get_u32(); \
	func_ppi_t *unifunc=(func_ppi_t*)func; \
	t1=clock(); \
	unifunc(src,dst,size); \
	t2=clock(); \
	printf("[NMC:]wrap=%d fft=%d\r\n",t1-t0,t2-t1); \
}

#define NMC_RPC_PPI_I(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src = aura_get_buf(); \
	aura_buffer buf_dst = aura_get_buf(); \
	int *src = aura_buffer_to_ptr(buf_src); \
	int *dst = aura_buffer_to_ptr(buf_dst);	 \
	unsigned size = aura_get_u32(); \
	func_ppi_i_t *unifunc=(func_ppi_i_t*)func; \
	int ret=unifunc(src,dst,size); \
	aura_put_u32(ret); \
}

	
	
#define NMC_RPC_PPPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_pppi_t *unifunc=(func_pppi_t*)func; \
	unifunc(src0,src1,dst,size); \
}

#define NMC_RPC_PIPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src  = aura_get_buf(); \
	unsigned val  = aura_get_u32(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src   = aura_buffer_to_ptr(buf_src); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_pipi_t *unifunc=(func_pipi_t*)func; \
	unifunc(src,val,dst,size); \
}



#define NMC_RPC_PLPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src  = aura_get_buf(); \
	unsigned long long val  = aura_get_u64(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src   = aura_buffer_to_ptr(buf_src); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_plpi_t *unifunc=(func_plpi_t*)func; \
	unifunc(src,val,dst,size); \
}

#define NMC_RPC_PPLI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src  = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	unsigned long long val  = aura_get_u64(); \
	int *src   = aura_buffer_to_ptr(buf_src); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_pipi_t *unifunc=(func_pipi_t*)func; \
}

//	printf("[NMC:]%x %x %x %x\r\n",src,val,dst,size);\
//	unifunc(src,val,dst,size); \

#define NMC_RPC_PPP(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_ppp_t *unifunc=(func_ppp_t*)func; \
	unifunc(src0,src1,dst); \
}

#define NMC_RPC_PPP_I(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	unsigned size = aura_get_u32(); \
	func_ppp_t *unifunc=(func_ppp_t*)func; \
	int ret = unifunc(src0,src1,dst); \
	aura_put_u32(ret); \
}


#define NMC_RPC_PIR(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	unsigned size = aura_get_u32(); \
	func_pip_t *unifunc=(func_pip_t*)func; \
	int ret ; \
	unifunc(src0,size,&ret); \
	aura_put_u32(ret); \
	printf("NMC: %d %d\t\n",size,ret); \
}

#define NMC_RPC_PPR_I(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	int handle=123; \
	aura_buffer buf_src  = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src   = aura_buffer_to_ptr(buf_src); \
	int *dst   = aura_buffer_to_ptr(buf_dst);  \
	func_ppr_i_t *unifunc=(func_ppr_i_t*)func; \
	int ret = unifunc(src,dst,&handle); \
	aura_put_u32(handle); \
	aura_put_u32(ret); \
}

	

#define NMC_RPC_PIR64(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	unsigned size = aura_get_u32(); \
	func_pip_t *unifunc=(func_pip_t*)func; \
	long ret ; \
	unifunc(src0,size,&ret); \
	aura_put_u64(ret); \
}


//--------------------------
#ifdef RPC_nmppsAbs_64s
NMC_RPC_PPI(nmppsAbs_64s);
#endif 

#ifdef RPC_nmppsAbs_32s
NMC_RPC_PPI(nmppsAbs_32s);
#endif 

#ifdef RPC_nmppsAbs_16s
NMC_RPC_PPI(nmppsAbs_16s);
#endif 

#ifdef RPC_nmppsAbs_8s
NMC_RPC_PPI(nmppsAbs_8s);
#endif 
//-------------------------
#ifdef RPC_nmppsAbs1_8s
NMC_RPC_PPI(nmppsAbs1_8s);
#endif 

#ifdef RPC_nmppsAbs1_16s
NMC_RPC_PPI(nmppsAbs1_16s);
#endif 

#ifdef RPC_nmppsAbs1_32s
NMC_RPC_PPI(nmppsAbs1_32s);
#endif 

#ifdef RPC_nmppsAbs1_64s
NMC_RPC_PPI(nmppsAbs1_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsAdd_8s
NMC_RPC_PPPI(nmppsAdd_8s);
#endif 

#ifdef RPC_nmppsAdd_16s
NMC_RPC_PPPI(nmppsAdd_16s);
#endif 

#ifdef RPC_nmppsAdd_32s
NMC_RPC_PPPI(nmppsAdd_32s);
#endif 

#ifdef RPC_nmppsAdd_64s
NMC_RPC_PPPI(nmppsAdd_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsSub_8s
NMC_RPC_PPPI(nmppsSub_8s);
#endif 

#ifdef RPC_nmppsSub_16s
NMC_RPC_PPPI(nmppsSub_16s);
#endif 

#ifdef RPC_nmppsSub_32s
NMC_RPC_PPPI(nmppsSub_32s);
#endif 

#ifdef RPC_nmppsSub_64s
NMC_RPC_PPPI(nmppsSub_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsAddC_8s
NMC_RPC_PIPI(nmppsAddC_8s);
#endif 

#ifdef RPC_nmppsAddC_16s
NMC_RPC_PIPI(nmppsAddC_16s);
#endif 

#ifdef RPC_nmppsAddC_32s
NMC_RPC_PIPI(nmppsAddC_32s);
#endif 

#ifdef RPC_nmppsAddC_64s
NMC_RPC_PLPI(nmppsAddC_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsSubC_8s
NMC_RPC_PIPI(nmppsSubC_8s);
#endif 

#ifdef RPC_nmppsSubC_16s
NMC_RPC_PIPI(nmppsSubC_16s);
#endif 

#ifdef RPC_nmppsSubC_32s
NMC_RPC_PIPI(nmppsSubC_32s);
#endif 

#ifdef RPC_nmppsSubC_64s
NMC_RPC_PLPI(nmppsSubC_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsSubCRev_8s
NMC_RPC_PIPI(nmppsSubCRev_8s);
#endif 

#ifdef RPC_nmppsSubCRev_16s
NMC_RPC_PIPI(nmppsSubCRev_16s);
#endif 

#ifdef RPC_nmppsSubCRev_32s
NMC_RPC_PIPI(nmppsSubCRev_32s);
#endif 

#ifdef RPC_nmppsSubCRev_64s
NMC_RPC_PLPI(nmppsSubCRev_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsRShiftC_8s
NMC_RPC_PIPI(nmppsRShiftC_8s);
#endif 

#ifdef RPC_nmppsRShiftC_16s
NMC_RPC_PIPI(nmppsRShiftC_16s);
#endif 

#ifdef RPC_nmppsRShiftC_32s
NMC_RPC_PIPI(nmppsRShiftC_32s);
#endif 

#ifdef RPC_nmppsRShiftC_64s
NMC_RPC_PIPI(nmppsRShiftC_64s);
#endif 


NMC_RPC_I(nmppsFFTFree);
#ifdef RPC_nmppsFFT256Fwd

void rpc_nmppsFFT256FwdInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT256FwdInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT256Fwd);
#endif 


#ifdef RPC_nmppsFFT256Inv

void rpc_nmppsFFT256InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT256InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT256Inv);

#endif 




#ifdef RPC_nmppsFFT512Fwd

//NMC_RPC_PPR_I(nmppsFFT512FwdInitAllocH);
void rpc_nmppsFFT512FwdInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT512FwdInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT512Fwd);
#endif 


#ifdef RPC_nmppsFFT512Inv

void rpc_nmppsFFT512InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT512InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT512Inv);

#endif 



//-------------------------------------
#ifdef RPC_nmppsFFT1024Fwd
void rpc_nmppsFFT1024FwdInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT1024FwdInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT1024Fwd);
#endif 


#ifdef RPC_nmppsFFT1024Inv

void rpc_nmppsFFT1024InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT1024InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT1024Inv);

#endif 

//-------------------------------------
#ifdef RPC_nmppsFFT2048Fwd
void rpc_nmppsFFT2048FwdInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT2048FwdInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT2048Fwd);
#endif 


#ifdef RPC_nmppsFFT2048Inv

void rpc_nmppsFFT2048InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT2048InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT2048Inv);

#endif 


#ifdef RPC_nmppsMalloc
NMC_RPC_I_P(nmppsMalloc);
#endif

//--------------------------
#ifdef RPC_nmppsMin_8s
NMC_RPC_PIR(nmppsMin_8s);
#endif 

#ifdef RPC_nmppsMin_16s
NMC_RPC_PIR(nmppsMin_16s);
#endif 

#ifdef RPC_nmppsMin_32s
NMC_RPC_PIR(nmppsMin_32s);
#endif 

#ifdef RPC_nmppsMin_64s
//NMC_RPC_PIR64(nmppsMin_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsMax_8s
NMC_RPC_PIR(nmppsMax_8s);
#endif 

#ifdef RPC_nmppsMax_16s
NMC_RPC_PIR(nmppsMax_16s);
#endif 

#ifdef RPC_nmppsMax_32s
NMC_RPC_PIR(nmppsMax_32s);
#endif 

#ifdef RPC_nmppsMax_64s
//NMC_RPC_PIR64(nmppsMax_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsAndC_8u
NMC_RPC_PIPI(nmppsAndC_8u);
#endif 

#ifdef RPC_nmppsAndC_16u
NMC_RPC_PIPI(nmppsAndC_16u);
#endif 

#ifdef RPC_nmppsAndC_32u
NMC_RPC_PIPI(nmppsAndC_32u);
#endif 

#ifdef RPC_nmppsAndC_64u
NMC_RPC_PLPI(nmppsAndC_64u);
#endif
//--------------------------
#ifdef RPC_nmppsOrC_8u
NMC_RPC_PIPI(nmppsOrC_8u);
#endif 

#ifdef RPC_nmppsOrC_16u
NMC_RPC_PIPI(nmppsOrC_16u);
#endif 

#ifdef RPC_nmppsOrC_32u
NMC_RPC_PIPI(nmppsOrC_32u);
#endif 

#ifdef RPC_nmppsOrC_64u
NMC_RPC_PLPI(nmppsOrC_64u);
#endif 
//--------------------------
#ifdef RPC_nmppsXorC_8u
NMC_RPC_PIPI(nmppsXorC_8u);
#endif 

#ifdef RPC_nmppsXorC_16u
NMC_RPC_PIPI(nmppsXorC_16u);
#endif 

#ifdef RPC_nmppsXorC_32u
NMC_RPC_PIPI(nmppsXorC_32u);
#endif 

#ifdef RPC_nmppsXorC_64u
NMC_RPC_PLPI(nmppsXorC_64u);
#endif 
//--------------------------
#ifdef RPC_nmppsNot_64u
NMC_RPC_PPI(nmppsNot_64u);
#endif 

#ifdef RPC_nmppsNot_32u
NMC_RPC_PPI(nmppsNot_32u);
#endif 

#ifdef RPC_nmppsNot_16u
NMC_RPC_PPI(nmppsNot_16u);
#endif 

#ifdef RPC_nmppsNot_8u
NMC_RPC_PPI(nmppsNot_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsAnd_64u
NMC_RPC_PPPI(nmppsAnd_64u);
#endif 

#ifdef RPC_nmppsAnd_32u
NMC_RPC_PPPI(nmppsAnd_32u);
#endif 

#ifdef RPC_nmppsAnd_16u
NMC_RPC_PPPI(nmppsAnd_16u);
#endif 

#ifdef RPC_nmppsAnd_8u
NMC_RPC_PPPI(nmppsAnd_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsOr_64u
NMC_RPC_PPPI(nmppsOr_64u);
#endif 

#ifdef RPC_nmppsOr_32u
NMC_RPC_PPPI(nmppsOr_32u);
#endif 

#ifdef RPC_nmppsOr_16u
NMC_RPC_PPPI(nmppsOr_16u);
#endif 

#ifdef RPC_nmppsOr_8u
NMC_RPC_PPPI(nmppsOr_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsXor_64u
NMC_RPC_PPPI(nmppsXor_64u);
#endif 

#ifdef RPC_nmppsXor_32u
NMC_RPC_PPPI(nmppsXor_32u);
#endif 

#ifdef RPC_nmppsXor_16u
NMC_RPC_PPPI(nmppsXor_16u);
#endif 

#ifdef RPC_nmppsXor_8u
NMC_RPC_PPPI(nmppsXor_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsRShiftC_8u
NMC_RPC_PIPI(nmppsRShiftC_8u);
#endif 

#ifdef RPC_nmppsRShiftC_16u
NMC_RPC_PIPI(nmppsRShiftC_16u);
#endif 

#ifdef RPC_nmppsRShiftC_32u
NMC_RPC_PIPI(nmppsRShiftC_32u);
#endif 

#ifdef RPC_nmppsRShiftC_64u
NMC_RPC_PIPI(nmppsRShiftC_64u);
#endif 

//--------------------------
#ifdef RPC_nmppsSum_8s
NMC_RPC_PIR(nmppsSum_8s);
#endif 

#ifdef RPC_nmppsSum_16s
NMC_RPC_PIR64(nmppsSum_16s);
#endif 

#ifdef RPC_nmppsSum_32s
NMC_RPC_PIR64(nmppsSum_32s);
#endif 

#ifdef RPC_nmppsSum_64s
NMC_RPC_PIR64(nmppsSum_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsCmpNe0_64s
NMC_RPC_PPI(nmppsCmpNe0_64s);
#endif 

#ifdef RPC_nmppsCmpNe0_32s
NMC_RPC_PPI(nmppsCmpNe0_32s);
#endif 

#ifdef RPC_nmppsCmpNe0_16s
NMC_RPC_PPI(nmppsCmpNe0_16s);
#endif 

#ifdef RPC_nmppsCmpNe0_8s
NMC_RPC_PPI(nmppsCmpNe0_8s);
#endif 
//--------------------------
#ifdef RPC_nmppsCmpLt0_64s
NMC_RPC_PPI(nmppsCmpLt0_64s);
#endif 

#ifdef RPC_nmppsCmpLt0_32s
NMC_RPC_PPI(nmppsCmpLt0_32s);
#endif 

#ifdef RPC_nmppsCmpLt0_16s
NMC_RPC_PPI(nmppsCmpLt0_16s);
#endif 

#ifdef RPC_nmppsCmpLt0_8s
NMC_RPC_PPI(nmppsCmpLt0_8s);
#endif 

//--------------------------
#ifdef RPC_nmppsCmpNeC_64s
NMC_RPC_PLPI(nmppsCmpNeC_64s);
#endif 

#ifdef RPC_nmppsCmpNeC_32s
NMC_RPC_PIPI(nmppsCmpNeC_32s);
#endif 

#ifdef RPC_nmppsCmpNeC_16s
NMC_RPC_PIPI(nmppsCmpNeC_16s);
#endif 

#ifdef RPC_nmppsCmpNeC_8s
NMC_RPC_PIPI(nmppsCmpNeC_8s);
#endif 
//--------------------------
#ifdef RPC_nmppsCmpLtC_64s
NMC_RPC_PLPI(nmppsCmpLtC_64s);
#endif 

#ifdef RPC_nmppsCmpLtC_32s
NMC_RPC_PIPI(nmppsCmpLtC_32s);
#endif 

#ifdef RPC_nmppsCmpLtC_16s
NMC_RPC_PIPI(nmppsCmpLtC_16s);
#endif 

#ifdef RPC_nmppsCmpLtC_8s
NMC_RPC_PIPI(nmppsCmpLtC_8s);
#endif 