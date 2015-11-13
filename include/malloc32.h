#ifndef MALLOC32_DEFINED
#define MALLOC32_DEFINED

#ifdef __cplusplus
		extern "C" {
#endif

#define HEAP_0 1
#define HEAP_1 2
#define HEAP_2 4
#define HEAP_3 8

//void* malloc32 (unsigned size_int32 );
//void* malloc32 (unsigned size_int32, unsigned bank_mask);
//void  free32(void* p);
#ifndef uint64 
typedef unsigned long long uint64;
#endif 

#ifndef uint32
typedef unsigned int uint32;
#endif 

typedef void (*t_free_func)(void*);
typedef void (*Free32Func)(void*);
typedef void* (*Malloc32Func)(unsigned int);


enum  MALLOC32_MODE {MALLOC32_PRIOR_SEQ, MALLOC32_FIXED_SEQ, MALLOC32_RANDOM_SEQ, MALLOC32_ADDR_SEQ };

struct NmppsMalloc32Spec{
	Malloc32Func allocator[4];	
	enum   MALLOC32_MODE mode;
	uint32 numBufAllocated;
	uint32 nextFixedIndx;
	uint32 priorOrder;
	uint32 randomMask;
	uint32 status;
	uint32 heapCount;
	uint32 boundary;
	uint32 fill;
	uint64 allocHistory;
	uint64 fixedOrder;
};
void* nmppsMalloc32(unsigned sizeInt32);
void  nmppsFree32(void* buffer);

void  nmppsMalloc32InitFixedSeqF(uint64  heapSeq);
void  nmppsMalloc32InitFixedSeq (uint64  heapSeq,  int heapCount);
void  nmppsMalloc32InitFixedSeqA(uint64* heapSeq,  int heapCount);
void  nmppsMalloc32InitRandomSeq(uint32  heapSet,  int heapCount);
void  nmppsMalloc32InitPriorSeq (uint64  heapSeq,  int heapCount);
void  nmppsMalloc32InitAddrSeq  (void**  addrSeq,  int addrCount);
void  nmppsMalloc32StartAddrRec (void**  addrSeq,  int maxAddrCount);
int   nmppsMalloc32StopAddrRec  ();
void  nmppsMalloc32StartHeapRec (uint64* heapSeq,  int maxHeapCount);
int   nmppsMalloc32StopHeapRec  ();
void  nmppsMalloc32InitBoundary (int size, int fill );
int   nmppsMalloc32CheckBoundary(void*);
int   nmppsMalloc32IsErrorStatus();
void  nmppsMalloc32ResetStatus  ();
int   nmppsMalloc32GetHistory   (uint64* heapSeq, int allocCount);

extern struct NmppsMalloc32Spec nmppsMalloc32Spec;




#ifdef __cplusplus
		};
#endif

#endif
