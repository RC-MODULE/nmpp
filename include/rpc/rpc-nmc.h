#include "easynmc/aura.h"

typedef void (func_p_t)(void*);
//typedef void*(func_i_p_t)(int);
typedef void (func_ppi_t)(void*,void*,int);
typedef int (func_ppi_i_t)(void*,void*,int);
typedef int (func_ppr_i_t)(void*,void*,int*);
typedef void (func_pppi_t)(void*,void*,void*,int);
typedef void (func_pipi_t)(void*,int,void*,int);
typedef void (func_plpi_t)(void*,long,void*,int);
typedef void (func_pip_t)(void*,int,void*);
typedef void (func_ppp_t)(void*,void*,void*);
typedef int  (func_ppp_i_t)(void*,void*,void*);
typedef void (func_pppii_t) (void*,void*,void*,int,int);
typedef void (func_piippi_t) (void*,int,int,void*,void*,int);
typedef void (func_ppip_t) (void*,void*,int,void*); 

#include <time.h>

//#define NMC_RPC_I_P(func) \
//void rpc_ ## func(void *in, void *out) \
//{ \
//	unsigned i = aura_get_u32(); \
//	func_i_t *unifunc=(func_i_t*)func; \
//	void* p=unifunc(i); \
//	aura_put_u32((int)p); \
//}
//
//#define NMC_RPC_I(func) \
//void rpc_ ## func(void *in, void *out) \
//{ \
//	unsigned i = aura_get_u32(); \
//	func_i_p_t *unifunc=(func_i_p_t*)func; \
//	unifunc(i); \
//}


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
	unifunc(src,dst,size); \
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

#define NMC_RPC_PPIR64(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	unsigned size = aura_get_u32(); \
	func_ppip_t *unifunc=(func_ppip_t*)func; \
	long ret ; \
	unifunc(src0,src1,size,&ret); \
	aura_put_u64(ret); \
}

#define NMC_RPC_PPPII(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	int *dst   = aura_buffer_to_ptr(buf_dst); \
	unsigned height = aura_get_u32(); \
	unsigned width = aura_get_u32(); \
	func_pppii_t *unifunc=(func_pppii_t*)func; \
	unifunc(src0,src1,dst,height,width); \
}

#define NMC_RPC_PIIPPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	unsigned height = aura_get_u32(); \
	unsigned width0 = aura_get_u32(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	aura_buffer buf_dst  = aura_get_buf(); \
	unsigned width1 = aura_get_u32(); \
	int *src0  = aura_buffer_to_ptr(buf_src0); \
	int *src1  = aura_buffer_to_ptr(buf_src1); \
	int *dst   = aura_buffer_to_ptr(buf_dst); \
	func_piippi_t *unifunc=(func_piippi_t*)func; \
	unifunc(src0,height,width0,src1,dst,width1); \
}
