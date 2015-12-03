typedef void (func_p_t)(void*);
typedef void*(func_i_p_t)(int);
typedef void (func_ppi_t)(void*,void*,int);
typedef void (func_pppi_t)(void*,void*,void*,int);
typedef void (func_pipi_t)(void*,int,void*,int);
typedef void (func_ppp_t)(void*,void*,void*);
typedef int  (func_ppp_i_t)(void*,void*,void*);

#define NMC_RPC_I_P(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	unsigned i = aura_get_u32(); \
	func_i_t *unifunc=(func_i_t*)func; \
	void* p=unifunc(i); \
	aura_put_u32((int)p); \
}


#define NMC_RPC_PPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src = aura_get_buf(); \
	aura_buffer buf_dst = aura_get_buf(); \
	int *src = aura_buffer_to_ptr(buf_src); \
	int *dst = aura_buffer_to_ptr(buf_dst);	 \
	unsigned size = aura_get_u32(); \
	func_ppi_t *unifunc=(func_ppi_t*)func; \
	unifunc(src,dst,size); \
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
//NMC_RPC_PIPI(nmppsAddC_64s);
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
//NMC_RPC_PIPI(nmppsSubC_64s);
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


#ifdef RPC_nmppsFFT256Fwd
NMC_RPC_PPP(nmppsFFT256FwdOptimize);
NMC_RPC_PPP_I(nmppsFFT256FwdInitAlloc);
NMC_RPC_PPP(nmppsFFT256Fwd);
NMC_RPC_P(nmppsFFTFree);
#endif 

#ifdef RPC_nmppsMalloc
NMC_RPC_I_P(nmppsMalloc);
#endif


