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

typedef void (*t_free_func)(void*);
typedef void (*Free32Func)(void*);
typedef void* (*Malloc32Func)(unsigned int);

typedef unsigned long long NmppsAllocation ;

enum  MALLOC32_MODE {MALLOC32_FIXED_ORDER, MALLOC32_PRIOR_ORDER, MALLOC32_RANDOM_ORDER };

struct NmppsMalloc32Spec{
	Malloc32Func allocator[4];	
	enum MALLOC32_MODE orderType;
	unsigned int numBufAllocated;
	unsigned int nextFixedIndx;
	unsigned int priorOrder;
	unsigned int randomMask;
	unsigned int status;
	unsigned long long allocHistory;
	NmppsAllocation fixedOrder;
};
extern struct NmppsMalloc32Spec nmppsMalloc32Spec;


void* nmppsMalloc32(unsigned sizeInt32);
void  nmppsFree32(void* bufer);
void  nmppsMalloc32Mode(NmppsAllocation order, enum MALLOC32_MODE orderType);
void  nmppsMalloc32ModeA(unsigned* arr, int size , enum MALLOC32_MODE orderType);
int   nmppsMalloc32GetHistory(NmppsAllocation* order, int numAllocations);

#ifdef __cplusplus
		};
#endif

#endif
