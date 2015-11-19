#ifndef MALLOC32_DEFINED
#define MALLOC32_DEFINED
#include <malloc.h>
#include "nmtype.h"
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
typedef uint64 fifo64;
typedef uint32 fseq32;


enum  MALLOC32_MODE {MALLOC32_PRIORITY_MODE, MALLOC32_ROUTE_MODE, MALLOC32_LONG_ROUTE_MODE,  MALLOC32_FIXED_MODE, MALLOC32_RANDOM_MODE };

struct NmppsMalloc32Spec{
	Malloc32Func allocator[4];	
	enum    MALLOC32_MODE mode;
	uint32  random;			//  bit-mask of available heaps
	fseq32  priority;		//  heap allocation sequence in decdendnig priority terminated by 0xF

	uint32  numBufAllocated;
	uint32  status;			//  error status
	
	uint32  boundarySize;	//  
	uint32  boundaryFill;	//
	



	uint64* route;
	uint32  routePos;
	uint32  routeSize;
	uint64  routeInternal;

	fifo64  routeHistoryFifo;	//  heap allocation history with 0xF terminated 
	uint64* routeHistory;		
	uint32  routeHistorySize;
	uint32  routeHistoryMaxSize;
	
	void**  fixed;		
	uint32  fixedPos;		
	uint32  fixedSize;		
	void**  fixedHistory;		
	uint32  fixedHistorySize;
	uint32  fixedHistoryMaxSize;


};

#ifdef __NM__
	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32);}
#else 
	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32*4);}
#endif
	
void*  nmppsMalloc32 (unsigned sizeInt32);
__INLINE__ nm8s*  nmppsMalloc_8s (unsigned sizeInt8) { return (nm8s*)  nmppsMalloc32((sizeInt8+7)/4);}
__INLINE__ nm8u*  nmppsMalloc_8u (unsigned sizeInt8) { return (nm8u*)  nmppsMalloc32((sizeInt8+7)/4);}
__INLINE__ nm16s* nmppsMalloc_16s(unsigned sizeInt16){ return (nm16s*) nmppsMalloc32((sizeInt16+3)/2);}
__INLINE__ nm16u* nmppsMalloc_16u(unsigned sizeInt16){ return (nm16u*) nmppsMalloc32((sizeInt16+3)/2);}
__INLINE__ nm32s* nmppsMalloc_32s(unsigned sizeInt32){ return (nm32s*) nmppsMalloc32(sizeInt32+(1&sizeInt32));}
__INLINE__ nm32u* nmppsMalloc_32u(unsigned sizeInt32){ return (nm32u*) nmppsMalloc32(sizeInt32+(1&sizeInt32));}
__INLINE__ nm64s* nmppsMalloc_64s(unsigned sizeInt64){ return (nm64s*) nmppsMalloc32((sizeInt64)<<1);}
__INLINE__ nm64u* nmppsMalloc_64u(unsigned sizeInt64){ return (nm64u*) nmppsMalloc32((sizeInt64)<<1);}
void   nmppsFree32(void* buffer);

typedef uint64  seq64;
typedef uint64 fseq64;

void  nmppsMalloc32SetRouteMode (fseq64  heapSeq);
//void  nmppsMalloc32SetRouteMode (seq64   heapSeq,  int heapCount);
void  nmppsMalloc32SetBigRouteMode(seq64*  heapSeq,  int heapCount);
void  nmppsMalloc32SetRandomMode(uint32  heapSet,  int heapCount);
void  nmppsMalloc32SetPriorityMode (seq64   heapSeq,  int heapCount);
void  nmppsMalloc32SetFixedMode(void**  addrSeq,  int addrCount);
void  nmppsMalloc32StartAddrRec (void**  addrSeq,  int maxAddrCount);
int   nmppsMalloc32StopAddrRec  ();
void  nmppsMalloc32StartRouteRec (seq64*  heapSeq,  int maxHeapCount);
int   nmppsMalloc32StopRouteRec  ();
void  nmppsMalloc32SetBoundary  (int size, int fill );
int   nmppsMalloc32CheckBoundary(void*);
int   nmppsMalloc32IsErrorStatus();
void  nmppsMalloc32ResetStatus  ();
int   nmppsMalloc32GetHistory   (fseq64*  heapSeq, int seqSize);

extern struct NmppsMalloc32Spec nmppsMalloc32Spec;


 /**
    \defgroup nmppsMalloc nmppsMalloc
    \ingroup vSupport
    \brief
        \ru Распределение памяти для векторов библиотеки. 
        \en Memory allocation for library vectors. 
		\~
    \param nSize 
        \ru Число элементов в векторе. 
        \en Number of elements in vec. 
		\~
    \param hint 
        \ru Номер банка памяти. Может принимать значения 
                    MEM_LOCAL, MEM_GLOBAL. 
        \en Number of memory bank. Admissible values for memory bank
                    are MEM_LOCAL, MEM_GLOBAL. 
		\~
    \note 
		\ru Память, распределенная с помощью функций nmppsMalloc_ должна
              освобождаться с помощью функции nmppsFree(). 
        \en Memory allocated with function nmppsMalloc_ should be 
              freed with function nmppsFree()
		\~
    */
    //! \{
/*
void nmppsMalloc_64s(nm64s** pptr, int nSize, int hint );

__INLINE__ void nmppsMalloc_1 (nm1**   pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>6) +1, hint);}
__INLINE__ void nmppsMalloc_2s(nm2s**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>5) +1, hint);}
__INLINE__ void nmppsMalloc_2u(nm2u**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>5) +1, hint);}
__INLINE__ void nmppsMalloc_4s(nm4s**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>4) +1, hint);}
__INLINE__ void nmppsMalloc_4u(nm4u**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>4) +1, hint);}
__INLINE__ void nmppsMalloc_8u(nm8u**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>3) +1, hint);}
__INLINE__ void nmppsMalloc_8s(nm8s**  pptr, int nSize, int hint ) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>3) +1, hint);}
__INLINE__ void nmppsMalloc_16u(nm16u** pptr, int nSize, int hint) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>2) +1, hint);}
__INLINE__ void nmppsMalloc_16s(nm16s** pptr, int nSize, int hint) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>2) +1, hint);}
__INLINE__ void nmppsMalloc_32u(nm32u** pptr, int nSize, int hint) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>1) +1, hint);}
__INLINE__ void nmppsMalloc_32s(nm32s** pptr, int nSize, int hint) { nmppsMalloc_64s((nm64s**)pptr, (nSize>>1) +1, hint);}
__INLINE__ void nmppsMalloc_64u(nm64u** pptr, int nSize, int hint) { nmppsMalloc_64s((nm64s**)pptr, nSize, hint);}
*/
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsFree nmppsFree
    \ingroup vSupport
    \brief
        \ru Освобождение памяти для векторов. 
        \en Memory deallocation for vectors. 
		\~
    \note 
		  \ru Данная функция должна вызываться только для
              векторов, распределенных с помощью функций 
              nmppsMalloc_.
          \en This function should be called only for matrixis
              allocated by nmppsMalloc_ functions. 
		\~
    */
    //! \{


 __INLINE__  void nmppsFree(void* ptr) {nmppsFree32((void*)ptr);}
    //! \}
    
    

#ifdef __cplusplus
		};
#endif

#endif
