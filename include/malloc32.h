#ifndef MALLOC32_DEFINED
#define MALLOC32_DEFINED
#include <malloc.h>
#include "nmtype.h"

//#define void* malloc32 (unsigned size_int32 );
//#define malloc32 nmppsMalloc_32s
typedef void (*t_free_func)(void*);
#ifdef __cplusplus
		extern "C" {
#endif


#define HEAP_0 1
#define HEAP_1 2
#define HEAP_2 4
#define HEAP_3 8


void* malloc32 (unsigned size_int32, unsigned bank_mask);
void  free32(void* p);


typedef void (Free32Func)(void*);
typedef void* (Malloc32Func)(unsigned int);

#define NMPP_OPTIMIZE_ALLOC 1
#define NMPP_CUSTOM_ALLOC 2


#define  ENABLE_HISTORY 1 
#define  ENABLE_RANDOM 1
enum  MALLOC32_MODE {MALLOC32_RING_MODE,MALLOC32_HISTORY_MODE,MALLOC32_PRIORITY_MODE, MALLOC32_ROUTE_MODE, MALLOC32_LONG_ROUTE_MODE,  MALLOC32_FIXED_MODE, MALLOC32_RANDOM_MODE };
#define NMPPS_MALLOC_LIMIT 128
#define NMPPS_MALLOC_MAX_POS NMPPS_MALLOC_LIMIT-1

struct NmppsMallocSpec{
	Malloc32Func* allocator[4];	
	enum    MALLOC32_MODE mode;
	uint32  random;			//  bit-mask of available heaps
	fseq32  priority;		//  heap allocation sequence in decdendnig priority terminated by 0xF
	uint32  status;			//  error status
	uint32 	time;
	uint32 	timeBest;
	uint32  routePos;
	fseq64  route[NMPPS_MALLOC_LIMIT/16];
	fseq64  bestRoute[NMPPS_MALLOC_LIMIT/16];
	void* 	allocHistory[NMPPS_MALLOC_LIMIT];
	void* 	freeHistory[NMPPS_MALLOC_LIMIT];
	uint32 	allocHistoryPos;
	uint32 	freeHistoryPos;
	uint32  firstPass;
};

struct NmppsTmpSpec {
	void* buffer0;
	void* buffer1;
} ;

	
void*  nmppsMalloc32  (unsigned sizeInt32);
nm1*   nmppsMalloc_1  (unsigned sizeInt1) ;
nm2s*  nmppsMalloc_2s (unsigned sizeInt2) ;
nm2u*  nmppsMalloc_2u (unsigned sizeInt2) ;
nm4s*  nmppsMalloc_4s (unsigned sizeInt4) ;
nm4u*  nmppsMalloc_4u (unsigned sizeInt4) ;
nm8s*  nmppsMalloc_8s (unsigned sizeInt8) ;
nm8u*  nmppsMalloc_8u (unsigned sizeInt8) ;
nm16s* nmppsMalloc_16s(unsigned sizeInt16);
nm16u* nmppsMalloc_16u(unsigned sizeInt16);
nm32s* nmppsMalloc_32s(unsigned sizeInt32);
nm32sc* nmppsMalloc_32sc(unsigned sizeCmplxInt32);
nm32fc* nmppsMalloc_32fc(unsigned sizeCmplxFloat);
nm32u* nmppsMalloc_32u(unsigned sizeInt32);
nm64s* nmppsMalloc_64s(unsigned sizeInt64);
nm64u* nmppsMalloc_64u(unsigned sizeInt64);
void   nmppsFree32(void* buffer);

typedef struct {
	void* pull;
	nm8u* data;
}NmppsFrame_8u;

typedef struct {
	void* pull;
	nm8s* data;
}NmppsFrame_8s;

typedef struct {
	void* pull;
	nm16u* data;
}NmppsFrame_16u;

typedef struct {
	void* pull;
	nm16s* data;
}NmppsFrame_16s;

typedef struct {
	void* pull;
	nm32u* data;
}NmppsFrame_32u;

typedef struct {
	void* pull;
	nm32s* data;
}NmppsFrame_32s;

typedef struct {
	void* pull;
	nm64u* data;
}NmppsFrame_64u;

typedef struct {
	void* pull;
	nm64s* data;
}NmppsFrame_64s;

//NmppsFrame_32s* nmppsMallocFrame32  (unsigned sizeInt32, unsigned boundaryInt32);
nm8s*  nmppsMallocFrame_8s (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8s * pFrame) ;
nm8u*  nmppsMallocFrame_8u (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8u * pFrame) ;
nm16s* nmppsMallocFrame_16s(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16s* pFrame);
nm16u* nmppsMallocFrame_16u(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16u* pFrame);
nm32s* nmppsMallocFrame_32s(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32s* pFrame);
nm32u* nmppsMallocFrame_32u(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32u* pFrame);
nm64s* nmppsMallocFrame_64s(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64s* pFrame);
nm64u* nmppsMallocFrame_64u(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64u* pFrame);
void   nmppsFreeFrame(void* pFrame);


/*
typedef struct ss {
	void* pull;
	void* data;
}NmppiFrame;

nm8s*  nmppiMallocFrame_8s (unsigned width, unsigned height, unsigned border, NmppiFrame_8s * pFrame);
nm8u*  nmppiMallocFrame_8u (unsigned width, unsigned height, unsigned border, NmppiFrame_8u * pFrame);
nm16s* nmppiMallocFrame_16s(unsigned width, unsigned height, unsigned border, NmppiFrame_16s* pFrame);
nm16u* nmppiMallocFrame_16u(unsigned width, unsigned height, unsigned border, NmppiFrame_16u* pFrame);
nm32s* nmppiMallocFrame_32s(unsigned width, unsigned height, unsigned border, NmppiFrame_32s* pFrame);
nm32u* nmppiMallocFrame_32u(unsigned width, unsigned height, unsigned border, NmppiFrame_32u* pFrame);
nm64s* nmppiMallocFrame_64s(unsigned width, unsigned height, unsigned border, NmppiFrame_64s* pFrame);
nm64u* nmppiMallocFrame_64u(unsigned width, unsigned height, unsigned border, NmppiFrame_64u* pFrame);
void   nmppsFreeFrame32(void* buffer);
*/



typedef struct {
	void* 	buffer;
	int   	status;
	int 	mode;
	fseq64  route;
} SpecTmp1;
//
//typedef struct {
//	nm8s* 	buffer0;
//	nm8s* 	buffer1;
//	int   	status;
//	int 	mode;
//	fseq64  route;
//} Spec8s;

//int    nmppsMallocCreate(int limit);
//int    nmppsMallocDestroy();
//int    nmppsMallocMode(WIPE_ENABLE|REC_HISTORY|REC_ROUTE);

//void*  nmppsMallocSpec_8s(SpecTmp1* spec,int size, int mode);
void*  nmppsMallocSpec1(SpecTmp1* spc,int sizeBuf0,int , int);
void*  nmppsFreeSpec1  (SpecTmp1* spc);

int   nmppsMallocResetPos();
int   nmppsMallocResetRoute ();
void  nmppsMallocSetRouteMode  ();
void  nmppsMallocSetRingMode  ();
//void  nmppsMallocSetRouteModeEx(seq64*  heapSeq,  int routeSize, int routeLimit);

//void  nmppsMallocSetBigRouteMode(seq64*  heapSeq,  int heapCount);
//void  nmppsMallocSetRandomMode(uint32  heapSet,  int heapCount);
//void  nmppsMallocSetPriorityMode (seq64   heapSeq,  int heapCount);
//void  nmppsMallocSetHistoryMode(seq64*  addrSeq,  void** allocSeq);
void  nmppsMallocSetHistoryMode();
void  nmppsMallocRecHistory (void**  allocSeq, void** freeSeq);
//int   nmppsMallocStopAddrRec  ();
//void  nmppsMallocStartRouteRec (seq64*  heapSeq,  int maxHeapCount);
//int   nmppsMallocStopRouteRec  ();
//void  nmppsMallocSetBoundary32 (int size32 );
//void  nmppsMallocSetFill32(int borderColor, int dataColor );
//int   nmppsMallocCheckBoundary(void*);
//int   nmppsMallocIsErrorStatus();
int   nmppsMallocSuccess();
int   nmppsMallocFail();
int   nmppsMallocStatus();
void  nmppsMallocResetStatus  ();
//int   nmppsMallocGetHistory   (fseq64*  heapSeq, int seqSize);
//int   nmppsMallocSaveState();
//int   nmppsMallocRestoreState();
//void nmppsMallocReset(seq64* currRoute,void** allocHistory,void** freeHistory, int size);

void nmppsMallocTimerStart();
void nmppsMallocTimerResume();
void nmppsMallocTimerStop();

//void nmppsMallocNextRoute(seq64* currRoute, int mode);
void nmppsMallocRandomRoute();
int  nmppsMallocIncrementRoute();
int  nmppsMallocWipe();
int  nmppsMallocBetterRoute();
void nmppsMallocSetBestRoute(int historyEnable);
int  nmppsMallocSetRoute(fseq64* route, int count); // implemented 
void nmppsMallocSetShortRoute(fseq64 route);
void nmppsMallocSetRoute16(fseq64 route);
extern struct NmppsMallocSpec nmppsMallocSpec;


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


   void nmppsFree(void* ptr); 
    
    //! \}
    
    

#ifdef __cplusplus
		};
#endif

#endif
