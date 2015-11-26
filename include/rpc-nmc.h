#define RPC_NMC_PPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src = aura_get_buf(); \
	int *src  =aura_buffer_to_ptr(buf_src); \
	aura_buffer buf_dst = aura_get_buf(); \
	int *dst =aura_buffer_to_ptr(buf_dst);	 \
	unsigned size = aura_get_u32(); \
	func(src,dst,size); \
}
#define RPC_NMC_PPPI(func) \
void rpc_ ## func(void *in, void *out) \
{ \
	aura_buffer buf_src0 = aura_get_buf(); \
	aura_buffer buf_src1 = aura_get_buf(); \
	int *src0  =aura_buffer_to_ptr(buf_src0); \
	int *src1  =aura_buffer_to_ptr(buf_src1); \
	aura_buffer buf_dst = aura_get_buf(); \
	int *dst =aura_buffer_to_ptr(buf_dst);	\
	unsigned size = aura_get_u32(); \
	func(src0,src1,dst,size); \
} 

#ifdef RPC_nmppsAbs_32s
RPC_NMC_PPI (nmppsAbs_32s);
#endif 

#ifdef RPC_nmppsAdd_32s
RPC_NMC_PPPI(nmppsAdd_32s);
#endif 