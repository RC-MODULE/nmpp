#ifndef RING_INCLUDED
#define RING_INCLUDED
#include <string.h>
#include <time.h>

#ifdef __NM__ 
#undef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 320000000
#endif


#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define RING_BUFFER_DECLARED	0xDEC1A8ED
#define RING_BUFFER_ALLOCATED	0xA10CA7ED
#define RING_BUFFER_MEM_ERROR	0xDEADF00D
#define RING_BUFFER_ERROR		0xBEDABEDA
#define RING_BUFFER_OK			0x0

#define EXIT_ON_TIMEOUT       1
#define EXIT_ON_COMPLETED     0
#define EXIT_ON_FULL_BUFFER   2
#define EXIT_ON_EMPTY_BUFFER  2

#ifdef __NM__
#define bytesizeof(T) (sizeof(T)<<2)
#else
#define bytesizeof(T) sizeof(T)
#endif 

typedef  void *(*memcpy_ptr)(void *, void const *, size_t) ;
typedef  void *(*t_bytecpy)(void *to, int toIndex, void const *from, int fromIndex, size_t size) ;
template <class T> class C_RingBuffer{
public:	
	T* 		data;			///<  физический адрес кольцевого буфера входных данных 
	size_t 	size;			///<  размер кольцевого буфера входных данных (в элементах; гарантируется что это степень двойки)
	size_t 	head;			///<  сколько элементов ОТ НАЧАЛА ПОТОКА код MASTER уже записал в	буфер входных данных [заполняется MASTER]
	size_t 	tail;			///<  сколько элементов ОТ НАЧАЛА ПОТОКА код SLAVE  уже прочитал (обработал) 			 [заполняется SLAVE]
	size_t* head_addr;
	size_t* tail_addr;
	size_t 	id;
	
	t_bytecpy push_memcpy;
	t_bytecpy pop_memcpy;

	// ------------- dma --------------
	memcpy_ptr dma_init;
	size_t(*dma_check)();
	T*     dma_ptr;
	size_t dma_left;
	size_t dma_size;
	//----------------------------------
	unsigned timeout;    // msec
	unsigned time2sleep; // msec
	int 	pad[16-3-5*sizeof(memcpy_ptr)/sizeof(int)];	///<  резервные поля
	
	
	void Sleep(clock_t msec ){
		#ifdef __NM__ 
		clock_t dt=msec*(CLOCKS_PER_SEC/1000);	
		clock_t t0=clock();
		while(clock()-t0<dt){
			__asm{
				rep 32 with vfalse;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 [ar7] = afifo;
			}
		}
			
		#else
			::Sleep(msec);
		#endif
	}
	C_RingBuffer(){
		
		//sizeof_size_t=sizeof(size_t);
		//sizeof_T=sizeof(T);
		//Init(0,0,(memcpy_ptr)memcpy,(memcpy_ptr)memcpy);
		Init(0,0,0,0);
	}
	C_RingBuffer(T* buffer,size_t count, t_bytecpy pushmemcpy, t_bytecpy popmemcpy ){
		Init(buffer,count,pushmemcpy,popmemcpy);
	}
	//void Init(T* buffer,size_t count, memcpy_ptr pushmemcpy, memcpy_ptr popmemcpy ){
	bool Init(T* buffer,size_t count, t_bytecpy pushmemcpy, t_bytecpy popmemcpy ){
		if (buffer==0) return false;
		if (count&(count-1)!=0) return false ;
		data=buffer;
		size=count;
		head=0;
		tail=0;
		head_addr=&head;
		tail_addr=&tail;
		id=0x600DB00F;
		push_memcpy=(t_bytecpy)pushmemcpy;
		pop_memcpy =(t_bytecpy)popmemcpy;
		dma_init=0;
		dma_check=0;
		dma_ptr =0;
		dma_left=0;
		dma_size=0;
		time2sleep=1;	// msec
		timeout=100;	// 
		return true;
		
	}

	__INLINE__ bool IsFull(){
		return (head-tail==size);
	}
	__INLINE__ bool IsEmpty(){
		return (head==tail);
	}
	__INLINE__ size_t PushAvail(){
		return (size-(head-tail));
	}
	__INLINE__ size_t PopAvail(){
		return (head-tail);
	}
	
	
	T* Head(){
		if (PushAvail()==0)
			return 0;
		size_t headPointer=head&(size-1);
		T* pElement=data+headPointer;
		return pElement;
	}
	T* Tail(){
		if (PopAvail()==0)
			return 0;
		size_t tailPointer=tail&(size-1);
		T* pElement=data+tailPointer;
		return pElement;
	}
	
	bool MoveHead(int numElements){
		size_t h=head+numElements;
		if (h>tail+size)
			return RING_BUFFER_ERROR;
		head=h;
		return RING_BUFFER_OK;
	}

	bool MoveTail(int numElements){
		size_t t=tail+numElements;
		if (t>head)
			return RING_BUFFER_ERROR;
		tail=t;
		return RING_BUFFER_OK;
	}
	

	size_t Push(T* pSrcElements, size_t numElements, int ExitMode= EXIT_ON_COMPLETED)
	{
		size_t initHead=head;
		size_t count;
		size_t diff;
		clock_t t0=clock();
		size_t posSrc=0;
		while (numElements){
			size_t Tail=tail;
			size_t posHead=head&(size-1);			
			size_t posTail=Tail&(size-1);
			if (posTail<posHead || head==Tail)
				diff=size-posHead; 
			else if (posHead<posTail)
				diff=posTail-posHead; 
			else if (ExitMode&EXIT_ON_FULL_BUFFER) // buffer is full
				return (head-initHead);	
			else if (ExitMode&EXIT_ON_TIMEOUT){
				if ((clock()-t0)>timeout*(CLOCKS_PER_SEC/1000))
					return (head-initHead);	
				Sleep(time2sleep);
				continue;
			} else {							// EXIT_ON_COMPLETED
				Sleep(time2sleep);
				continue;
			}
			
			count=MIN(numElements,diff);
			if (push_memcpy(data,posHead*bytesizeof(T),pSrcElements,posSrc*bytesizeof(T),count*bytesizeof(T))){
				head+=count;
				posSrc+=count;
				numElements -=count;
			}
		}
		return (head-initHead);
	}
	
	size_t Push(T pSrcElement)
	{
		return Push(&pSrcElement,1,EXIT_ON_COMPLETED);
	}
	
	void PushRequest(T* pSrcElements, size_t numElements)
	{
		size_t posHead;
		size_t posTail;
		size_t diff=0;
		while(diff==0){
			///!!! Head or head ??
			posHead=head&(size-1);
			posTail=tail&(size-1);
			if (posTail<posHead || head==tail)
				diff=size-posHead; 
			else if (posHead<posTail)
				diff=posTail-posHead; 
			else { // buffer is full
				Sleep(time2sleep);
				continue;
			} 
		}
		dma_ptr =pSrcElements;
		dma_left =numElements;
		dma_size =MIN(dma_left,diff);
		//dma_init(data,posHead,pSrcElements,0,dma_size*sizeof(T));
	}

	bool isPushCompleted()
	{
		if (dma_left==0)
			return true;
		if (dma_check())
			return false;
		
		head     +=dma_size;
		dma_ptr +=dma_size;
		dma_left -=dma_size;
		if (dma_left){
			PushRequest(dma_ptr,dma_left);//?
			return false;
		}
		return true;
			
	}
	
	
		
	
	
	
	size_t Pop(T* pDstElements, size_t numElements, int ExitMode= EXIT_ON_COMPLETED)
	{
		size_t initTail=tail;
		size_t count;
		size_t diff;
		clock_t t0=clock();
		size_t posDst=0;
		while (numElements){
			size_t Head=head;
			size_t posHead=Head&(size-1);
			size_t posTail=tail&(size-1);
			if (posTail<posHead )
				diff=posHead-posTail; 
			else if (posHead<=posTail && Head!=tail)
				diff=size-posTail; 
			else if (ExitMode&EXIT_ON_EMPTY_BUFFER) // buffer is empty
				return (tail-initTail);	
			else if (ExitMode&EXIT_ON_TIMEOUT){
				if ((clock()-t0)>timeout)
					return (tail-initTail);	
				Sleep(time2sleep);
				continue;
			} else {
				//Sleep(time2sleep);
				continue;
			}
			
			count=MIN(numElements,diff);
			pop_memcpy(pDstElements,posDst*bytesizeof(T),data,posTail*bytesizeof(T),count*bytesizeof(T));
			tail+=count;
			posDst+=count;
			numElements -=count;
		}
		return (tail-initTail);
	}
	
	
	
	
	
	

};


#endif
